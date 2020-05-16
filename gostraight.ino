#define D1 2
#define D2 3
#define A1 4
#define A2 5
#define B1 6
#define B2 7
#define C1 8
#define C2 9
/*电机引脚初始化*/
void motor_pinint( )
{
  pinMode (A1, OUTPUT); 
  pinMode (A2, OUTPUT);
  pinMode (B1, OUTPUT); 
  pinMode (B2, OUTPUT); 
  pinMode (C1, OUTPUT); 
  pinMode (C2, OUTPUT);
  pinMode (D1, OUTPUT); 
  pinMode (D2, OUTPUT); //设置引脚为输出引脚
  }
void mystop(){
  analogWrite(A1,0);
  analogWrite(A2,0);
  analogWrite(B1,0);
  analogWrite(B2,0);
  analogWrite(C1,0);
  analogWrite(C2,0);
  analogWrite(D1,0);
  analogWrite(D2,0);
}

void Turnfront_F(int v)
{ analogWrite(A1,0);
  analogWrite(A2,v);
analogWrite(B1,0);
  analogWrite(B2,v);
analogWrite(C1,v);
  analogWrite(C2,0);
analogWrite(D1,v);
  analogWrite(D2,0);
}


void setup() {
 
  Serial.begin(9600); //串口波特率9600（PC端使用）
  motor_pinint();     //电机引脚初始化
}

void loop() {
  // put your main code here, to run repeatedly:
  Turnfront_F(40);//直走
  delay(2000);
  mystop();//停止
  delay(10000);
}
