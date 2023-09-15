// Họ và tên: Vũ Minh Phát
// MSSV: 21127739
// Quiz 01

// Thời gian hoạt động của mỗi đèn
#define RED_LIGHT_DURATION 		10000
#define GREEN_LIGHT_DURATION	7000
#define YELLOW_LIGHT_DURATION 	3000

// Khai báo pin cho các đèn
const byte greenLightPin  = 13;
const byte yellowLightPin = 12;
const byte redLightPin    = 11;

enum TrafficLight {
	RED_TURN,
  	GREEN_TURN,
  	YELLOW_TURN,
  	NUM_OF_LIGHT
};
// Cho đèn đỏ bật đầu tiên
byte turn = RED_TURN;

void setup() {
	pinMode(greenLightPin , OUTPUT);
  	pinMode(yellowLightPin, OUTPUT);
	pinMode(redLightPin   , OUTPUT);
	Serial.begin(9600);	
}

void loop() {
  	// tắt đèn đã bật trước đó
	turnOffPreviousLight();
  	// bật đèn thích hợp dựa theo giá trị turn
	turnOnCurrentLight();

	DEBUG_LOG(); // xem thời gian hoạt động của mỗi đèn

  	// xác định đèn tiếp theo được bật
  	turn = (turn + 1) % NUM_OF_LIGHT;

}

void turnOffPreviousLight() {
  	// Tắt đèn đã bật trước đó dựa theo giá trị prevTurn
  	byte prevTurn = (NUM_OF_LIGHT + turn - 1) % NUM_OF_LIGHT;
  	switch(prevTurn) {
  	case RED_TURN:
      	digitalWrite(redLightPin, LOW);
      	break;

    case GREEN_TURN:
      	digitalWrite(greenLightPin, LOW);
      	break;

	case YELLOW_TURN:
      	digitalWrite(yellowLightPin, LOW);
      	break;
  	}
}

void turnOnCurrentLight() {
  	// Bật đèn dựa theo giá trị turn
  	// và chờ một khoảng thời gian tương ứng
  	switch(turn) {
	case RED_TURN:
      	digitalWrite(redLightPin, HIGH);
      	delay(RED_LIGHT_DURATION);
      	break;

    case GREEN_TURN:
      	digitalWrite(greenLightPin, HIGH);
      	delay(GREEN_LIGHT_DURATION);
      	break;

	case YELLOW_TURN:
      	digitalWrite(yellowLightPin, HIGH);
      	delay(YELLOW_LIGHT_DURATION);
      	break;
  	}
}

// dùng để kiểm tra các đèn có chạy đúng hay không?
void DEBUG_LOG() {
	static int lastTime = 0;
  	static int currTime = 0;
	
  	currTime = millis() / 1000;
  	Serial.print("turn ");
	Serial.print(turn);
  	Serial.print(": ");
	Serial.println(currTime - lastTime);

  	lastTime = currTime;
}