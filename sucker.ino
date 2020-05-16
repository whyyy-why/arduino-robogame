#define xp1 51  //连到I/O口
#define xp2 49

void setup() {
  // 初始化
  pinMode(xp1,OUTPUT);
  pinMode(xp2,OUTPUT);
  
}

void loop() {
 
    digitalWrite(xp1,HIGH);   //吸盘一直吸
    digitalWrite(xp2,HIGH);   
    delay(6000);
    digitalWrite(xp2,LOW);   //关闭吸盘
    delay(6000);
    digitalWrite(xp1,LOW);
    delay(100000);
   

}
