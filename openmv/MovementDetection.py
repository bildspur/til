# Movement Detection
# bildspur 2018

import sensor, image, pyb, os, time

sensor.reset()                      # Reset and initialize the sensor.
sensor.set_pixformat(sensor.GRAYSCALE) # Set pixel format to RGB565 (or GRAYSCALE)
sensor.set_framesize(sensor.QVGA)   # Set frame size to QVGA (320x240)
sensor.skip_frames(time = 2000)     # Wait for settings take effect.
sensor.set_auto_whitebal(True)
clock = time.clock()                # Create a clock object to track the FPS.

# variables
trigger_threshold = 5

# blob detection
blob_threshold = (5, 255)
pixels_threshold = 250
area_threshold = 250


last_frame_triggered = False
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
    triggered = diff > trigger_threshold

    # send framebuffer to ide
    # print(extra_fb.compressed_for_ide(), end="")

    blobs = extra_fb.find_blobs([blob_threshold], pixels_threshold=pixels_threshold, area_threshold=area_threshold, merge=True)
    extra_fb.replace(img)

    # find direction by blob detection
    if(triggered):
        for blob in blobs:
            img.draw_rectangle(blob.rect())
            img.draw_cross(blob.cx(), blob.cy())

            # send trigger with position
            print("%s: %s | %s" % (clock.fps(), blob.cx(), blob.cy()))


    # update framebuffer
    #extra_fb.replace(img)
    last_frame_triggered = triggered
