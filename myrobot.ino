#include <Ps3Controller.h>
#include "FastTrig.h"

// Motor FL
int flPin1 = 13;
int flPin2 = 14;
int enableFlPin = 12;

// Motor FR
int frPin1 = 18;
int frPin2 = 17;
int enableFrPin = 16;

// Motor RL
int rlPin1 = 33;
int rlPin2 = 32;
int enableRlPin = 15;

// Motor RR
int rrPin1 = 27;
int rrPin2 = 26;
int enableRrPin = 25;

// Setting PWM properties
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 200;
int wheelSpeed = 230;

const float sticksens = 5.0;
const float RAD2DEG = 180.0f / PI;

void stop() {
  digitalWrite(frPin2, LOW);
  digitalWrite(frPin1, LOW);

  digitalWrite(flPin2, LOW);
  digitalWrite(flPin1, LOW);

  digitalWrite(rrPin2, LOW);
  digitalWrite(rrPin1, LOW);

  digitalWrite(rlPin2, LOW);
  digitalWrite(rlPin1, LOW);
}

void moveForward() {
  digitalWrite(frPin2, HIGH);
  digitalWrite(frPin1, LOW);

  digitalWrite(flPin2, HIGH);
  digitalWrite(flPin1, LOW);

  digitalWrite(rrPin2, HIGH);
  digitalWrite(rrPin1, LOW);

  digitalWrite(rlPin2, HIGH);
  digitalWrite(rlPin1, LOW);
}

void moveBackward() {
  digitalWrite(frPin2, LOW);
  digitalWrite(frPin1, HIGH);

  digitalWrite(flPin2, LOW);
  digitalWrite(flPin1, HIGH);

  digitalWrite(rrPin2, LOW);
  digitalWrite(rrPin1, HIGH);

  digitalWrite(rlPin2, LOW);
  digitalWrite(rlPin1, HIGH);
}

void strafeRight() {
  digitalWrite(frPin2, HIGH);
  digitalWrite(frPin1, LOW);

  digitalWrite(flPin2, LOW);
  digitalWrite(flPin1, HIGH);

  digitalWrite(rrPin2, LOW);
  digitalWrite(rrPin1, HIGH);

  digitalWrite(rlPin2, HIGH);
  digitalWrite(rlPin1, LOW);
}

void strafeLeft() {
  digitalWrite(frPin2, LOW);
  digitalWrite(frPin1, HIGH);

  digitalWrite(flPin2, HIGH);
  digitalWrite(flPin1, LOW);

  digitalWrite(rrPin2, HIGH);
  digitalWrite(rrPin1, LOW);

  digitalWrite(rlPin2, LOW);
  digitalWrite(rlPin1, HIGH);
}

void moveDiagUpLeft() {
  digitalWrite(frPin2, HIGH);
  digitalWrite(frPin1, LOW);

  digitalWrite(flPin2, LOW);
  digitalWrite(flPin1, LOW);

  digitalWrite(rrPin2, LOW);
  digitalWrite(rrPin1, LOW);

  digitalWrite(rlPin2, HIGH);
  digitalWrite(rlPin1, LOW);
}

void moveDiagUpRight() {
  digitalWrite(frPin2, LOW);
  digitalWrite(frPin1, LOW);

  digitalWrite(flPin2, HIGH);
  digitalWrite(flPin1, LOW);

  digitalWrite(rrPin2, HIGH);
  digitalWrite(rrPin1, LOW);

  digitalWrite(rlPin2, LOW);
  digitalWrite(rlPin1, LOW);
}

void moveDiagDownLeft() {
  digitalWrite(frPin2, LOW);
  digitalWrite(frPin1, LOW);

  digitalWrite(flPin2, LOW);
  digitalWrite(flPin1, HIGH);

  digitalWrite(rrPin2, LOW);
  digitalWrite(rrPin1, HIGH);

  digitalWrite(rlPin2, LOW);
  digitalWrite(rlPin1, LOW);
}

void moveDiagDownRight() {
  digitalWrite(frPin2, LOW);
  digitalWrite(frPin1, HIGH);

  digitalWrite(flPin2, LOW);
  digitalWrite(flPin1, LOW);

  digitalWrite(rrPin2, LOW);
  digitalWrite(rrPin1, LOW);

  digitalWrite(rlPin2, LOW);
  digitalWrite(rlPin1, HIGH);
}

void moveCw() {
  digitalWrite(frPin2, LOW);
  digitalWrite(frPin1, HIGH);

  digitalWrite(flPin2, HIGH);
  digitalWrite(flPin1, LOW);

  digitalWrite(rrPin2, LOW);
  digitalWrite(rrPin1, HIGH);

  digitalWrite(rlPin2, HIGH);
  digitalWrite(rlPin1, LOW);
}

void moveCcw() {
  digitalWrite(frPin2, HIGH);
  digitalWrite(frPin1, LOW);

  digitalWrite(flPin2, LOW);
  digitalWrite(flPin1, HIGH);

  digitalWrite(rrPin2, HIGH);
  digitalWrite(rrPin1, LOW);

  digitalWrite(rlPin2, LOW);
  digitalWrite(rlPin1, HIGH);
}

