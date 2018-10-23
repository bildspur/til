class TimeStar
{
  long startTime;
  long duration;

  boolean isRunning(long timeStamp)
  {
    return timeStamp - startTime < duration;
  }

  void start(long timeStamp, long duration)
  {
    startTime = timeStamp;
    this.duration = duration;
  }

  float getBrightness(long timeStamp)
  {
    // calculate normalized time
    float nvalue = (timeStamp - startTime) / (float)duration;
    return windowedSine(nvalue);
  }

  private float windowedSine(float x)
  {
    if (x < 0.0f || x > 1.0f)
      return 0.0f;

    // calculate sine
    return 0.5 * (1 + sin(2 * PI * x - (PI / 2)));
  }
}
