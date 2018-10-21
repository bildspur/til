float MAX_BRIGHTNESS = 1.0f;
float MIN_BRIGHTNESS = 0.0f;

Luboid[] luboids = new Luboid[10];

StarPattern star = new StarPattern();
WavePattern wave = new WavePattern();

int rectWidth = 40;
int rectHeight = 15;
int luboidSpace = 20;

int padding = 50;

void setup()
{
  frameRate(40);
  size(1024, 400, FX2D);

  for (int i = 0; i < luboids.length; i++)
  {
    Luboid l = new Luboid(i);
    l.y = round(random(padding, height - (padding + rectHeight)));
    l.x = ((width - (padding + rectWidth)) / (float)luboids.length) * i;

    luboids[i] = l;
  }
}

void draw()
{
  background(0);

  star.update();
  wave.update();

  updateLuboids();

  renderLights();
}

void updateLuboids()
{
  for (Luboid l : luboids)
  {
    // update luboids (for brightness);
    l.update();
  }
}

void renderLights()
{
  pushMatrix();
  translate(padding, padding);

  for (Luboid l : luboids)
  {
    int id = l.id;
    int brightness = round(map(l.brightness.get(), MIN_BRIGHTNESS, MAX_BRIGHTNESS, 0, 255));

    stroke(255);
    fill(brightness);
    rect(l.x, l.y, rectWidth, rectHeight);
  }
  popMatrix();
}

void keyPressed()
{
  println("send wave!");
}