/**实现左右右左转向**/
int LSPEED = 5;     //左轮转速
int RSPEED = 6;     //右轮转速
int LDIR = 4;      //左轮方向
int RDIR = 7;     //右轮方向
char onspeed =100;  //启动速度
int ontime=1000;   //启动时间
bool bstop=false;
int grayscalePinL=A2;
int grayscalePinR=A3;
int grayscalePinRR=A4;




void stop(void){                 //停止
       analogWrite (LSPEED,0);   
       analogWrite (RSPEED,0);     
}  
 
void advance(char a,char b){           //前进
       analogWrite (LSPEED,a);             //PWM调速
       digitalWrite(LDIR,HIGH);    
       analogWrite (RSPEED,b);    
       digitalWrite(RDIR,HIGH);
}  
void back_off (char a,char b) {          //后退
       analogWrite (LSPEED,a);
       digitalWrite(LDIR,LOW);   
       analogWrite (RSPEED,b);    
       digitalWrite(RDIR,LOW);
}
void turn_L (char a,char b) {           //左转
       analogWrite (LSPEED,a);
       digitalWrite(LDIR,LOW);    
       analogWrite (RSPEED,b);    
       digitalWrite(RDIR,HIGH);
}
void turn_R (char a,char b) {           //右转
       analogWrite (LSPEED,a);
       digitalWrite(LDIR,HIGH);    
       analogWrite (RSPEED,b);    
       digitalWrite(RDIR,LOW);
}

void setRoads(char valL,char valR){
   if(valL&&(valR==0))
  {
    turn_R(onspeed,onspeed);
    delay(2);
  }
  
 
    else if((valL==0)&&valR) 
  {
    //speed
    turn_L(onspeed,onspeed);          //检测到左边传感器遇到黑线，说明小车右偏了，立即往左转一点
    delay(2);
                                //后面道理相同
  }    
  else
  {
    advance(onspeed,onspeed); 
    delay(2);
  } 
}

void setup(void) { 
    pinMode(LDIR, OUTPUT);  
    pinMode(RDIR, OUTPUT);  
    pinMode(grayscalePinL,INPUT);
    pinMode(grayscalePinRR,INPUT);
    pinMode(grayscalePinR,INPUT);
    Serial.begin(9600);      //设置串口波特率
} 
void loop() 
{ 
  char valL,valRR,valR;
  int i=0;
  if(!bstop)
  {
  valL=digitalRead(grayscalePinL);    
  valRR=digitalRead(grayscalePinRR);
  valR=digitalRead(grayscalePinR);  

  if(i=0&&(valR==0)&&(valL==0))
  {
    turn_L(onspeed,onspeed);          //检测到左边传感器遇到黑线，说明小车右偏了，立即往左转一点
    delay(1000);
    for(int j=0;j<5;j++)
    setRoads(valL,valR);
    i++;
  }

  if(i==1&&(valR==0)&&(valRR==0))
  {
    turn_R(onspeed,onspeed);
    delay(1000);
    for(int j=0;j<5;j++)
    setRoads(valL,valR);
    i++;
  }

if(i==2&&(valL==0)&&(valR==0))
{
  turn_R(onspeed,onspeed);
  delay(1000);
  for(int j=0;j<5;j++)
  setRoads(valL,valR);
  i++;
}

if(i==3&&(valL==0)&&(valR)==0)
{
  turn_L(onspeed,onspeed);
  delay(1000);
  for(int j=0;j<5;j++)
  setRoads(valL,valR);
}

  setRoads(valL,valR);
  }
else
    stop();
}






