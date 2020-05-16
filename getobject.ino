#define servo 10
#define xp1 51
#define xp2 49
#define xp3 24
#define xp4 25
#define bjlow1   33          //bj1转传送带的步进电机    1是连接DIR+到单片机IO口的   其他：DIR-,PUL-接GND EN-接GND EN+不接
#define bjlow2   35             //2是连接PUL+到单片机IO口的
#define PIN_TRIG 49
#define PIN_ECHO 51
#define xp1 46
#define xp2 48
#define xp3 50
#define xp4 52


float cm;
float temp;
#include "Rfid_D_Think_M50.h"
#include <Servo.h>
#define BLOCK_NO  0    // 待读取的块号 = 0

Rfid_D_Think_M50 rfid( Serial1 ); // 使用 硬件串口Serial1 与 Rfid 模块通信

Servo myservo;

int xpnum[5];
int recogrfid(uint8_t data[]){
  int flag=0;
      while(!flag){
        rfid.enableAntenna();
        
        if( rfid.read(BLOCK_NO, data) ){// 若读取成功，在串口0打印读取结果
           flag=1; //读取成功标识
           for(int j=0; j<4; j++){
               Serial.print(data[j], HEX);                                    
               Serial.print(' ');
               }
            Serial.println();
          }
        else{                          // 若读取失败
            Serial.println("no card!");
            }
        rfid.disableAntenna();            // 读操作之后关闭天线，否则芯片发热
        delay(300);                         //缓0.3s接着读
      }
   return flag;
}

void stepperinit(){ //步进电机初始化
   pinMode(bjlow1,OUTPUT);
    pinMode(bjlow2,OUTPUT);
    
         //这里HIGH 设定的是步进电机正转
    
  }

void xpinit(){ 
  pinMode(xp1,OUTPUT);         //继电器的com
  pinMode(xp2,OUTPUT);
  pinMode(xp3,OUTPUT);
  pinMode(xp4,OUTPUT);
    xpnum[1]=xp1;
    xpnum[2]=xp2;
    xpnum[3]=xp3;
    xpnum[4]=xp4; 
}


void stepper_rotate(int Tus,int num,int circle,int bj)       //这个是步进电机转的函数，第一个参数是脉冲的周期，改变可改变转速，circle是转的圈数，bj是步进电机的PUL+接到哪个口了
{
  int i=num*circle,     //这个num  一圈 多少步
      j;
  for(j=0;j<i;j++)
  {
    digitalWrite(bj, HIGH);             //这里模拟产生脉冲信号
    delayMicroseconds((int)(Tus/2));
    digitalWrite(bj, LOW);
    delayMicroseconds((int)(Tus/2));
  }
}





void upsomedis(int dis,int num)    //上升一段距离
{  float s=0,x;
  int i=0;
   digitalWrite(bjlow1,HIGH);  //上升
   x=(num/200)*7.2;
      while(s<dis){
   stepper_rotate(100000,num,1,bjlow2); 
   s+=x;
   }
} 
  void downsomedis(int dis,int num)     //下降一段距离
  {  float s=0,x;
  int i=0;
   digitalWrite(bjlow1,LOW); //下降
   x=(num/200)*7.2;
      while(s<dis){
   stepper_rotate(100000,num,1,bjlow2); 
   s+=x;
   }
   }
 /*  void movesomedis(int dis,int num);    //移动一段距离
{  float s=0,x;
  int i=0;
  x=(num/200)*7.2;
  while(s<dis){
   i++;
   s+=x;
   }
  stepper_rotate(100000,num,i,bjlow2); 
   }
   */

 int getdis(){
   digitalWrite(PIN_TRIG, LOW);  
   delayMicroseconds(2);  
   digitalWrite(PIN_TRIG, HIGH); 
   delayMicroseconds(10);  
   digitalWrite(PIN_TRIG, LOW);     
   temp = float(pulseIn(PIN_ECHO, HIGH));  
   cm = (temp*17)/1000;   
   Serial.print("Echo = ");  
   Serial.print(temp);  
   Serial.print(",  Distance = ");   
   Serial.print(cm);  
   Serial.println("cm"); 
    return cm;
    }


