float MAX_BRIGHTNESS = 1.0f;
float MIN_BRIGHTNESS = 0.0f;

Luboid[] luboids = new Luboid[20];

StarPattern star = new StarPattern();
TimeStarPattern timeStar = new TimeStarPattern();
WavePattern wave = new WavePattern();

int rectWidth = 40;
int rectHeight = 15;
int luboidSpace = 20;

int padding = 50;

boolean thereIsANewWave = false;

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

  timeStar.setup();
}

void draw()
{
  background(0);

  //star.update();
  //timeStar.update();
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
    float globalBrightness = map(l.brightness.get(), 0.0f, 1.0f, MIN_BRIGHTNESS, MAX_BRIGHTNESS);
    int brightness = round(map(globalBrightness, 0.0f, 1.0f, 0, 255));

    stroke(255);
    fill(brightness);
    rect(l.x, l.y, rectWidth, rectHeight);
  }
  popMatrix();
}

void keyPressed()
{
  println("send wave!");
  thereIsANewWave = true;
}
