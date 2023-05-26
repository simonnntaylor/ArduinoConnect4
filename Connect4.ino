/*
 * Simon Taylor
 * the date
 * this is a project
*/

//define the segments for Seven Segment Display
  #define segA 1
  #define segB 2
  #define segC 3
  #define segD 4
  #define segE 5
  #define segF 6
  #define segG 7

//define the displays for Seven Segment Display
  #define display1 22
  #define display2 23
  #define display3 24
  #define display4 25

//define the player LED indicators
  #define player1LED 28
  #define player2LED 29

//define the matrix pins
  #define matrixCLK 30
  #define matrixCS 31
  #define matrixDIN 32

//define the joystick pins
  #define joystickSEL 12
  #define joystickHORX A1
  #define joystickVERT A2


void segDisplay(int display, int seg) {
  //display numbers on a seven segment display
  //takes an int that is which display is being outputted and the num to output
  //only works for me in this class

  switch (display) {
    case 1:
      digitalWrite(display1, HIGH);
      break;
    case 2:
      digitalWrite(display2, HIGH);
      break;
    case 3:
      digitalWrite(display3, HIGH);
      break;
    case 4:
      digitalWrite(display4, HIGH);
      break;
  }


  switch (seg) {
    case 0:
      digitalWrite(segA, LOW);
      digitalWrite(segB, LOW);
      digitalWrite(segC, LOW);
      digitalWrite(segD, LOW);
      digitalWrite(segE, LOW);
      digitalWrite(segF, LOW);
      break;
    case 1:
      digitalWrite(segB, LOW);
      digitalWrite(segC, LOW);
      break;
    case 2:
      digitalWrite(segA, LOW);
      digitalWrite(segB, LOW);
      digitalWrite(segG, LOW);
      digitalWrite(segE, LOW);
      digitalWrite(segD, LOW);
      break;
    case 3:
      digitalWrite(segA, LOW);
      digitalWrite(segB, LOW);
      digitalWrite(segG, LOW);
      digitalWrite(segC, LOW);
      digitalWrite(segD, LOW);
      break;
    case 4:
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      digitalWrite(segB, LOW);
      digitalWrite(segC, LOW);
      break;
    case 5:
      digitalWrite(segA, LOW);
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      digitalWrite(segC, LOW);
      digitalWrite(segD, LOW);
      break;
    case 6:
      digitalWrite(segA, LOW);
      digitalWrite(segF, LOW);
      digitalWrite(segE, LOW);
      digitalWrite(segD, LOW);
      digitalWrite(segC, LOW);
      digitalWrite(segG, LOW);
      break;
    case 7:
      digitalWrite(segA, LOW);
      digitalWrite(segB, LOW);
      digitalWrite(segC, LOW);
      break;
    case 8:
      digitalWrite(segA, LOW);
      digitalWrite(segB, LOW);
      digitalWrite(segC, LOW);
      digitalWrite(segD, LOW);
      digitalWrite(segE, LOW);
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      break;
    case 9:
      digitalWrite(segA, LOW);
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      digitalWrite(segB, LOW);
      digitalWrite(segC, LOW);
      break;
  }
}


void setup() {
  // put your setup code here, to run once:
  pinMode(28, OUTPUT);
  pinMode(29, OUTPUT);
  for (int i = 22; i <= 25; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  for (int j = 1; j <= 7; j++) {
    pinMode(j, OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(28, HIGH);
  digitalWrite(29, HIGH);

  for (int j = 1; j <= 7; j++) {
    digitalWrite(j, LOW);
  }

  delay(1000);


  digitalWrite(28, LOW);
  digitalWrite(29, LOW);

  for (int j = 1; j <= 7; j++) {
    digitalWrite(j, HIGH);
  }

  delay(1000);
}
