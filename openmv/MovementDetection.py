# Movement Detection
# bildspur 2018

import sensor, image, pyb, os, time

TRIGGER_THRESHOLD = 5

sensor.reset()                      # Reset and initialize the sensor.
sensor.set_pixformat(sensor.GRAYSCALE) # Set pixel format to RGB565 (or GRAYSCALE)
sensor.set_framesize(sensor.QVGA)   # Set frame size to QVGA (320x240)
sensor.skip_frames(time = 2000)     # Wait for settings take effect.
sensor.set_auto_whitebal(True)
clock = time.clock()                # Create a clock object to track the FPS.

extra_fb = sensor.alloc_extra_fb(sensor.width(), sensor.height(), sensor.GRAYSCALE)

sensor.skip_frames(time = 2000) # Give the user time to get ready.
extra_fb.replace(sensor.snapshot())

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
    triggered = diff > TRIGGER_THRESHOLD

    print(clock.fps(), triggered) # Note: Your OpenMV Cam runs about half as fast while
    # connected to your computer. The FPS should increase once disconnected.

    # send framebuffer to ide
    # print(extra_fb.compressed_for_ide(), end="")

    # find direction
    if(triggered):
        # detect blob an calculate new position
        print("triggered")


    # update framebuffer
    extra_fb.replace(img)
