# Untitled - By: cansik - Mon Oct 8 2018

import sensor, image, time

sensor.reset()
sensor.set_pixformat(sensor.GRAYSCALE)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 500)

clock = time.clock()

blob_threshold = (230, 255)

while(True):
    clock.tick()
    img = sensor.snapshot()
    blobs = img.find_blobs([blob_threshold], pixels_threshold=100, area_threshold=100, merge=True)

    for blob in blobs:
        img.draw_rectangle(blob.rect())
        img.draw_cross(blob.cx(), blob.cy())

    print(clock.fps())