void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
  
    // 使能天线并设置射频工作模式
    // 以 ISO15693 为例
    if( rfid.enableAntenna( rfid.ISO15693 ) ){
        Serial.println("init ok");
    }else{
        Serial.println("init failed");
        for(;;);
    }
    stepperinit();            //步进电机
    xpinit();                 //吸盘
    myservo.attach(10);       //舵机
}

void getob(int col[],int pos[]){
    int flag=0,i;
     uint8_t data[4];
    recogrfid(data);
    for(i=1;i<5;i++){
       if( data[2]==col[i])
          { Serial.print(col[i]);
            Serial.print("  sucess!");
            flag=1;
          }
           Serial.println();
           break;}
   
    if(flag==1){ 
     myservo.write(pos[i]);
    digitalWrite(xpnum[i],LOW);
    delay(500);}
  

  }
    
void loop() {
  // put your main code here, to run repeatedly:
   uint8_t data1[4],data2[4],data3[4],data4[4],data5[4],data6[4],data7[4],data8[4];   //存物块信息
  float s,s1;
   int col[5],pos[5],flag=0,i;

//第一个物块
   
    //myservo.write(10);    //吸盘最底下
  upsomedis(30,200);   //升30cm，每段升7.2cm
    s=getdis(); 
   if(s!=0) 
   {s1=s+25+50-80;
   downsomedis(s1-5,50);}
   else {
    Serial.print("bug!!");
    downsomedis(25,50);
   }
 
   while(!recogrfid(data1))               //识别物块颜色
   {downsomedis(2,20);
    }
    col[1]=data1[1]; //记录颜色
     // 吸盘吸           
     downsomedis(1,10);
      digitalWrite(xp1,HIGH);
      delay(2000);
     upsomedis(35,100);
   delay(1000);
     pos[1]=10 ;       //放物块要转回来的角度位置
   flag=1;
     
     myservo.write(65);
//第二个物块
      s=getdis(); 
   if(s!=0) 
   {s1=(s+25+25)-80;
   downsomedis(s1-5,50);}
   else {
    Serial.print("bug!!");
    downsomedis(5,50);
   }
 
   while(!recogrfid(data2))               //识别物块颜色
   {downsomedis(2,20);
    }
   
 
    col[2]=data2[1];
      //吸盘吸
      digitalWrite(xp2,HIGH);
     delay(2000);
     upsomedis(15,100);
     delay(1000);
      
    pos[2]=65;           //放物块要转回来的角度位置
    
 myservo.write(125);
//第三个物块
   s=getdis(); 
     if(s!=0) 
   {s1=(s+25)-50;
   downsomedis(s1-5,50);}
   else {
    Serial.print("bug!!");
    downsomedis(5,50);
   }
 
   while(!recogrfid(data3))               //识别物块颜色
   {downsomedis(2,20);
    }
    col[3]=data3[1];
      //吸盘吸
      digitalWrite(xp3,HIGH);
     delay(2000);
     upsomedis(40,100);
     delay(1000);
    recogrfid(data3);               //识别物块颜色
    col[3]=data3[1];
      //吸盘吸
      digitalWrite(xp3,HIGH);
  
      
    pos[3]=125;         //放物块要转回来的角度位置
   myservo.write(200);

   
//第四个物块
    s=getdis(); 
     if(s!=0) 
   {s1=(s+25)-80;
   downsomedis(s1-5,50);}
   else {
    Serial.print("bug!!");
    downsomedis(15,50);
   }
 
   while(!recogrfid(data4))               //识别物块颜色
   {downsomedis(2,20);
    }
   
    col[4]=data4[1];
      //吸盘吸
      digitalWrite(xp4,HIGH);
     delay(2000);
      upsomedis(5,100);
    pos[4]=200;         //放物块要转回来的角度位置


 upsomedis(40,100);
 //放1物块  
   //识别
    recogrfid(data5);
    for(i=1;i<5;i++){
       if( data5[2]==col[i])
          { Serial.print(col[i]);
            Serial.print("  sucess!");
            flag=1;
          }
           Serial.println();
           break;}
    
    if(flag==1){ myservo.write(pos[i]);
    digitalWrite(xpnum[i],LOW);
   delay(500);}
   flag=0;
   
   getob(col,pos);
  
   


   
}
