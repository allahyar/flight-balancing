#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);
int speed = 0;

void setup() {
  Serial.begin(9600);

  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
}
int angleToPwm(int angle) {
  return map(angle + speed , 0, 90 , 0, 205);
}
void loop() {

  if (Serial.available()) {
    speed = Serial.read();
  }

  mpu6050.update();

  float angleX = mpu6050.getAngleX();
  float angleY = mpu6050.getAngleY();

  int x1 = angleToPwm(angleX > 0 ? angleX : 0);
  int x2 = angleToPwm(angleX < 0 ? abs(angleX) : 0);

  int y1 = angleToPwm(angleY > 0 ? angleY : 0);
  int y2 = angleToPwm(angleY < 0 ? abs(angleY) : 0);

  analogWrite(13, x2);
  analogWrite(12, x1);

  analogWrite(11, y2);
  analogWrite(10, y1);

  Serial.println(x1);

}
