/*
**********************************************************************
* Programmer: Shivansh Khullar
* Date: Monday May 15, 2023
**********************************************************************
* Program: A traffic light and pedestrian walk cycle system that 
* controls traffic lights for two stations and a pedestrian crossing. 
* The system uses LEDs for traffic signals and pedestrian lights. 
* A button press triggers the pedestrian walk cycle, allowing the 
* pedestrian signal to be activated with feedback for crossing.
**********************************************************************
* Description: This program manages the traffic light cycle for two 
* stations, each with a red, yellow, and green LED. The system uses 
* a button to trigger a pedestrian walk cycle. When the button is pressed, 
* the pedestrian signal changes to white, and after a brief delay, 
* the pedestrian light flashes. The program uses interrupts to detect 
* the button press and initiate the pedestrian walk cycle, while keeping 
* the traffic light cycle running continuously.
**********************************************************************
* Connections:
* - Pedestrian Walk Button: pin 2
* - Pedestrian Red LED: pin 6
* - Pedestrian White LED: pin 7
* - Traffic Station 1 Red LED: pin 8
* - Traffic Station 1 Yellow LED: pin 9
* - Traffic Station 1 Green LED: pin 10
* - Traffic Station 2 Red LED: pin 11
* - Traffic Station 2 Yellow LED: pin 12
* - Traffic Station 2 Green LED: pin 13
**********************************************************************
*/

int walkRequest = 0;  // Variable for the state of the Walk Push Button
const int walkButtonPin = 2;
const int redPedestrianLED = 6;
const int whitePedestrianLED = 7;

// Setup Variables for Station 1 Traffic Light Components
const int redLight1 = 8;
const int yellowLight1 = 9;
const int greenLight1 = 10;

// Setup Variables for Station 2 Traffic Light Components
const int redLight2 = 11;
const int yellowLight2 = 12;
const int greenLight2 = 13;

// Variables that will change:
volatile int buttonState = 0;  // Variable to monitor pushbutton status

void setup() {
  // Set all LEDs as OUTPUT
  pinMode(redPedestrianLED, OUTPUT);
  pinMode(whitePedestrianLED, OUTPUT);
  pinMode(redLight1, OUTPUT);
  pinMode(yellowLight1, OUTPUT);
  pinMode(greenLight1, OUTPUT);
  pinMode(redLight2, OUTPUT);
  pinMode(yellowLight2, OUTPUT);
  pinMode(greenLight2, OUTPUT);
  pinMode(walkButtonPin, INPUT);  // Set Walk Button as INPUT

  attachInterrupt(digitalPinToInterrupt(walkButtonPin), pinISR, CHANGE);  // Watch for button press changes

  // Initialize state of all red LEDs to HIGH
  digitalWrite(redLight1, HIGH);
  digitalWrite(redLight2, HIGH);
  digitalWrite(redPedestrianLED, HIGH);
}

void loop() {
  // Station 1 Traffic Light Timing
  station1Cycle();

  if (walkRequest == 1) {  // If the Walk button has been pressed
    walkCycle();  // Exit main loop and run WalkCycle()
  }

  // Station 2 Traffic Light Timing
  station2Cycle();

  if (walkRequest == 1) {  // If the Walk button has been pressed
    walkCycle();  // Exit main loop and run WalkCycle()
  }
}

void station1Cycle() {
  delay(2500);  // 2.5 Seconds of Red
  digitalWrite(redLight1, LOW);  // Red Light OFF, Green ON
  digitalWrite(greenLight1, HIGH);
  delay(15000);  // 15 Seconds of Green
  digitalWrite(greenLight1, LOW);  // Green OFF, Yellow ON
  digitalWrite(yellowLight1, HIGH);
  delay(3500);  // 3.5 Seconds of Yellow
  digitalWrite(yellowLight1, LOW);  // Yellow OFF, Red ON
  digitalWrite(redLight1, HIGH);
}

void station2Cycle() {
  delay(2500);  // 2.5 Seconds of Red
  digitalWrite(redLight2, LOW); digitalWrite(greenLight2, HIGH);  // Red OFF, Green ON
  delay(15000);  // 15 Seconds of Green
  digitalWrite(greenLight2, LOW); digitalWrite(yellowLight2, HIGH);  // Green OFF, Yellow ON
  delay(3500);  // 3.5 Seconds of Yellow
  digitalWrite(yellowLight2, LOW); digitalWrite(redLight2, HIGH);  // Yellow OFF, Red ON
}

void walkCycle() {
  delay(3500);  // 3.5 Second delay before "WALK" begins
  digitalWrite(whitePedestrianLED, HIGH); digitalWrite(redPedestrianLED, LOW);  // Turn on White Pedestrian Light
  delay(15000);  // 15 Second delay to allow crossing street
  digitalWrite(whitePedestrianLED, LOW);  // Turn off White Pedestrian Light
  digitalWrite(redPedestrianLED, HIGH);  // Turn on Red Pedestrian Light

  // Flash White Pedestrian LED 5 times
  for (int x = 0; x < 5; x++) {
    digitalWrite(whitePedestrianLED, HIGH);
    delay(250);
    digitalWrite(whitePedestrianLED, LOW);
    delay(250);
  }

  walkRequest = 0;  // Reset Walk Button request
}

void pinISR() {
  // Toggle the walkRequest when the button is pressed
  buttonState = digitalRead(walkButtonPin);
  if (buttonState == HIGH) {
    walkRequest = 1;  // Set Walk button state to pressed
  }
}
