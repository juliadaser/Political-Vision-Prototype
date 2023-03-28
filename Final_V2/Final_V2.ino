// Libraries
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_Sensor.h>

// Gyroscope
Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0();

// Keeping track of orientation of the headpiece: center, left or right
char *orientation = "center";

// Keeping track of user's location on Website
char *page_location = "normal";

// setting up our servo motors
#include <Servo.h>

Servo servo_right_1;
Servo servo_left_1;

Servo servo_right_2;
Servo servo_left_2;

int servo_right_1_attach = 2;
int servo_left_1_attach = 3;

int servo_right_2_attach = 8;
int servo_left_2_attach = 9;

int servo_right_state = 0;
int servo_left_state = 180;


// RIGHT SERVOS
// back: 0
// middle: 90
// closed: 180

// LEFT SERVOS
// back: 180
// middle: 80
// closed: 0

void setupSensor(){
  // 1.) Set the accelerometer range
  lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_2G);
  // 2.) Set the magnetometer sensitivity
  lsm.setupMag(lsm.LSM9DS0_MAGGAIN_2GAUSS);
  // 3.) Setup the gyroscope
  lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_245DPS);
}

void setup(){
#ifndef ESP8266
  while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
#endif
  Serial.begin(9600);
  Serial.println("LSM raw read demo");
  
  // Try to initialise and warn if we couldn't detect the Gyroscope
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM9DS0");
    while (1);
  }
  Serial.println("Found LSM9DS0 9DOF");
  Serial.println("");
  Serial.println("");
  Serial.println("Setting up LSM9DS0 9DOF");
  setupSensor();
  delay(1);

  //Servo Motors Prep
  servo_right_1.attach(servo_right_1_attach);
  servo_left_1.attach(servo_left_1_attach);
  servo_right_2.attach(servo_right_2_attach);
  servo_left_2.attach(servo_left_2_attach);

  // BOTH MOTORS OF EACH SIDE ARE SET TO SAME VALUE
  servo_right_1.write(servo_right_state);
  servo_right_2.write(servo_right_state);
  servo_left_1.write(servo_left_state);
  servo_left_2.write(servo_left_state);

  // Serial Comm to Website Prep
  Serial.setTimeout(10);
}

void loop(){

  // reading Gyroscope
  lsm.read();

  // Assigning Gyroscope readings to directions
  if ((int)lsm.gyroData.z > 10000){ // TURNING LEFT
    if (orientation == "center"){
      orientation = "left";
      delay(400);
      }
    if (orientation == "right"){
      orientation = "center";
      delay(400);
      }  
    }
  if ((int)lsm.gyroData.z < -10000){// TURNING RIGHT
    if (orientation == "center"){
      orientation = "right";
      delay(400);
      }
    if (orientation == "left"){
      orientation = "center";
      delay(400);
      }
    }

  Serial.println(orientation);
  

  // Serial Communication with Node: Data to Location on Website
  if (Serial.available() > 0) {
    byte input = Serial.read();

    // for normal state (no search engine)
    if (input == 'L') {
      page_location = "normal";
    }
    
    // for NewYorkTimes
    if (input == 'N') {
      page_location = "newyorktimes";
    }

    // for Google News
    if (input == 'G') { // duck duck
      page_location = "googlenews";
    }

    // for BBC & NewsWeek
    if (input == 'B') { // duck duck
      page_location = "bbcnewsweek";
    }

    // for The Wall Street Journal
    if (input == 'W') { // duck duck
      page_location = "wallstreet";
    }

    // for Fox News
    if (input == 'F') {
      page_location = "foxnews";
    }


  }
  

// Translating the visibility based on Search Engine
  // for normal state (no search engine)
  if (page_location == "normal") {
      digitalWrite(11, HIGH);
      servo_right_state = 0;
      servo_left_state = 180;
    }

  // for The New York Times (left)
  if (page_location == "newyorktimes") {
    // test LED
    digitalWrite(11, LOW);
    // Motor Code
    if(orientation == "center"){
      servo_right_state = 90;
      servo_left_state = 180;
      }

    if(orientation == "right"){
      servo_right_state = 165;
      servo_left_state = 15;
    }
    
    if(orientation == "left"){
      servo_right_state = 0;
      servo_left_state = 180;
    }
  }

// for Google News (middle left)
  if (page_location == "googlenews") {
    // test LED
    digitalWrite(11, LOW);
    // Motor Code
    if(orientation == "center"){
      servo_right_state = 50;
      servo_left_state = 180;
      }

    if(orientation == "right"){
      servo_right_state = 125;
      servo_left_state = 55;
    }
    
    if(orientation == "left"){
      servo_right_state = 0;
      servo_left_state = 180;
    }
  }

  // for BBC and The NewsWeek (neutral)
  if (page_location == "bbcnewsweek") {
      digitalWrite(11, LOW);
      servo_right_state = 90;
      servo_left_state = 90;
    }


// for The Wall Street(middle right)
  if (page_location == "wallstreet") {
    digitalWrite(11, LOW);
    // Motor Code
    if(orientation == "center"){
      servo_right_state = 0;
      servo_left_state = 120;
      }

    if(orientation == "right"){
      servo_right_state = 0;
      servo_left_state = 180;
    }
    
    if(orientation == "left"){
      servo_right_state = 125;
      servo_left_state = 55;
    }
  }



  // for Fox News (right)
  if (page_location == "foxnews") {
    digitalWrite(11, LOW);
    // Motor Code
    if(orientation == "center"){
      servo_right_state = 0;
      servo_left_state = 80;
      }

    if(orientation == "right"){
      servo_right_state = 0;
      servo_left_state = 180;
    }
    
    if(orientation == "left"){
      servo_right_state = 165;
      servo_left_state = 15;
    }
  }
    

  // write data to servos.
  servo_right_1.write(servo_right_state);
  servo_right_2.write(servo_right_state);
  servo_left_1.write(servo_left_state);
  servo_left_2.write(servo_left_state);



  delay(100);

}
