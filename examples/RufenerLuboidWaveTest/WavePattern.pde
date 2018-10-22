class WavePattern
{
  long[] waves = new long[10];
  int nextWave = 0;

  int WAVE_TIME = 3000; // seconds per wave
  int WAVE_TRAVEL_SPEED = 500;

  void update()
  {
    // check for wave
    if (thereIsANewWave)
    {
      waves[nextWave] = millis();
      nextWave = (nextWave + 1) % waves.length;

      // clean flags
      thereIsANewWave = false;
    }

    // update waves
    for (int i = 0; i < waves.length; i++)
    {
      long waveStart = waves[i];

      if (waveStart == 0)
        continue;

      // calculate timediff
      long timeDiff = millis() - waveStart;

      boolean waveIsRelevant = false;
      for (Luboid l : luboids)
      {
        if (updateLuboid(l, timeDiff))
          waveIsRelevant = true;
      }

      // check if stop wave
      if (!waveIsRelevant)
        waves[i] = 0;
    }
  }

  boolean updateLuboid(Luboid luboid, long timeDiff)
  {
    // do nothing till nmt relevant
    long ldiff = timeDiff - (luboid.id * WAVE_TRAVEL_SPEED);
    if (ldiff < 0)
      return true;

    float x = ldiff / (float)WAVE_TIME;

    if (x > 1.0)
      return false;

    float brightness = getFirstSineValue(x);
    luboid.brightness.setTarget(brightness);
    return true;
  }

  float getFirstSineValue(float x)
  {
    if (x < 0.0f || x > 1.0f)
      return 0.0f;

    // calculate sine
    return 0.5 * (1 + sin(2 * PI * x - (PI / 2)));
  }
}
