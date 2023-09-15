//#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>

#define PASSWORD_MIN_LEN 1
#define PASSWORD_MAX_LEN 16
#define PASSWORD_DISPLAY '*'

// unit for measuring angles
#define DELTA_DEGREE 5
#define CLOSE_DOOR_DEGREE 0
#define OPEN_DOOR_DEGREE 90
#define SERVO_DELAY_TIME 15

// -------- password must have 1 more character to mark '\0' --------
// string to hold user input
char   data[PASSWORD_MAX_LEN+1];
// password
char master[PASSWORD_MAX_LEN+1] = "1234";

enum KEY_TYPE { ENTER = '#', DELETE = 'D', RETYPE = '*' };

// Pin connected to lock relay input
int lockOutput = 13;

// Counter for character entries
byte data_count = 0;

// Character to hold key input
char customKey;

// Constants for row and column size
const byte ROWS = 4;
const byte COLS = 4;

// Array2D to represent keys on ROWSxCOLS keypad
char hexKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Connections to Arduino
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};


// Create keypad object
Keypad customKeypad = Keypad(makeKeymap(hexKeys),rowPins, colPins, ROWS, COLS);

// Create LCD object
LiquidCrystal_I2C lcd(0x20, 16, 2);

// Create Servo object
Servo lockServo;
Servo doorServo;

byte lockServoPos = 0;
byte doorServoPos = 0;
byte servoPos = 0;

byte lockServoPin = 12;
byte doorServoPin = 13;
byte wrong_pw_alert = 10;
byte green_led = 11;

void setup() {
    Serial.begin(9600);
    // Setup lcd backlight and initialize
    lcd.backlight();
    lcd.init();
    resetLCD();

    // Set lockOutput as an OUTPUT pin
    pinMode(lockOutput, OUTPUT);

    // Set buzzer, red and green led as OUTPUT
    pinMode(wrong_pw_alert, OUTPUT);
    pinMode(green_led, OUTPUT);

    // Set up servo
	lockServo.attach(lockServoPin);
	doorServo.attach(doorServoPin);

  	//closeDoor();
  /* // test change password
  Serial.println(master);
  changePassword("1234567890123456");
  Serial.println(master);
  lcd.print(master);
  */
}

void loop() {
  // Look for keypress
  customKey = customKeypad.getKey();
  if (customKey) {
	switch(customKey) {
    case RETYPE: // when re-type password
		handle_retype();
		break;

    case DELETE: // when press delete
      	handle_delete();
		break;

    case ENTER: // when press enter
      	handle_enter();
      	break;

    default: // when typing password
      	handle_typing(customKey);
    	break;  	
    }
  }

}

void handle_retype() {
	clearData();
    resetLCD();
}

void handle_delete() {
  // ONLY HANDLE when data has at least 1 character 
  if (data_count > 0) {
    // delete last key in data and decrease data_count
	data[--data_count] = '\0';
  	
    // delete last char in lcd
	lcd.setCursor(data_count, 1);
    lcd.print(' ');
  }
}

void handle_enter() {
	lcd.clear();
    
    // password is correct
    if (strcmp(data, master) == 0) {
    	lcd.print("Correct!");
      
      	// turn on green led 1 sec
      	digitalWrite(green_led, HIGH);
      	delay(1000);
      	digitalWrite(green_led, LOW);
      	
      	// use servo to open door
      	openDoor();
      	delay(1000);
      	closeDoor();
    } else {
    	// turn on red ligt and buzzer
      	digitalWrite(wrong_pw_alert, HIGH);

      	lcd.print("Incorrect!");
      	delay(1000);

        // turn off red light and buzzer
        digitalWrite(wrong_pw_alert, LOW);
    }
    
    handle_retype();
}

void handle_typing(char key) {        
  	// Check if we have reached the password max length
	if (data_count == PASSWORD_MAX_LEN) {
		return;
	}

	// when data has empty space
    // Load key into data
    data[data_count] = key;
    
    // Display last key
    lcd.setCursor(data_count,1);
    lcd.print(PASSWORD_DISPLAY);
	// increase data_count
    data_count += 1;
}

void resetLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
}

void changePassword(char* newPassword) {
	byte password_len = strlen(newPassword);
  	// if password_len is valid
  	if (password_len >= PASSWORD_MIN_LEN
        && password_len <= PASSWORD_MAX_LEN) {
    	// update password
      	strcpy(master, newPassword);
    }
}

void clearData() {
  while(data_count != 0) {
  	//Serial.print(data[data_count-1]);
    data[--data_count] = '\0';
  }
  /*
  Serial.println();
  Serial.println(data_count);
  Serial.println(data[0]);
  */
}

// ---------- Use servo to open/close door ----------
void openDoor() {
  	for (; servoPos < OPEN_DOOR_DEGREE; servoPos += DELTA_DEGREE) { 
    	lockServo.write(servoPos);	// tell servo to go to position in variable 'pos'
        doorServo.write(servoPos);	// tell servo to go to position in variable 'pos'
    	delay(SERVO_DELAY_TIME);	// waits for the servo to reach the position
  	}
}
void closeDoor() {
    for (; servoPos > CLOSE_DOOR_DEGREE; servoPos -= DELTA_DEGREE) { 
      lockServo.write(servoPos);	// tell servo to go to position in variable 'pos'
      doorServo.write(servoPos);	// tell servo to go to position in variable 'pos'
      delay(SERVO_DELAY_TIME);	// waits for the servo to reach the position
    }
	//myServo.write(servoPos);	// tell servo to go to CLOSE_DOOR_DEGREE
}