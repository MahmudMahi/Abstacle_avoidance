#include <Servo.h>          //Servo motor library. This is standard library
#include <NewPing.h>

#define in1 5 //L298n Motor Driver pins.
#define in2 6
#define in3 10
#define in4 11

#define autoPin 7
#define manualPin 8
#define pinA 3
#define pinB 4

#define trig_pin A3 //analog input 1
#define echo_pin A2 //analog input 2

#define maximum_distance 200
boolean goesForward = false;
int distance = 100;

NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
Servo servo_motor; //our servo nam
int command; //Int to store app command state.
int Speed = 155;
int Speedsec;
int buttonState = 0;
int lastButtonState = 0;
int Turnradius = 0; //Set the radius of a turn, 0 - 255 Note:the robot will malfunction if this is higher than int Speed.
int brakeTime = 45;
int brkonoff = 1; //1 for the electronic braking system, 0 for normal.
void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  pinMode(autoPin, INPUT_PULLUP);
  pinMode(manualPin, INPUT_PULLUP);

  servo_motor.attach(9); //our servo pin

  servo_motor.write(90);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  
  Serial.begin(9600);  //Set the baud rate to your Bluetooth module.
}

void loop() {
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, HIGH);
      delay(3000);
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, LOW);
      delay(1000);
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, LOW);
      delay(3000);

if (digitalRead(autoPin)==HIGH){
      int distanceRight = 0;
      int distanceLeft = 0;
      delay(50);

      if (distance <= 20){
        Stop();
        delay(300);
        back();
        delay(400);
        Stop();
        delay(300);
        distanceRight = lookRight();
        delay(300);
        distanceLeft = lookLeft();
        delay(300);

        if (distance >= distanceLeft){
          right();
          Stop();
        }
        else{
          left();
          Stop();
        }
      }
      else{
        forward(); 
      }
        distance = readPing();
  }

    

  else if(digitalRead(manualPin)==HIGH){
      if (Serial.available() > 0) {
      command = Serial.read();
      Stop(); //Initialize with motors stoped.
      switch (command) {
        case 'F':
          forward();
          break;
        case 'B':
          back();
          break;
        case 'L':
          left();
          break;
        case 'R':
          right();
          break;
        case 'G':
          forwardleft();
          break;
        case 'I':
          forwardright();
          break;
        case 'H':
          backleft();
          break;
        case 'J':
          backright();
          break;
        case '0':
          Speed = 100;
          break;
        case '1':
          Speed = 140;
          break;
        case '2':
          Speed = 153;
          break;
        case '3':
          Speed = 165;
          break;
        case '4':
          Speed = 178;
          break;
        case '5':
          Speed = 191;
          break;
        case '6':
          Speed = 204;
          break;
        case '7':
          Speed = 216;
          break;
        case '8':
          Speed = 229;
          break;
        case '9':
          Speed = 242;
          break;
        case 'q':
          Speed = 255;
          break;
      }
      Speedsec = Turnradius;
      if (brkonoff == 1) {
        brakeOn();
      } else {
        brakeOff();
      }
    }
  }
 
}

void forward() {
  analogWrite(in1, Speed);
  analogWrite(in3, Speed);
}

void back() {
  analogWrite(in2, Speed);
  analogWrite(in4, Speed);
}

void left() {
  analogWrite(in3, Speed);
  analogWrite(in2, Speed);
}

void right() {
  analogWrite(in4, Speed);
  analogWrite(in1, Speed);
}
void forwardleft() {
  analogWrite(in1, Speedsec);
  analogWrite(in3, Speed);
}
void forwardright() {
  analogWrite(in1, Speed);
  analogWrite(in3, Speedsec);
}
void backright() {
  analogWrite(in2, Speed);
  analogWrite(in4, Speedsec);
}
void backleft() {
  analogWrite(in2, Speedsec);
  analogWrite(in4, Speed);
}

void Stop() {
  analogWrite(in1, 0);
  analogWrite(in2, 0);
  analogWrite(in3, 0);
  analogWrite(in4, 0);
}

void brakeOn() {
  //Here's the future use: an electronic braking system!
  // read the pushbutton input pin:
  buttonState = command;
  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == 'S') {
      if (lastButtonState != buttonState) {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, HIGH);
        delay(brakeTime);
        Stop();
      }
    }
    // save the current state as the last state,
    //for next time through the loop
    lastButtonState = buttonState;
  }
}
void brakeOff() {

}

// obs abstacle
int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

int lookRight(){  
      servo_motor.write(10);
      delay(500);
      int distance = readPing();
      delay(100);
      servo_motor.write(90);
      return distance;
    }

    int lookLeft(){
      servo_motor.write(170);
      delay(500);
      int distance = readPing();
      delay(100);
      servo_motor.write(90);
      return distance;
      delay(100);
    }
