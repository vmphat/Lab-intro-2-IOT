int r = 13, g=12, y=8;
int turn =0;
void setup()
{
  Serial.begin(9600);
  pinMode(r,OUTPUT);
  pinMode(g,OUTPUT);
  pinMode(y,OUTPUT);  
}
void loop()
{
    digitalWrite(r,0);
    digitalWrite(g,0);
    digitalWrite(y,0);
  
  if(turn==0) {
    digitalWrite(r,1);
  } else if(turn==1) {
    digitalWrite(g,1);
  } else {
    Serial.println(turn);
    digitalWrite(y,1);
  }
  turn= (turn+1)%3;
  delay(1000);
}
