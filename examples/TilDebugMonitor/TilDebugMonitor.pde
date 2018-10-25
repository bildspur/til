Luboid[] luboids = new Luboid[] {
  new Luboid(0, 0, 50, 601, 9), 
  new Luboid(1, 4, 30, 534, 9), 
  new Luboid(2, 8, 30, 508, 8), 
  new Luboid(3, 12, 40, 439, 10), 
  new Luboid(4, 16, 50, 410, 8), 
  new Luboid(5, 20, 30, 365, 7), 
  new Luboid(6, 24, 40, 314, 9), 
  new Luboid(7, 28, 30, 279, 7), 
  new Luboid(8, 32, 50, 238, 10), 
  new Luboid(9, 36, 30, 248, 8), 
  new Luboid(10, 40, 50, 221, 6), 
  new Luboid(11, 44, 40, 186, 8), 
  new Luboid(12, 48, 30, 193, 2), 
  new Luboid(13, 52, 30, 184, 5), 
  new Luboid(14, 56, 40, 156, 7), 
  new Luboid(15, 60, 30, 152, 9), 
  new Luboid(16, 64, 30, 145, 2), 
  new Luboid(17, 68, 30, 138, 10), 
  new Luboid(18, 72, 50, 116, 1), 
  new Luboid(19, 76, 50, 115, 3), 
  new Luboid(20, 80, 30, 133, 5), 
  new Luboid(21, 84, 50, 110, 6), 
  new Luboid(22, 88, 30, 110, 7), 
  new Luboid(23, 92, 50, 82, 8), 
  new Luboid(24, 96, 30, 97, 2), 
  new Luboid(25, 100, 30, 96, 10), 
  new Luboid(26, 104, 30, 82, 5), 
  new Luboid(27, 108, 50, 62, 9), 
  new Luboid(28, 112, 40, 63, 3), 
  new Luboid(29, 116, 40, 54, 7), 
  new Luboid(30, 120, 30, 62, 6), 
  new Luboid(31, 124, 40, 40, 4), 
  new Luboid(32, 128, 40, 23, 5), 
};

int levels = 10;
int padding = 50;

void setup()
{
  frameRate(60);
  size(800, 400, FX2D);

  // fix luboids sizes
  for (Luboid luboid : luboids)
  {
    luboid.y = map(luboid.y, 1, levels, height - padding, 0 + padding);
  }
}

void draw()
{
  background(0);
  renderLights();
  showLuboidInformation();
}

void showLuboidInformation()
{
  PVector mouse = new PVector(mouseX, mouseY);
  PVector transMouse = new PVector(mouse.x, mouse.y);

  cursor(ARROW);

  Luboid luboid = findLuboidByPositon(transMouse);
  if (luboid == null)
    return;

  luboid.isOn = true;

  // display info
  pushMatrix();
  translate(mouse.x + 20, mouse.y + 20);
  noStroke();
  fill(255, 0, 0, 100);
  rect(-5, -20, 75, 75);

  fill(255);
  textSize(12);
  text("Luboid #" + luboid.id 
    + "\nDMX: " + luboid.dmxAddress
    + "\nB: " + luboid.brightness, 
    0, 0);
  popMatrix();

  cursor(HAND);
}

Luboid findLuboidByPositon(PVector pos)
{
  for (Luboid luboid : luboids)
  {
    if (luboid.isInside(pos))
      return luboid;
  }
  return null;
}

void renderLights()
{
  pushMatrix();
  //translate(padding, padding);

  for (Luboid l : luboids)
  {
    int brightness = l.brightness;


    stroke(100);
    strokeWeight(1.0f);

    if (l.isOn)
    {
      stroke(0, 255, 0);
      strokeWeight(2.0f);
      l.isOn = false;
    }

    fill(brightness);
    rect(l.x, l.y, l.width, l.height);
  }
  popMatrix();
}
