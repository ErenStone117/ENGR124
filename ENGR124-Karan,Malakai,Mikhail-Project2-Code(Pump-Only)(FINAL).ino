const int buttonPin = 1; // Button connected to pin 1
const int relay_pump = 2; // Relay connected to pin 2
int buttonState;

void setup() {
    pinMode(buttonPin, INPUT);
    pinMode(relay_pump, OUTPUT);
}

void loop() {
    // Read the button state
    buttonState = digitalRead(buttonPin);

    if (buttonState == LOW) { // We press the button (assuming active low)
        digitalWrite(relay_pump, HIGH); // The water pump fills the bottle
    } else { // We release the button
        digitalWrite(relay_pump, LOW); // The water pump stops
    }
}