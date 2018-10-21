class Luboid
{
  float EASING_SPEED = 0.1;

  int id;
  EasingValue brightness = new EasingValue(0.0, EASING_SPEED);

  float x = 0;
  float y = 0;

  public Luboid(int id)
  {
    this.id = id;
  }

  void update()
  {
    brightness.update();
  }

  void turnOff()
  {
    brightness.setTarget(MIN_BRIGHTNESS);
  }

  void turnOn()
  {
    brightness.setTarget(MAX_BRIGHTNESS);
  }
}
