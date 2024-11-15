#include <Streaming.h>
#include <Servo.h>

Servo servo;

void ServoSpin(int startAngle, int endAngle, int direction) //spinDirection should be 1 or -1
{
  servo.write(startAngle);
  delay(500);
  for (int i = startAngle; i * direction <= endAngle; i += direction) servo.write(i);
  delay(500);
}

void setup()
{
  //Circle* circle1 = new Circle();
  Serial.begin(115200);
  Serial << endl << "Hello World!" << endl;
  servo.attach(D3, 500, 2400);
  pinMode(D4, INPUT_PULLUP);
  //Serial << circle1->r << endl;
}

int button = 0;

void loop()
{
  if (digitalRead(D4) == 0)
  {
    button = abs(button - 1);
    if (button) ServoSpin(180, 0, -1);
    else ServoSpin(0, 180, 1);
  }
}
