
void setup() {
  // put your setup code here, to run once:
  pinMode(22,INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int a;
  //读开关的状态记入a 状态分为0与1
   a=digitalRead(22);
   Serial.print("=");
   Serial.println(a);
}
