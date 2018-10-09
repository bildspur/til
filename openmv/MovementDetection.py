# Movement Detection
# cansik @ bildspur 2018

import sensor, image, pyb, os, time, utime, math

sensor.reset()                      # Reset and initialize the sensor.
sensor.set_pixformat(sensor.GRAYSCALE) # Set pixel format to RGB565 (or GRAYSCALE)
sensor.set_framesize(sensor.QVGA)   # Set frame size to QVGA (320x240)
sensor.skip_frames(time = 500)     # Wait for settings take effect.
sensor.set_auto_whitebal(True)
clock = time.clock()                # Create a clock object to track the FPS.

# variables
extra_fb = sensor.alloc_extra_fb(sensor.width(), sensor.height(), sensor.GRAYSCALE)
uart = pyb.UART(3, 9600, timeout_char = 1000)

red_led = pyb.LED(1)
green_led = pyb.LED(2)
blue_led = pyb.LED(3)

trigger_threshold = 5

# debug
show_debug = True
debug_color = (0, 0, 0)

# blob detection
blob_threshold = (5, 255)
pixels_threshold = 250
area_threshold = 5000

# tracking
tracking_distance_threshold = 150
tracking_area_threshold = 100000 # remove tracking area as distinguisher
moving_objects = []
last_frame_triggered = False

# trigger
min_life = 10
min_distance = 150

# start of  main
sensor.skip_frames(time = 2000) # Give the user time to get ready.
extra_fb.replace(sensor.snapshot())

def blink_led(led):
    led.on()
    utime.sleep_ms(200)
    led.off()

def distance(p1, p2):
    return math.sqrt(((p1[0]-p2[0])**2)+((p1[1]-p2[1])**2))

# check if mos have to trigger
def trigger_movement(moving_objects):
    for mo in moving_objects:
        d = mo.moved_distance()
        if d > min_distance and mo.life > min_life:
            direction = mo.moved_direction()

            # only check x
            print("Trigger: %s" % ("Right" if direction[0] else "Left"))

            # light up led
            blink_led(red_led if direction[0] else blue_led)

            # send UART
            if direction[0]:
                uart.write("t:r")
            else:
                uart.write("t:l")

            # delete object
            mo.is_dead = True

# update mos with blobs
def update_tracking(blobs, moving_objects):
    # reset flags
    for mo in moving_objects:
        mo.updated = False

    # update mos with blobs
    for blob in blobs:
        is_used = False

        # check for each mos if it is used
        for mo in moving_objects:
            if mo.check_match(blob, tracking_distance_threshold, tracking_area_threshold):
                is_used = True
                break

        # add to list if not used
        if not is_used:
            moving_objects.append(MovingObject(blob))

    # filter not updated and dead objects
    alive_mos = [mo for mo in moving_objects if mo.updated and not mo.is_dead]

    moving_objects.clear()
    for mo in alive_mos:
        moving_objects.append(mo)

# trackable object
class MovingObject:
    def __init__(self, blob):
        self.blob = blob
        self.is_dead = False
        self.life = 1
        self.updated = True
        self.start_position = (blob.cx(), blob.cy())

    def moved_distance(self):
        return distance(self.start_position, (self.blob.cx(), self.blob.cy()))

    # returns direction (true -> right, false -> left)
    def moved_direction(self):
        x = self.blob.cx() - self.start_position[0] > 0
        y = self.blob.cy() - self.start_position[1] > 0
        return (x, y)

    def check_match(self, blob, distance_threshold, area_threshold):
        d = distance((blob.cx(), blob.cy()), (self.blob.cx(), self.blob.cy()))
        a = abs(blob.area() - self.blob.area())

        if d < distance_threshold and a < area_threshold:
            self.blob = blob
            self.updated = True
            self.life += 1

        return self.updated

while(True):
    clock.tick()

    # read image and take difference from framebuffer
    img = sensor.snapshot()
    extra_fb.difference(img)

    # detect if there is a change
    hist = extra_fb.get_histogram()
    diff = hist.get_percentile(0.99).l_value() - hist.get_percentile(0.90).l_value()
    triggered = diff > trigger_threshold

    # send framebuffer to ide (not working atm)
    # print(extra_fb.compressed_for_ide(), end="")

    # detect blobs here and update extra_fb to use img for debug output
    blobs = extra_fb.find_blobs([blob_threshold], pixels_threshold=pixels_threshold, area_threshold=area_threshold, merge=True)
    extra_fb.replace(img)

    # update blobs
    update_tracking(blobs, moving_objects)

    # trigger if necessary
    trigger_movement(moving_objects)

    # display blobs debug info
    if show_debug:
        # show tracked mo's
        img.draw_string(20, 20, "MO:%s" % (len(moving_objects)), scale=2, color=debug_color)

        # show blobs and distance
        for mo in moving_objects:
            img.draw_arrow(mo.start_position[0], mo.start_position[1], mo.blob.cx(), mo.blob.cy())
            img.draw_string(mo.blob.cx(), mo.blob.cy(), "%s" % (mo.moved_distance()))

            img.draw_rectangle(mo.blob.rect())
            img.draw_cross(mo.blob.cx(), mo.blob.cy())


    # update framebuffer
    last_frame_triggered = triggered
