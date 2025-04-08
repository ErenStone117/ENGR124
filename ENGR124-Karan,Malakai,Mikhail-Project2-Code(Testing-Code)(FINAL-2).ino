// Define pin connections for the water pump
const int buttonPin = 1; // Button connected to pin 1
const int relay_pump = 2; // Relay connected to pin 2
int buttonState;

// Define pin connections for the stepper motor
const int dirPin = 3; // Direction pin
const int stepPin = 4; // Step pin
const int upButtonPin = 7; // Button to control lifting the motor
const int downButtonPin = 8; // Button to control lowering the motor

// Variables to track button states for the stepper motor
bool isMovingUp = false; // State of the motor moving up
bool isMovingDown = false; // State of the motor moving down
bool lastUpButtonState = HIGH; // Last state of the up button
bool lastDownButtonState = HIGH; // Last state of the down button
unsigned long lastDebounceTimeUp = 0; // Last debounce time for up button
unsigned long lastDebounceTimeDown = 0; // Last debounce time for down button
unsigned long debounceDelay = 50; // Debounce time in milliseconds

// Motor speed control
const int stepDelay = 2000; // Delay between steps in microseconds

void setup() {
    // Setup for water pump
    pinMode(buttonPin, INPUT);
    pinMode(relay_pump, OUTPUT);

    // Setup for stepper motor
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    pinMode(upButtonPin, INPUT_PULLUP); // Set up button pin as input with pull-up resistor
    pinMode(downButtonPin, INPUT_PULLUP); // Set down button pin as input with pull-up resistor
}

void loop() {
    // Read the button state for the water pump
    buttonState = digitalRead(buttonPin);
    if (buttonState == LOW) { // We press the button
        digitalWrite(relay_pump, HIGH); // The water pump fills the bottle
    } else { // We release the button
        digitalWrite(relay_pump, LOW); // The water pump stops
    }

    // Read the current state of the stepper motor buttons
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
