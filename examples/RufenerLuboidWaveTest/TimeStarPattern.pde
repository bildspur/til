class TimeStarPattern
{
  float RANDOM_ON_FACTOR = 0.95;
  float RANDOM_OFF_FACTOR = 0.9;

  void update()
  {
    for (Luboid luboid : luboids)
    {
      // check if leaf is on
      if (luboid.brightness.get() > 0.75)
      {
        if (isRandomCalled(RANDOM_OFF_FACTOR))
          luboid.turnOff();
      } else
      {
        if (isRandomCalled(RANDOM_ON_FACTOR))
          luboid.brightness.setTarget(random(50, 100) / 100.0);
      }
    }
  }

  boolean isRandomCalled(float factor) {
    return (random(0, 1000) / 1000.0) > factor;
  }
}
