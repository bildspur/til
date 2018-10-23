class TimeStarPattern
{
  float RANDOM_ON_FACTOR = 0.95;

  long minDuration = 5000;
  long maxDuration = 20000;

  float minBrightness = 0.2f;
  float maxBrightness = 0.5f;

  TimeStar[] stars;

  void setup()
  {
    // init stars
    stars = new TimeStar[luboids.length];
    for (int i = 0; i < stars.length; i++)
    {
      stars[i] = new TimeStar();
    }
  }

  void update()
  {
    long timeStamp = millis();

    // rnd stars
    for (int i = 0; i < stars.length; i++)
    {
      TimeStar star = stars[i];
      if (!star.isRunning(timeStamp) && isRandomCalled(RANDOM_ON_FACTOR))
        star.start(timeStamp, (long)round(random(minDuration, maxDuration)));

      // update
      float brightness = star.getBrightness(timeStamp);
      float clampedBrightness = map(brightness, MIN_BRIGHTNESS, MAX_BRIGHTNESS, minBrightness, maxBrightness);
      luboids[i].brightness.setTarget(clampedBrightness);
    }
  }

  void turnOn(TimeStar star)
  {
  }

  boolean isRandomCalled(float factor) {
    return (random(0, 1000) / 1000.0) > factor;
  }
}
