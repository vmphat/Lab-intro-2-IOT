// Họ và tên: Vũ Minh Phát
// MSSV: 21127739
// Quiz 03

// Định nghĩa các pin sẽ sử dụng
#define LIGHT_PIN	A0
#define RELAY_PIN	8

// Khi giá trị quang trở chạm
// tới ngưỡng này thì tắt đèn
#define LIGHT_OFF_THRES	500

// Cường độ sáng đo được từ quang trở 
int lightIntensity;

void setup() {
	pinMode(LIGHT_PIN, INPUT);
  	pinMode(RELAY_PIN, OUTPUT);

 	Serial.begin(9600);
}

void loop() {
  	lightIntensity = analogRead(LIGHT_PIN);
	Serial.println(lightIntensity);

  	// Bật đèn nếu giá trị quang trở < 500
  	if (lightIntensity < LIGHT_OFF_THRES) {
		digitalWrite(RELAY_PIN, HIGH);
    }
  	// Tắt đèn nếu ngược lại
    else {
        digitalWrite(RELAY_PIN, LOW);
    }
}
