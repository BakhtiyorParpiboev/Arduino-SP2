
#include <Servo.h>
#define PIN_SERVO 10

Servo myServo; 
unsigned long MOVING_TIME = 1000; 
unsigned long moveStartTime;
int startAngle = 30;
int stopAngle = 90;
bool movingForward = true;

float sigmoid(float x) {
  return 1 / (1 + exp(-x));
}

void setup() {
  myServo.attach(PIN_SERVO); 
  moveStartTime = millis();

  myServo.write(startAngle); 
  delay(500); 
}

void loop() {
  unsigned long progress = millis() - moveStartTime;

  if (progress <= MOVING_TIME) {
    float normalizedProgress = (float)progress / MOVING_TIME;
    float sigmoidValue = sigmoid(normalizedProgress * 12 - 6);

    int angle;
    if (movingForward) {
      angle = startAngle + sigmoidValue * (stopAngle - startAngle);
    } else {
      angle = stopAngle + sigmoidValue * (startAngle - stopAngle);
    }
    myServo.write(angle);
  } else {
    movingForward = !movingForward;
    moveStartTime = millis();
  }
}
