class EasingValue
{
  float value;
  float target;
  float easing;

  public EasingValue()
  {
    value = 0.0;
    easing = 0.1;
  }

  public EasingValue(float value, float easing)
  {
    this.value = value;
    this.easing = easing;
  }

  void update() {
    float delta = target - value;
    value += delta * easing;
  }

  float get() {
    return value;
  }

  void set(float value) {
    this.value = value;
    this.target = value;
  }

  void setEasing(float easing) {
    this.easing = easing;
  }

  int getInt() {
    return (round(value));
  }

  void setTarget(float value) {
    target = value;
  }

  float getTarget() {
    return target;
  }

  float getEasing() {
    return easing;
  }
}
