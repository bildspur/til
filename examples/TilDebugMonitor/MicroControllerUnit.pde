import processing.serial.*;

class MicroControllerUnit
{
  String portName;
  Serial port;

  PApplet parent;

  public MicroControllerUnit(PApplet parent, String portName)
  {
    this.portName = portName;
    this.parent = parent;
  }

  public boolean isAttached()
  {
    return mcu.port != null;
  }

  public void attach()
  {
    try
    {
      port = new Serial(parent, portName, 115200);
    }
    catch(Exception ex)
    {
      println("Serial Error: " + ex.getMessage());
    }
  }

  public String readData()
  {
    if ( port.available() > 0) 
      return port.readStringUntil('\n');
    return null;
  }

  public void detach()
  {
    port.stop();
    port = null;
  }
}
