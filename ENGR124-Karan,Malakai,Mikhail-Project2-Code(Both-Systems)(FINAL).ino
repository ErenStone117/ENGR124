// Define pin connections & motor's steps per revolution
const int dirPin = 3;          // Direction pin for stepper motor
const int stepPin = 4;         // Step pin for stepper motor
const int stepsPerRevolution = 500; // Steps per revolution

const int buttonCW = 5;        // Button for clockwise rotation
const int buttonCCW = 6;       // Button for counterclockwise rotation

// Speed control variables
int stepDelay = 2000; // Increased delay for lower speed and higher torque

// Relay and button for water pump
const int buttonPin = 7; // Button connected to pin 7
const int relay_pump = 8; // Relay connected to pin 8
int buttonState;

void setup()
{
    // Declare pins as Outputs
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    pinMode(relay_pump, OUTPUT);

    // Declare button pins as Inputs
    pinMode(buttonCW, INPUT_PULLUP);  // Use internal pull-up resistor
    pinMode(buttonCCW, INPUT_PULLUP); // Use internal pull-up resistor
    pinMode(buttonPin, INPUT_PULLUP);  // Use internal pull-up resistor for pump button
}

void loop()
{
    // Check if the clockwise button is pressed
    if (digitalRead(buttonCW) == LOW) // Button pressed (active LOW)
    {
        // Set motor direction clockwise
        digitalWrite(dirPin, HIGH);
        
        // Spin motor continuously while button is pressed
        while (digitalRead(buttonCW) == LOW) {
            digitalWrite(stepPin, HIGH);
            delayMicroseconds(stepDelay); // Adjust speed as needed
            digitalWrite(stepPin, LOW);
            delayMicroseconds(stepDelay);
        }
    }

    // Check if the counterclockwise button is pressed
    if (digitalRead(buttonCCW) == LOW) // Button pressed (active LOW)
    {
        // Set motor direction counterclockwise
        digitalWrite(dirPin, LOW);
        
        // Spin motor continuously while button is pressed
        while (digitalRead(buttonCCW) == LOW) {
            digitalWrite(stepPin, HIGH);
            delayMicroseconds(stepDelay); // Adjust speed as needed
            digitalWrite(stepPin, LOW);
            delayMicroseconds(stepDelay);
        }
    }

    // Read the button state for the water pump
    buttonState = digitalRead(buttonPin);

    if (buttonState == LOW) { // We press the button (assuming active low)
        digitalWrite(relay_pump, HIGH); // The water pump fills the bottle
    } else { // We release the button
        digitalWrite(relay_pump, LOW); // The water pump stops
    }
}
