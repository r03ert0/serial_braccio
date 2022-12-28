
/*
  serial_braccio.ino

 Control Braccio using serial commands

 Created on 28 Nov 2022
 by Roberto Toro
 */

#include <Braccio.h>
#include <Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

int m0 = 20; // delay, allowed values from 10 to 30 msec.
int m1 = 0; // base degrees. Allowed values from 0 to 180 degrees.
int m2 = 15; // shoulder degrees. Allowed values from 15 to 165 degrees.
int m3 = 180; // elbow degrees. Allowed values from 0 to 180 degrees.
int m4 = 170; // wrist vertical degrees. Allowed values from 0 to 180 degrees.
int m5 = 0; // wrist rotation degrees. Allowed values from 0 to 180 degrees.
int m6 = 73; // gripper degrees. Allowed values from 10 to 73 degrees. 10: the toungue is open, 73: the gripper is closed.
  
void setup() {
  Braccio.begin();

  Serial.begin(9600);
  while(!Serial);
  Serial.println("Ready");

  Braccio.ServoMovement(m0, m1, m2, m3, m4, m5, m6);
}

void loop() {
  char LF = 10;

  if (Serial.available()) {
    String msg = Serial.readStringUntil(LF);

    if (msg != 0) {
      Serial.println(msg);
    }

    if(msg.startsWith("m")) {
      String num = String(msg[1]);
      Serial.println("Part number " + num);
      String val = msg.substring(3);
      Serial.println("Value " + val);
      if (num.startsWith("0")) m0 = val.toInt();
      if (num.startsWith("1")) m1 = val.toInt();
      if (num.startsWith("2")) m2 = val.toInt();
      if (num.startsWith("3")) m3 = val.toInt();
      if (num.startsWith("4")) m4 = val.toInt();
      if (num.startsWith("5")) m5 = val.toInt();
      if (num.startsWith("6")) m6 = val.toInt();
      Braccio.ServoMovement(m0, m1, m2, m3, m4, m5, m6);
    }
  }
}
