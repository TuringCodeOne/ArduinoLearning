int LSPEED = 5;     //左轮转速
int RSPEED = 6;     //右轮转速
int LDIR = 4;      //左轮方向
int RDIR = 7;     //右轮方向
char onspeed =100;  //启动速度
int ontime=1000;   //启动时间
bool bstop=false;
int grayscalePinL=A2;
int grayscalePinM=A3;
int grayscalePinR=A4;

char start_msg[15] = {
  "Start loop "};                    
int  adc_key_val[5] ={
  30, 150, 360, 535, 760 };
int NUM_KEYS = 5;
int adc_key_in;
int key=-1;
int oldkey=-1;
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

void setup(void) { 
    int i;
    pinMode(LDIR, OUTPUT);  
    pinMode(RDIR, OUTPUT);  
    pinMode(grayscalePinL,INPUT);
    pinMode(grayscalePinM,INPUT);
    pinMode(grayscalePinR,INPUT);

    Serial.begin(19200);      //设置串口波特率
    Serial.println("w,s,a,d");
} 
void loop() 
{ 
  static char x=0;
  char valL,valM,valR;
  if(!bstop)
  {
  valL=digitalRead(grayscalePinL);    
  valM=digitalRead(grayscalePinM);
  valR=digitalRead(grayscalePinR);  

  if((valL==0)&&valM&&valR) 
  {
    //speed
    turn_L(onspeed,onspeed);          //检测到左边传感器遇到黑线，说明小车右偏了，立即往左转一点
    delay(2);
    while(1){
    valM=digitalRead(grayscalePinM);         //循环判断中间传感器度数，
    if(valM==1){  
      turn_L(onspeed,onspeed);                     //如果num2==1说明还没有转到中间位置，继续左转
      delay(2);
    }
    else
      break;                      //检测到num2==0说明转过头了，跳出循环，检测三个传感器的状态再做出相应动作
    }                                       //后面道理相同
  }    
  else if(valM&&valL&&(valR==0))
  {
    turn_R(onspeed,onspeed);
    delay(2);
    while(1){
    valM=digitalRead(grayscalePinM);
    if(valM==1){
      turn_R(onspeed,onspeed);   
      delay(2);}
      else
        break;
    }
  }
  else
  {
    advance(onspeed,onspeed); 
    delay(2);
  } 
  }
  else
    stop();
  adc_key_in = analogRead(7);    // read the value from the sensor  
  key = get_key(adc_key_in);    // convert into key press
  if (key != oldkey) {   // if keypress is detected
    delay(50);      // wait for debounce time
    adc_key_in = analogRead(7);    // read the value from the sensor  
    key = get_key(adc_key_in);    // convert into key press
    if (key != oldkey) {         
      oldkey = key;
      carmove(key);
    }
  }
  //digitalWrite(13, LOW);
}
// Convert ADC value to key number
int get_key(unsigned int input)
{   
  int k;
  for (k = 0; k < NUM_KEYS; k++)
  {
    if (input < adc_key_val[k])
    {  
      return k;  
    }
  }
  if (k >= NUM_KEYS)
    k = -1;     // No valid key pressed
  return k;
}
void carmove(char val) { 
/*     if(val!=-1){
          switch(val){
             case 0://前进
                     advance (onspeed,onspeed);   //PWM调速
                     break;
             case 2://后退
                     back_off (onspeed,onspeed);
                     break;
             case 1://左转
                     turn_L (onspeed,onspeed);
                     break;       
             case 3://右转
                     turn_R (onspeed,onspeed);
                     break;          
            }     
          delay(ontime); 
          stop();
       }
      else stop();  
*/
  if(val!=-1)
  {
    bstop=!bstop;
    }
}




