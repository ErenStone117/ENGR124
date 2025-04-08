// Motor control pins and variables
const int dirPin = 2; // Direction pin
const int stepPin = 3; // Step pin
const int upButtonPin = 7; // Button to control lifting the motor
const int downButtonPin = 8; // Button to control lowering the motor

bool isMovingUp = false; // State of the motor moving up
bool isMovingDown = false; // State of the motor moving down
bool lastUpButtonState = HIGH; // Last state of the up button
bool lastDownButtonState = HIGH; // Last state of the down button
unsigned long lastDebounceTimeUp = 0; // Last debounce time for up button
unsigned long lastDebounceTimeDown = 0; // Last debounce time for down button
unsigned long debounceDelay = 50; // Debounce time in milliseconds
const int stepDelay = 2000; // Delay between steps in microseconds

// Water pump control pins and variables
const int buttonPin = 6;
// Pin connected to the push button
const int relayPin = 5;   // Pin connected to the relay module

void setup() {
  // Motor control setup
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(upButtonPin, INPUT_PULLUP); // Set up button pin as input with pull-up resistor
  pinMode(downButtonPin, INPUT_PULLUP); // Set down button pin as input with pull-up resistor

  // Water pump control setup
  pinMode(buttonPin, INPUT);  // Set button pin as input
  pinMode(relayPin, OUTPUT);   // Set relay pin as output
  digitalWrite(relayPin, LOW); // Ensure relay is off initially
}

void loop() {
  // Motor control: Read the current state of the buttons
  handleMotorControl();
  
  // Water pump control: Read the state of the push button
  handlePumpControl();
}

void handleMotorControl() {
  int upButtonState = digitalRead(upButtonPin);
  int downButtonState = digitalRead(downButtonPin);

  // Handle the up button
  if (upButtonState != lastUpButtonState) {
    lastDebounceTimeUp = millis(); // Reset the debounce timer
  }
  if ((millis() - lastDebounceTimeUp) > debounceDelay) {
    if (upButtonState == LOW) { // Button pressed
      if (!isMovingUp) { // If not already moving up
        isMovingUp = true; // Start moving up
        isMovingDown = false; // Stop moving down
        digitalWrite(dirPin, HIGH); // Set direction to up
      }
    } else { // Button released
      isMovingUp = false; // Stop moving up
    }
  }

  // Handle the down button
  if (downButtonState != lastDownButtonState) {
    lastDebounceTimeDown = millis(); // Reset the debounce timer
  }
  if ((millis() - lastDebounceTimeDown) > debounceDelay) {
    if (downButtonState == LOW) { // Button pressed
      if (!isMovingDown) { // If not already moving down
        isMovingDown = true; // Start moving down
        isMovingUp = false; // Stop moving up
        digitalWrite(dirPin, LOW); // Set direction to down
      }
    } else { // Button released
      isMovingDown = false; // Stop moving down
    }
  }

  // Control the motor if moving
  if (isMovingUp || isMovingDown) {
    digitalWrite(stepPin, HIGH); // Step the motor
    delayMicroseconds(stepDelay); // Adjust speed as needed
    digitalWrite(stepPin, LOW); // Step the motor
    delayMicroseconds(stepDelay);
  }

  // Save the current button states for the next loop iteration
  lastUpButtonState = upButtonState;
  lastDownButtonState = downButtonState;
}

void handlePumpControl() {
  // Read the state of the push button
  int buttonState = digitalRead(buttonPin);

  // If the button is pressed
  if (buttonState == HIGH) {
    digitalWrite(relayPin, HIGH); // Activate the relay (turn on the pump)
  } else {
    digitalWrite(relayPin, LOW);  // Deactivate the relay (turn off the pump)
  }
}
