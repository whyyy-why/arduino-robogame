#define D1 2
#define D2 3
#define A1 4
#define A2 5
#define B1 6
#define B2 7
#define C1 8
#define C2 9

#define frontA_track_PIN 30
#define frontB_track_PIN 32
#define leftA_track_PIN 34
#define leftB_track_PIN 36
#define righA_track_PIN 38
#define righB_track_PIN 40
#define backA_track_PIN 42
#define backB_track_PIN 44

void motor_pinint( );                               //引脚初始化
void _stop();                         
int n1,n2,n3,n4;
int i1,i2,i3,i4;
int f1,f2,l1,l2,r1,r2,b1,b2;                  //8个传感器数值的数组 

/*循迹模块引脚初始化*/
void track_pinint( )
{ 
  pinMode (leftA_track_PIN, INPUT); 
  pinMode (leftB_track_PIN, INPUT); 
  pinMode (frontA_track_PIN,INPUT);
  pinMode (frontB_track_PIN,INPUT);
  pinMode (backA_track_PIN,INPUT);
  pinMode (backA_track_PIN,INPUT);
  pinMode (righA_track_PIN, INPUT);
  pinMode (righB_track_PIN, INPUT); //设置引脚为输入引脚
}
 
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

void getstate()
{
  f1 = digitalRead(frontA_track_PIN);
  f2 = digitalRead(frontB_track_PIN);
  l1 = digitalRead(leftA_track_PIN);
  l2 = digitalRead(leftB_track_PIN);
  r1 = digitalRead(righA_track_PIN);
  r2 = digitalRead(righB_track_PIN);
  b1 = digitalRead(backA_track_PIN);
  b2 = digitalRead(backB_track_PIN);
}

void motorCW1(int v)  //一号轮正转
{analogWrite(A1,0);
  analogWrite(A2,v);}

void motorCCW1(int v)  //一号轮反转
{analogWrite(A1,v);
  analogWrite(A2,0);}

void motorCW2(int v)  //二号轮正转
{analogWrite(B1,0);
  analogWrite(B2,v);}

void motorCCW2(int v)  //二号轮反转
{analogWrite(B1,v);
  analogWrite(B2,0);}

void motorCW3(int v)  //三号轮正转
{analogWrite(C1,0);
  analogWrite(C2,v);}

void motorCCW3(int v)  //三号轮反转
{analogWrite(C1,v);
  analogWrite(C2,0);}

void motorCW4(int v)  //四号轮正转
{analogWrite(D1,v);
  analogWrite(D2,0);}

void motorCCW4(int v)  //四号轮反转
{analogWrite(D1,0);
  analogWrite(D2,v);}

void Turnfront_F()
{ analogWrite(A1,0);
  analogWrite(A2,40);
analogWrite(B1,0);
  analogWrite(B2,40);
analogWrite(C2,40);
  analogWrite(C1,0);
analogWrite(D1,40);
  analogWrite(D2,0);
}

void Turnleft()
{ analogWrite(A2,40);
  analogWrite(A1,0);
analogWrite(B2,40);
  analogWrite(B1,0);
analogWrite(C1,40);
  analogWrite(C2,0);
analogWrite(D2,40);
  analogWrite(D1,0);
}
void Turnright()
{ analogWrite(A1,40);
  analogWrite(A2,0);
analogWrite(B1,40);
  analogWrite(B2,0);
analogWrite(C2,40);
  analogWrite(C1,0);
analogWrite(D1,40);
  analogWrite(D2,0);
}

void Turnfront_B()
{motorCCW1(40);
 motorCCW2(40);
 motorCCW3(40);
 motorCCW4(40);
}

void Turnfront_R()
{motorCCW1(40);
 motorCW2(40);
 motorCCW3(40);
 motorCW4(40);
}

void Turnfront_L()
{motorCW1(40);
 motorCCW2(40);
 motorCW3(40);
 motorCCW4(40);
}
int forward_inf()
{
    getstate();
    if((f1==0)&&(f2==0))   {n1=0;}
    else if((f1==0)&&(f2==1))    {n1=1;}
    else if((f1==1)&&(f2==0))    {n1=-1;}
    else if((f1==1)&&(f2==1))    {n1=0;}      
    return n1;
}

 int back_inf()
{
    getstate();
    if((b1==0)&&(b2==0))   {n2=0;}
    else if((b1==0)&&(b2==1))    {n2=1;}
    else if((b1==1)&&(b2==0))    {n2=-1;}
    else if((b1==1)&&(b2==1))    {n2=0;}      
    return n2;
}
 int leftward_inf()
{
    getstate();
    if((l1==0)&&(l2==0))   {n3=0;}
    else if((l1==0)&&(l2==1))    {n3=1;}
    else if((l1==1)&&(l2==0))    {n3=-1;}
    else if((l1==1)&&(l2==1))    {n3=0;}      
    return n3;
}
 int rightward_inf()
{
    getstate();
    if((r1==0)&&(r2==0))   {n4=0;}
    else if((r1==0)&&(r2==1))    {n4=1;}
    else if((r1==1)&&(r2==0))    {n4=-1;}
    else if((r1==1)&&(r2==1))    {n4=0;}      
    return n4;
}

