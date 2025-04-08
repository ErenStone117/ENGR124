// Define pin connections & motor's steps per revolution
const int dirPin = 2;          // Direction pin
const int stepPin = 3;         // Step pin
const int stepsPerRevolution =500; // Steps per revolution

const int buttonCW = 4;        // Button for clockwise rotation
const int buttonCCW = 5;       // Button for counterclockwise rotation

void setup()
{
    // Declare pins as Outputs
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    
    // Declare button pins as Inputs
    pinMode(buttonCW, INPUT_PULLUP);  // Use internal pull-up resistor
    pinMode(buttonCCW, INPUT_PULLUP); // Use internal pull-up resistor
}

void loop()
{
    // Check if the clockwise button is pressed
    if (digitalRead(buttonCW) == LOW) // Button pressed (active LOW)
    {
        // Set motor direction clockwise
        digitalWrite(dirPin, HIGH);
        
        // Spin motor
        for(int x = 0; x < stepsPerRevolution; x++)
        {
            digitalWrite(stepPin, HIGH);
            delayMicroseconds(2000); // Adjust speed as needed
            digitalWrite(stepPin, LOW);
            delayMicroseconds(2000);
        }
        delay(100); // Short delay to debounce button
    }

    // Check if the counterclockwise button is pressed
    if (digitalRead(buttonCCW) == LOW) // Button pressed (active LOW)
    {
        // Set motor direction counterclockwise
        digitalWrite(dirPin, LOW);
        
        // Spin motor
        for(int x = 0; x < stepsPerRevolution; x++)
        {
            digitalWrite(stepPin, HIGH);
            delayMicroseconds(1000); // Adjust speed as needed
            digitalWrite(stepPin, LOW);
            delayMicroseconds(1000);
        }
        delay(100); // Short delay to debounce button
    }
}