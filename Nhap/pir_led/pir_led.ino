// C++ code
//

#define DETACHED HIGH

byte irPin = 12;
byte ledPin = 13;

// the setup function runs once when you press reset or power the board
void setup() {
    // initialize digital pin LED_BUILTIN as an output.
	pinMode(irPin, INPUT);
	pinMode(ledPin, OUTPUT);

    Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
	byte input = digitalRead(irPin);
  	if(digitalRead(irPin) == DETACHED) {
      	Serial.println(input);
		digitalWrite(ledPin, HIGH);
    } else {
		Serial.println(input);
    	digitalWrite(ledPin, LOW);
    }
  	delay(10);
}