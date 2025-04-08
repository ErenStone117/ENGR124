const int relayPin = 6;    // Relay control pin (connected to Mega's pin 6)
const int buttonPin = 4;   // Button pin (connected to Mega's pin 4)

unsigned long lastDebounceTime = 0; // Debounce timer
const unsigned long debounceDelay = 50; // 50ms debounce

void setup() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Ensure motor is OFF initially
  pinMode(buttonPin, INPUT_PULLUP); // Use Mega's internal pull-up resistor
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  // Debounce logic
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (buttonState == LOW) { // Button pressed (LOW due to pull-up)
      digitalWrite(relayPin, HIGH); // Turn motor ON
    } else {
      digitalWrite(relayPin, LOW); // Turn motor OFF
    }
    lastDebounceTime = millis(); // Reset debounce timer
  }
}
