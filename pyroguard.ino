/*
**********************************************************************
* Programmer: Shivansh Khullar
* Date: Tuesday June 20, 2023
**********************************************************************
* Program: A gas monitoring and alert system to ensure safety by
* detecting gas levels and providing visual and auditory warnings.
**********************************************************************
* Description: The system monitors gas levels using a sensor. 
* Based on the readings, it displays the status (NORMAL, WARNING, 
* or DANGER) on an LCD, activates corresponding LEDs, and emits 
* alert tones in the case of high gas levels.
**********************************************************************
* Connections: 
* - LCD: pins 12, 11, 5, 4, 3, 2
* - Gas sensor: pin A0
* - LEDs: pins 6, 7, 13
* - Buzzer: pin 9
**********************************************************************
*/

#include <LiquidCrystal.h>

// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int buzzerPin = 9; // Piezo buzzer pin

void setup() {
  Serial.begin(9600);        // Initialize serial communication for debugging
  lcd.begin(16, 2);          // Initialize the LCD with 16 columns and 2 rows
  pinMode(13, OUTPUT);       // LED pin for DANGER
  pinMode(7, OUTPUT);        // LED pin for NORMAL
  pinMode(6, OUTPUT);        // LED pin for WARNING
}

void loop() {
  int gas_data = analogRead(A0);  // Read gas sensor data from pin A0

  // Display the gas level on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Gas :");
  lcd.setCursor(6, 0);
  lcd.print(gas_data);

  if (gas_data > 800) {
    // DANGER: High gas level detected
    digitalWrite(7, LOW);         // Turn off NORMAL LED
    digitalWrite(6, LOW);         // Turn off WARNING LED
    digitalWrite(13, HIGH);       // Turn on DANGER LED
    lcd.setCursor(0, 1);
    lcd.print("DANGER");

    // Play alert tones
    emitDangerTones();

  } else if (gas_data > 700) {
    // WARNING: Moderate gas level detected
    digitalWrite(7, LOW);         // Turn off NORMAL LED
    digitalWrite(13, LOW);        // Turn off DANGER LED
    digitalWrite(6, HIGH);        // Turn on WARNING LED
    lcd.setCursor(0, 1);
    lcd.print("WARNING");
  } else {
    // NORMAL: Safe gas level
    digitalWrite(6, LOW);         // Turn off WARNING LED
    digitalWrite(13, LOW);        // Turn off DANGER LED
    digitalWrite(7, HIGH);        // Turn on NORMAL LED
    lcd.setCursor(0, 1);
    lcd.print("NORMAL");
  }

  delay(500);  // Wait before the next reading
}

void emitDangerTones() {
  // Emit a sequence of tones for danger indication
  int tones[] = {400, 800, 600, 1000};
  for (int i = 0; i < 4; i++) {
    tone(buzzerPin, tones[i], 200);  // Play tone
    delay(300);                     // Wait between tones
    noTone(buzzerPin);              // Stop tone
    delay(200);
  }
}
