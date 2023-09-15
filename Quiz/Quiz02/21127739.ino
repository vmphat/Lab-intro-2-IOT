// Họ và tên: Vũ Minh Phát
// MSSV: 21127739
// Quiz 02

// Định nghĩa pin của các LED và cảm biến k/cách
#define LED_1 		2
#define LED_2 		3
#define LED_3 		4
#define LED_4 		5
#define LED_5 		6
#define TRIG_PIN	8
#define ECHO_PIN	9

// Tốc độ âm thanh (cm/us)
#define SOUND_SPEED	0.0344
#define EPS			1e-06

// Các thông số của cảm biến khoảng cách
#define MIN_RANGE			2
#define MAX_RANGE			330
#define RANGING_ACCURACY	0.3
#define UNDEFINE			-1

// Ngưỡng phát sáng của từng LED
// (nếu khoảng cách vượt qua ngưỡng thì LED phát sáng)
#define LED_1_FLASH_THRES	0
#define LED_2_FLASH_THRES	50
#define LED_3_FLASH_THRES	100
#define LED_4_FLASH_THRES	150
#define LED_5_FLASH_THRES	200

// Khoảng cách từ cảm biến tới vật (cm)
double distanceCm;
double lastDistanceCm;

void setup() {
	pinMode(LED_1, OUTPUT);
  	pinMode(LED_2, OUTPUT);
	pinMode(LED_3, OUTPUT);
	pinMode(LED_4, OUTPUT);
	pinMode(LED_5, OUTPUT);

  	pinMode(TRIG_PIN, OUTPUT);
	pinMode(ECHO_PIN, INPUT);

	Serial.begin(9600);
}

void loop() {
  	// Giá trị khoảng cách đo được
  	distanceCm = getDistanceInCm();
  	if (distanceCm < MIN_RANGE || distanceCm > MAX_RANGE) {
		handleOutOfRangeDistance();
    }
  	Serial.println(distanceCm);

	turnOffAllLED();
	turnOnSatisfiedLED(distanceCm);

  	lastDistanceCm = distanceCm;
  	delay(10);
}

double getDistanceInCm() {
  	// clear the TRIG_PIN
	digitalWrite(TRIG_PIN, LOW);
  	delayMicroseconds(2);
  	// set TRIG_PIN on HIGH state for 10us
 	digitalWrite(TRIG_PIN, HIGH);
  	delayMicroseconds(10);
  	digitalWrite(TRIG_PIN, LOW);

  	// tính thời gian sóng âm di chuyển (us)
	unsigned long duration = pulseIn(ECHO_PIN, HIGH);

	// trả về khoảng cách từ cảm biến tới vật
  	return duration * SOUND_SPEED / 2.;
}

void handleOutOfRangeDistance() {
	double distToMin = fabs(lastDistanceCm - MIN_RANGE);
  	double distToMax = fabs(lastDistanceCm - MAX_RANGE);
  	
  	if (distToMin < distToMax) {
		distanceCm = MIN_RANGE;
    } else {
      	distanceCm = MAX_RANGE;
    }
}

void turnOffAllLED() {
	digitalWrite(LED_1, LOW);
	digitalWrite(LED_2, LOW);
	digitalWrite(LED_3, LOW);
	digitalWrite(LED_4, LOW);
	digitalWrite(LED_5, LOW);
}
void turnOnSatisfiedLED(double comparedValue) {
	turnOnLEDIfSatisfy(comparedValue, LED_1_FLASH_THRES, LED_1);
  	turnOnLEDIfSatisfy(comparedValue, LED_2_FLASH_THRES, LED_2);
	turnOnLEDIfSatisfy(comparedValue, LED_3_FLASH_THRES, LED_3);
	turnOnLEDIfSatisfy(comparedValue, LED_4_FLASH_THRES, LED_4);
	turnOnLEDIfSatisfy(comparedValue, LED_5_FLASH_THRES, LED_5);
}
void turnOnLEDIfSatisfy(double comparedValue, byte thres, byte ledPin) {
	if (isGreaterThan(comparedValue, thres)) {
		digitalWrite(ledPin, HIGH);
    }
}

bool isEqual(double a, double b) {
  	return fabs(a-b) < EPS;// 
}
bool isGreaterThan(double a, double b) {
	return (a-b) > EPS;
}