void decreaseSpeed() {
  wheelSpeed -= 5;
  if (wheelSpeed < 200) {
    wheelSpeed = 200;
  }
  ledcWrite(enableFrPin, wheelSpeed);
  ledcWrite(enableFlPin, wheelSpeed);
  ledcWrite(enableRrPin, wheelSpeed);
  ledcWrite(enableRlPin, wheelSpeed);
}

void increaseSpeed() {
  wheelSpeed += 5;
  if (wheelSpeed > 255) {
    wheelSpeed = 255;
  }
  ledcWrite(enableFrPin, wheelSpeed);
  ledcWrite(enableFlPin, wheelSpeed);
  ledcWrite(enableRrPin, wheelSpeed);
  ledcWrite(enableRlPin, wheelSpeed);
}

void onConnect() {
  Serial.println("Connected.");
}

void notify() {
  //do robot movements here
  if (Ps3.data.button.cross) {
    Serial.println("Pressing the cross button");
  }

  if (Ps3.data.button.square) {
    Serial.println("Pressing the square button");
  }

  if (Ps3.data.button.triangle) {
    Serial.println("Pressing the triangle button");
  }

  if (Ps3.data.button.circle) {
    Serial.println("Pressing the circle button");
  }

  if (Ps3.event.button_up.up || Ps3.event.button_up.down || Ps3.event.button_up.left || Ps3.event.button_up.right || Ps3.event.button_up.r2 || Ps3.event.button_up.l2) {
    Serial.println("Released a movement button");
    stop();
  }

  if (Ps3.event.button_down.up) {
    moveForward();
  }
  if (Ps3.event.button_down.down) {
    moveBackward();
  }
  if (Ps3.event.button_down.left) {
    strafeLeft();
  }
  if (Ps3.event.button_down.right) {
    strafeRight();
  }
  if (Ps3.event.button_down.l2) {
    moveCcw();
  }
  if (Ps3.event.button_down.r2) {
    moveCw();
  }

  if (Ps3.event.button_up.l1) {
    Serial.println("decrease speed");
    decreaseSpeed();
  }
  if (Ps3.event.button_up.r1) {
    Serial.println("increase speed");
    increaseSpeed();
  }

  /*if (abs(Ps3.event.analog_changed.stick.rx) + abs(Ps3.event.analog_changed.stick.ry) > 2) {

    int x = abs(Ps3.data.analog.stick.rx);
    int y = abs(Ps3.data.analog.stick.ry);
    double distance = sqrt((x * x) + (y * y));
    Serial.println(distance);

    float angleRadian = atan2Fast(Ps3.data.analog.stick.ry, Ps3.data.analog.stick.rx);
    float angle = angleRadian * RAD2DEG;
    if (angle < 0) {
      angle += 360;
    }

    if (distance < 15) {
      Serial.println("stick centered");
      stop();
    } else {
      Serial.println("stick moved");
      if (angle < (45.0 + sticksens) && angle > (45.0 - sticksens)) {
        moveDiagDownLeft();
      }
      if (angle < (135.0 + sticksens) && angle > (135.0 - sticksens)) {
        moveDiagDownRight();
      }

      if (angle < (225.0 + sticksens) && angle > (225.0 - sticksens)) {
        moveDiagUpRight();
      }

      if (angle < (315.0 + sticksens) && angle > (315.0 - sticksens)) {
        moveDiagUpLeft();
      }
    }
  }*/
}

void setup() {

  Serial.begin(115200);


  // sets the pins as outputs:
  pinMode(frPin1, OUTPUT);
  pinMode(frPin2, OUTPUT);
  pinMode(enableFrPin, OUTPUT);

  pinMode(flPin1, OUTPUT);
  pinMode(flPin2, OUTPUT);
  pinMode(enableFlPin, OUTPUT);

  pinMode(rrPin1, OUTPUT);
  pinMode(rrPin2, OUTPUT);
  pinMode(enableRrPin, OUTPUT);

  pinMode(rlPin1, OUTPUT);
  pinMode(rlPin2, OUTPUT);
  pinMode(enableRlPin, OUTPUT);

  // configure LEDC PWM
  ledcAttachChannel(enableFrPin, freq, resolution, 0);
  ledcAttachChannel(enableFlPin, freq, resolution, 1);
  ledcAttachChannel(enableRrPin, freq, resolution, 4);
  ledcAttachChannel(enableRlPin, freq, resolution, 6);
  

  /*ledcAttach(enableFrPin, freq, resolution);
  ledcAttach(enableFlPin, freq, resolution);
  ledcAttach(enableRrPin, freq, resolution);
  ledcAttach(enableRlPin, freq, resolution);*/

  ledcWrite(enableFrPin, wheelSpeed);
  ledcWrite(enableFlPin, wheelSpeed);
  ledcWrite(enableRrPin, wheelSpeed);
  ledcWrite(enableRlPin, wheelSpeed);

  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
  Ps3.begin("cc:db:a7:62:8e:1e");
  // testing
  Serial.print("Robot initialized !");
}

void loop() {

}
