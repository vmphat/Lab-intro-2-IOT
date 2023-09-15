// Họ và tên: Vũ Minh Phát
// MSSV: 21127739
// Lab 01

// Định nghĩa các pin dành cho đèn LED và button
#define RED_LED		2
#define GREEN_LED	4
#define BLUE_LED	6
#define WHITE_LED	3
#define ORANGE_LED	5
#define YELLOW_LED	7
#define BUTTON		8

// Ngưỡng thời gian khi ấn và giữ nút quá lâu
// thì tất cả LED sẽ bật sáng
#define PRESS_N_HOLD_BUTTON_THRES	6000
// Thời gian chớp tắt luân phiên 
// của mỗi UPPER_LED (hàng phía trên)
#define ALTER_FLASH_TIME			1000

// Đặt định danh cho mỗi LED theo quy ước
enum LED_ID {
	LED_1 = RED_LED,
  	LED_2 = GREEN_LED,
	LED_3 = BLUE_LED,
	LED_4 = WHITE_LED,
	LED_5 = ORANGE_LED,
	LED_6 = YELLOW_LED
};

// Quy định thứ tự chớp tắt luân phiên
// cho các LED hàng trên khi ấn nút nhấn
enum UPPER_LED_TURN {
	RED_TURN = 0,
  	GREEN_TURN,
	BLUE_TURN,
  	NUM_OF_UPPER_LED
};
// LED đầu tiên được bật sáng là RED_LED
// trong chu trình chớp tắt luân phiên
byte ledTurn = RED_TURN;

// Khi vừa khởi động chương trình
// thì trạng thái nút nhấn là thả
byte lastButtonState = LOW;
// Lưu thời điểm gần nhất khi nút nhấn
// chuyển trạng thái (nhấn <-> thả)
unsigned long lastButtonStateChangeMillis = 0;

// Lưu thời điểm 1 đèn bật sáng
// trong chu trình chớp tắt luân phiên
unsigned long lastUpperLEDFlashingMillis = 0;
// Biến cờ hiệu xác định xem đã reset
// chu trình chớp tắt hay chưa?
bool hasResetCycle = false;

void setup() {
	pinMode(   RED_LED, OUTPUT);
  	pinMode( GREEN_LED, OUTPUT);
	pinMode(  BLUE_LED, OUTPUT);
	pinMode( WHITE_LED, OUTPUT);
	pinMode(ORANGE_LED, OUTPUT);
	pinMode(YELLOW_LED, OUTPUT);
  
  	pinMode(BUTTON, INPUT);

  	Serial.begin(9600);
}

void loop() {
	// Lấy trạng thái hiện tại của nút nhấn 
	byte buttonState = digitalRead(BUTTON);
  	// Nếu chuyển trạng thái
	if (buttonState != lastButtonState) {
		lastButtonStateChangeMillis = millis();
		lastButtonState = buttonState;
    }

	// Khi thả nút nhấn ra
    if (buttonState == LOW) {
      	// LED 1, 2, 3 -> sáng đồng loạt
		turnOnUpperLED();
		// LED 4, 5, 6 -> tắt đồng loạt
		turnOffLowerLED();

		hasResetCycle = false;
    }

	// Khi ấn nút
    if (buttonState == HIGH) {   
      	// Khi ấn và giữ nút quá lâu
		if (millis() - lastButtonStateChangeMillis > PRESS_N_HOLD_BUTTON_THRES) {
          	// thì tất cả LED bật sáng
			turnOnUpperLED();
			turnOnLowerLED();
        } else {
          	// Reset chu trình nếu cần
			if (hasResetCycle == false) {
				resetUpperLEDCycle();
			}
			// LED 4, 5, 6 -> sáng đồng loạt
			turnOnLowerLED();
          	// LED 1, 2, 3 -> chớp tắt luân phiên
			alterFlashingUpperLED();    	
        }
    }
}

void turnOnUpperLED() {
	digitalWrite(LED_1, HIGH);
	digitalWrite(LED_2, HIGH);
	digitalWrite(LED_3, HIGH);
}
void turnOffUpperLED() {
	digitalWrite(LED_1, LOW);
	digitalWrite(LED_2, LOW);
	digitalWrite(LED_3, LOW);
}
void turnOnLowerLED() {
	digitalWrite(LED_4, HIGH);
	digitalWrite(LED_5, HIGH);
	digitalWrite(LED_6, HIGH);
}
void turnOffLowerLED() {
	digitalWrite(LED_4, LOW);
	digitalWrite(LED_5, LOW);
	digitalWrite(LED_6, LOW);
}

void resetUpperLEDCycle() {
	turnOffUpperLED();
	hasResetCycle = true;
	ledTurn = RED_TURN;
	lastUpperLEDFlashingMillis = millis();
}

void alterFlashingUpperLED() {
	// Nếu 1 đèn kết thúc thời gian phát sáng
	if (millis() - lastUpperLEDFlashingMillis >= ALTER_FLASH_TIME) {
      	// Chuyển lượt phát sáng cho đèn kế tiếp
    	ledTurn = (ledTurn + 1) % NUM_OF_UPPER_LED;
		// Tắt đèn đã bật sáng trước đó
      	turnOffPreviousUpperLED();

		lastUpperLEDFlashingMillis = millis();
    }
	turnOnCurrentUpperLED();
}
void turnOnCurrentUpperLED() {
	switch(ledTurn) {
	case RED_TURN:
		digitalWrite(RED_LED, HIGH);
		break;
	case GREEN_TURN:
    	digitalWrite(GREEN_LED, HIGH);
    	break;
	case BLUE_TURN:
    	digitalWrite(BLUE_LED, HIGH);
    	break;
	}
}
void turnOffPreviousUpperLED() {
	byte prevTurn = (NUM_OF_UPPER_LED + ledTurn - 1) % NUM_OF_UPPER_LED;
	switch(prevTurn) {
  	case RED_TURN:
    	digitalWrite(RED_LED, LOW);
    	break;
  	case GREEN_TURN:
   		digitalWrite(GREEN_LED, LOW);
    	break;
 	case BLUE_TURN:
    	digitalWrite(BLUE_LED, LOW);
    	break;
	}
}