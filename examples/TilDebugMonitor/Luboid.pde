class Luboid
{
  int id;
  int brightness = 0;
  int dmxAddress;

  float x = 0;
  float y = 0;

  float width = 0;
  float height = 7.5f;

  boolean isOn = false;

  public Luboid(int id, int dmxAddress, float width, float x, float y)
  {
    this.id = id;
    this.x = x;
    this.y = y;
    this.dmxAddress = dmxAddress;
    this.width = width;
  }

  boolean isInside(PVector v)
  { 
    return (v.x >= x && v.x <= (x + width))
      && (v.y >= y && v.y <= (y + height));
  }
}
