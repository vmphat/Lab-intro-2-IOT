int red  = 11;
int blue = 10;
int green=  9;
void setup() {
  pinMode(red  , OUTPUT);
  pinMode(blue , OUTPUT);
  pinMode(green, OUTPUT);

  Serial.begin(9600);
  Serial.println();
  String s = "84d8b2";
  /*
  Serial.println(s.substring(0,2));
  Serial.println(hexToDec(s.substring(0,2)));
  
  Serial.println(s.substring(2,4));
  Serial.println(hexToDec(s.substring(2,4)));
  
  Serial.println(s.substring(4,6));
  Serial.println(hexToDec(s.substring(4,6)));
  */
  int r=132, g=216, b=178;
  Serial.println(decToHex(r,2)+decToHex(g,2)+decToHex(b,2));


}

void loop() {
  //turnOnRGB(255,178,102);
  //turnOnRGB("84d8b2");
  turnOnRGB(132, 216, 178);
  delay(1000);

}

void turnOnRGB(int r, int g, int b) {
  analogWrite(red, r);
  analogWrite(green, g);
  analogWrite(blue, b);
}

void turnOnRGB(String hexCode) {
  // Xu ly ngoai le
  
  analogWrite(red  , hexToDec(hexCode.substring(0,2)));
  analogWrite(green, hexToDec(hexCode.substring(2,4)));
  analogWrite(blue , hexToDec(hexCode.substring(4,6)));
}

int hexToDec(String hexString) {
  
  int decValue = 0;
  int nextInt = 0;
  
  for (int i = 0; i < hexString.length(); i++) {
    
    nextInt = int(hexString.charAt(i));
    if (nextInt >= 48 && nextInt <= 57) 
      	nextInt = map(nextInt, 48, 57, 0, 9);
    else if (nextInt >= 65 && nextInt <= 70) 
      	nextInt = map(nextInt, 65, 70, 10, 15);
    else if (nextInt >= 97 && nextInt <= 102) 
      	nextInt = map(nextInt, 97, 102, 10, 15);
    nextInt = constrain(nextInt, 0, 15);
    
    decValue = (decValue * 16) + nextInt;
  }
  
  return decValue;
}

String decToHex(byte decValue, byte desiredStringLength) {
  
  String hexString = String(decValue, HEX);
  while (hexString.length() < desiredStringLength) 
    	hexString = "0" + hexString;
  
  return hexString;
}