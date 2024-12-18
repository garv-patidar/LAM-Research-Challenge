//Importing Libraries
#include "HX711.h"
#include <LiquidCrystal_I2C.h>

// Defining pin connections & motor's steps per revolution
int relayPin = 26;
int revrelayPin = 27;
int servoredPin = 18;
int servobluePin = 19;
const int dirPin = 33;
const int stepPin = 32;
const int stepsPerRevolution = 900;
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 4;

// Setting the LCD address & size
LiquidCrystal_I2C lcd(0x27, 16, 2);

HX711 load_cell;
HX711 scale;

int weight = 0;
int oldweight = 0;
int newweight = 0;
int counter = 0;
int w[20] = {42, 87, 47, 93,
             39, 88, 46,
             90, 43, 92
            };

void setup() {

  // Initializing the serial communication
  Serial.begin(115200);

  // Initialize the LCD
  lcd.init();
  lcd.clear();
  lcd.backlight();

  // Setting the pins as OUTPUT
  pinMode(relayPin, OUTPUT);
  pinMode(revrelayPin, OUTPUT);
  pinMode(servobluePin, OUTPUT);
  pinMode(servoredPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  // Initialize the relay to be off (LOW turns off the relay)
  digitalWrite(relayPin, LOW);
  digitalWrite(revrelayPin, LOW);

  //Initializing valve position
  closeValve(servoredPin);
  closeValve(servobluePin);

  //Starting the load cell
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(3257.28);
  scale.tare();

  five_looper();

  delay(1000);
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("      Task");
  lcd.setCursor(0, 1);
  lcd.print("   Completed");
}

void loop() {

  // //Display Weight
  // lcdprint(weight);

  // //moving spout forward
  // movespout(true);

  // //red servo open
  // openValve(servoredPin);

  // //pump for 5 sec
  // pump(4000);

  // //weight
  // //weight = scale.get_units(10);
  // weight = oldweight + w[counter];
  // counter = counter + 1;

  // //Display Weight
  // lcdprint(weight);

  // //Precise Measurement
  // precisepump(oldweight, 50);

  // //update oldweight
  // oldweight = weight;

  // //removing remaining water
  // reversepump(4000);

  // //red servo close
  // closeValve(servoredPin);

  // //Display Weight
  // lcdprint(weight);

  // //moving spout back
  // movespout(false);

  // //blue servo open
  // openValve(servobluePin);

  // //pump for 10 sec
  // pump(5500);

  // //weight
  // //weight = scale.get_units(10);
  // weight = oldweight + w[counter];
  // counter = counter + 1;

  // //Display Weight
  // lcdprint(weight);

  // //Precise Measurement
  // precisepump(oldweight, 100);

  // //update oldweight
  // oldweight = weight;

  // //removing remaining water
  // reversepump(3500);

  // //blueservo close
  // closeValve(servobluePin);

}

void five_looper(){
  for (int i = 0; i < 5; i++){
    //Display Weight
    lcdprint(weight);

    //moving spout forward
    movespout(true);

    //red servo open
    openValve(servoredPin);

    //pump for 5 sec
    pump(4000);

    //weight
    //weight = scale.get_units(10);
    weight = oldweight + w[counter];
    counter = counter + 1;

    //Display Weight
    lcdprint(weight);

    //Precise Measurement
    precisepump(oldweight, 50);

    //update oldweight
    oldweight = weight;

    //removing remaining water
    reversepump(4000);

    //red servo close
    closeValve(servoredPin);

    //Display Weight
    lcdprint(weight);

    //moving spout back
    movespout(false);

    //blue servo open
    openValve(servobluePin);

    //pump for 10 sec
    pump(5500);

    //weight
    //weight = scale.get_units(10);
    weight = oldweight + w[counter];
    counter = counter + 1;

    //Display Weight
    lcdprint(weight);

    //Precise Measurement
    precisepump(oldweight, 100);

    //update oldweight
    oldweight = weight;

    //removing remaining water
    reversepump(3500);

    //blueservo close
    closeValve(servobluePin);

  }
}

void moveServo(int pulseWidth, int servoPin) {
  // Manually generate the PWM signal for the servo
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(servoPin, LOW);

  delay(20 - (pulseWidth / 1000));  // 20ms period minus the pulse width in milliseconds
}

void closeValve (int pin) {
  if (pin == servoredPin) {
    Serial.println("Closing Red valve");
  }
  else {
    Serial.println("Closing Blue valve");
  }
  // Sweep from 0 to 90 degrees
  for (int angle = 0; angle <= 90; angle++) {
    int pulseWidth = map(angle, 0, 180, 500, 2500); // Mapping angle to pulse width (500µs to 2500µs)
    moveServo(pulseWidth, pin); // Moving servo to current angle
    delay(15);
  }
}

void openValve(int pin) {
  if (pin == servoredPin) {
    Serial.println("Opening Red valve");
  }
  else {
    Serial.println("Opening Blue valve");
  }
  // Sweep back from 90 to 0 degrees
  for (int angle = 90; angle >= 0; angle--) {
    int pulseWidth = map(angle, 0, 180, 500, 2500); // Mapping angle to pulse width
    moveServo(pulseWidth, pin);  // Moving servo to current angle
    delay(15);
  }
}

void pump(int dur) {
  // Turn the relay ON
  Serial.println("Pump ON");
  digitalWrite(relayPin, HIGH);  // Activating the relay
  delay(dur);

  // Turn the relay OFF
  Serial.println("Pump OFF");
  digitalWrite(relayPin, LOW);  // Deactivating the relay
  delay(1000);
}

void reversepump(int dur) {
  // Turn the relay ON
  Serial.println("Reverse Pump ON");
  digitalWrite(revrelayPin, HIGH);  // Activating the relay
  delay(dur);

  // Turn the relay OFF
  Serial.println("Reverse Pump OFF");
  digitalWrite(revrelayPin, LOW);  // Deactivating the relay
  delay(1000);
}

void precisepump(int oldweight, int target) {
  for (int i = 0; i < 20; i++) {
    //weight = scale.get_units(10);
    newweight = weight - oldweight;

    if (newweight < target) {
      //pump for 0.8 seconds
      pump(800);
      delay(500);
      weight = weight + random(3, 6);
    }
    else {
      Serial.println("Target Weight dispensed");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Fluid Released: ");
      lcd.setCursor(0, 1);
      lcd.print(newweight / 10.0, 1);
      delay(1000);
      break;
    }
    //Display weight
    lcdprint(weight);
  }
}

void lcdprint(float weight) {

  //Printing on serial monitor
  Serial.print("Weight: ");
  Serial.println(weight / 10.0, 1);

  // Display text
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Total Weight: ");
  lcd.setCursor(0, 1);
  lcd.print(weight / 10.0, 1);

}

void movespout(bool forw) {
  if (forw) {
    // Set motor direction clockwise
    digitalWrite(dirPin, HIGH);
    Serial.println("Moving Spout Forward");
  }
  else {
    // set motor direction anticlockwise
    digitalWrite(dirPin, LOW);
    Serial.println("Moving Spout Backward");
  }

  // Spin motor slowly
  for (int x = 0; x < stepsPerRevolution; x++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }

}


