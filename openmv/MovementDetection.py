# Movement Detection
# bildspur 2018

import sensor, image, pyb, os, time, math

sensor.reset()                      # Reset and initialize the sensor.
sensor.set_pixformat(sensor.GRAYSCALE) # Set pixel format to RGB565 (or GRAYSCALE)
sensor.set_framesize(sensor.QVGA)   # Set frame size to QVGA (320x240)
sensor.skip_frames(time = 500)     # Wait for settings take effect.
sensor.set_auto_whitebal(True)
clock = time.clock()                # Create a clock object to track the FPS.

# variables
trigger_threshold = 5
extra_fb = sensor.alloc_extra_fb(sensor.width(), sensor.height(), sensor.GRAYSCALE)

# blob detection
blob_threshold = (5, 255)
pixels_threshold = 250
area_threshold = 5000

# tracking
tracking_distance_threshold = 150
tracking_area_threshold = 100000 # remove tracking area as distinguisher
moving_objects = []
last_frame_triggered = False

sensor.skip_frames(time = 2000) # Give the user time to get ready.
extra_fb.replace(sensor.snapshot())

def distance(p1, p2):
    return math.sqrt(((p1[0]-p2[0])**2)+((p1[1]-p2[1])**2))

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
                continue

        # add to list if not used
        if not is_used:
            moving_objects.append(MovingObject(blob))

    # filter not updated and dead objects
    alive_mos = [mo for mo in moving_objects if mo.updated and not mo.is_dead]

    moving_objects.clear()
    for mo in alive_mos:
        moving_objects.append(mo)


class MovingObject:
    def __init__(self, blob):
        self.blob = blob
        self.has_triggered = False
        self.is_dead = False
        self.life = 1
        self.updated = True

    def check_match(self, blob, distance_threshold, area_threshold):
        d = distance([blob.cx(), blob.cy()], [self.blob.cx(), self.blob.cy()])
        a = abs(blob.area() - self.blob.area())

        # print("D: %s\tA: %s" % (d, a))

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

    hist = extra_fb.get_histogram()
    # This code below works by comparing the 99th percentile value (e.g. the
    # non-outlier max value against the 90th percentile value (e.g. a non-max
    # value. The difference between the two values will grow as the difference
    # image seems more pixels change.
    diff = hist.get_percentile(0.99).l_value() - hist.get_percentile(0.90).l_value()
    triggered = diff > trigger_threshold

    # send framebuffer to ide
    # print(extra_fb.compressed_for_ide(), end="")

    # detect blobs here and update extra_fb to use img for debug output
    blobs = extra_fb.find_blobs([blob_threshold], pixels_threshold=pixels_threshold, area_threshold=area_threshold, merge=True)
    extra_fb.replace(img)

    # update blobs
    update_tracking(blobs, moving_objects)
    print("MO's: %s" % (len(moving_objects)))

    if(len(moving_objects) > 0):
        print("first: updated = %s, life = %s" % (moving_objects[0].is_dead, moving_objects[0].life))

    # find direction by blob detection
    if(triggered):
        for blob in blobs:
            img.draw_rectangle(blob.rect())
            img.draw_cross(blob.cx(), blob.cy())

            # send trigger with position
            # print("%s: %s | %s (%s)" % (clock.fps(), blob.cx(), blob.cy(), blob.area()))


    # update framebuffer
    last_frame_triggered = triggered