int crossroad_F()     //前行时判断岔道
{
  getstate();
  if((l1==0)&&(l2==1)&&(r1==1)&&(r2==1))
  {
    int a1=0;
    while(l1==0){
      delay(2);
      getstate();
      a1++;
    }
    if((l1==1)&&(l2==1)&&(a1>=50)) i1=-1; //左岔道
  }
 else if((r1==0)&&(r2==1)&&(l1==1)&&(l2==1))
  {
    int a2=0;
    while(r1==0){
      delay(2);
      getstate();
      a2++;
    }
    if((r1==1)&&(r2==1)&&(a2>=50)) i1=1; //右岔道
  }
  else i1=0; //无岔道或十字等     
}
int crossroad_R()     //右行时判断岔道
{
  getstate();
  if((f1==1)&&(f2==0))
  {
    int a3=0;
    while(f2==0){
      delay(2);
      getstate();
      a3++;
    }
    if((f1==1)&&(f2==1)&&(a3>=50)) i2=-1; //前岔道
  }
  else if((b1==1)&&(b2==0))
  {
    int a4=0;
    while(b2==0){
      delay(2);
      getstate();
      a4++;
    }
    if((b1==1)&&(b2==1)&&(a4>=50)) i2=1; //后岔道
  }
  else i2=0; //无岔道     
}
int crossroad_L()     //左行时判断岔道
{
  getstate();
  if((f1==0)&&(f2==1))
  {
    int a5=0;
    while(f1==0){
      delay(2);
      getstate();
      a5++;
    }
    if((f1==1)&&(f2==1)&&(a5>=50)) i3=-1; //前岔道
  }
  else if((b1==0)&&(b2==1))
  {
    int a6=0;
    while(b1==0){
      delay(2);
      getstate();
      a6++;
    }
    if((b1==1)&&(b2==1)&&(a6>=50)) i3=1; //后岔道
  }
  else i3=0; //无岔道     
}
int crossroad_B()     //后行时判断岔道
{
  getstate();
  if((l1==1)&&(l2==0))
  {
    int a7=0;
    while(l1==0){
      delay(2);
      getstate();
      a7++;
    }
    if((l1==1)&&(l2==1)&&(a7>=50)) i4=-1; //左岔道
  }
  else if((r1==1)&&(r2==0))
  {
    int a8=0;
    while(r1==0){
      delay(2);
      getstate();
      a8++;
    }
    if((r1==1)&&(r2==1)&&(a8>=50)) i4=1; //右岔道
  }
  else i4=0; //无岔道     
}

void _stop()
{
  analogWrite(A2,0);
  analogWrite(A1,0);
  analogWrite(B2,0);
  analogWrite(B1,0);
  analogWrite(C1,0);
  analogWrite(C2,0);
  analogWrite(D2,0);
  analogWrite(D1,0);  
  }
  
void setup() {
  Serial.begin(9600); //串口波特率9600（PC端使用）
  track_pinint( );    //循迹引脚初始化
  motor_pinint();     //电机引脚初始化
}

void frontforward()
{int a;
 a=forward_inf();
    switch (a)
   {case 0:Turnfront_F(); break;
    case 1:Turnleft();  break;
    case -1:Turnright(); break;
    }
}

void rightforward()
{int b;
 b=rightward_inf();
    switch (b)
   {case 0:Turnfront_R(); break;
    case 1:Turnleft();  break;
    case -1:Turnright(); break;
    }
}

void leftforward()
{int c;
 c=leftward_inf();
    switch (c)
   {case 0:Turnfront_L(); break;
    case 1:Turnleft();  break;
    case -1:Turnright(); break;
   }
}

void backforward()
{int d;
 d=rightward_inf();
    switch (d)
   {case 0:Turnfront_B(); break;
    case 1:Turnleft();  break;
    case -1:Turnright(); break;
    }
}

void loop() {
  int s1,s2,s3,s4;
  s1=crossroad_F();
  while(s1!=-1) {frontforward; s1=crossroad_F();}//走到第一个左岔道
  _stop();
  delay(1000);//拿一号
  frontforward;
  s1=crossroad_F();
  while(s1!=1) {frontforward; s1=crossroad_F();}//走到第一个右岔道
  rightforward; //右拐
  s2=crossroad_R();
  while(s2!=-1) {rightforward;s2=crossroad_R();}//第一个前岔道
  _stop();
  delay(1000);//拿二号
  rightforward;
  while(s2!=-1) {rightforward;s2=crossroad_R();}//第二个前岔道
  _stop();
  delay(1000);//拿三号
  leftforward;
  while(s3!=1) {leftforward;s3=crossroad_L();}
  backforward;
  while(s4!=1) {backforward;s4=crossroad_B();}
  rightforward;
  while(s2!=-1) {rightforward;s2=crossroad_R();}
  _stop(); //拿四号
  rightforward;
  while(s2!=1) {rightforward;s2=crossroad_R();} 
  backforward;//后拐
  while(s4!=1) {backforward;s4=crossroad_B();}//路口
  _stop();//放物块
  backforward;
  while(s4!=1) {backforward;s4=crossroad_B();}
  _stop();//放
  backforward;
  while(s4!=1) {backforward;s4=crossroad_B();}
  _stop();//放
  backforward;
  while(s4!=1) {backforward;s4=crossroad_B();}
  _stop();//放
  _stop();
  delay(100000);
}
