#define bj11 33       //bj1转传送带的步进电机    1是连接DIR+到单片机IO口的   其他：DIR-,PUL-接GND EN-接GND EN+不接
#define bj12 35               //2是连接PUL+到单片机IO口的
#define bj21  50                //bj2转负载的步进电机
#define bj22 48

void stepper_rotate1(int Tus,int circle,int bj)       //这个是步进电机转的函数，第一个参数是脉冲的周期，改变可改变转速，第二个是转的圈数，第三个是步进电机的PUL+接到哪个口了
{
  int i=200*circle,     //这个200可改   决定了一次转多少圈   
      j;
  for(j=0;j<i;j++)
  {
    digitalWrite(bj, HIGH);             //这里模拟产生脉冲信号
    delayMicroseconds((int)(Tus/2));
    digitalWrite(bj, LOW);
    delayMicroseconds((int)(Tus/2));
  }
}
void stepper_rotate2(int Tus,int circle,int bj) 
{
  int i=50*circle,                 //这个40 转完快要90°  可改
      j;
  for(j=0;j<i;j++)
  {
    digitalWrite(bj, HIGH);
    delayMicroseconds((int)(Tus/2));
    digitalWrite(bj, LOW);
    delayMicroseconds((int)(Tus/2));
  }
}

void setup() {
  // put your setup code here, to run once:
    pinMode(bj11,OUTPUT);
    pinMode(bj12,OUTPUT);
    pinMode(bj21,OUTPUT);
    pinMode(bj22,OUTPUT);
    digitalWrite(bj11,HIGH);       //这里HIGH 设定的是步进电机正转
    digitalWrite(bj21,HIGH); 
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(bj11,LOW);     
 // stepper_rotate2(1000000,1,bj12); //转90°
  stepper_rotate1(2000000,1,bj12);
  delay(5000);               //转完等5s
}
