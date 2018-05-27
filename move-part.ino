int LSPEED = 5;     //左轮转速
int RSPEED = 6;     //右轮转速
int LDIR = 4;      //左轮方向
int RDIR = 7;     //右轮方向
char onspeed =100;  //启动速度
int ontime=1000;   //启动时间
void stop(void){                 //停止
       analogWrite (LSPEED,0);   
       analogWrite (RSPEED,0);     
}  
 
void advance(char a,char b){           //前进
	//add code here
}  
void back_off (char a,char b) {          //后退
	//add code here
}
void turn_L (char a,char b) {           //左转
       analogWrite (LSPEED,a);
       digitalWrite(LDIR,LOW);    
       analogWrite (RSPEED,b);    
       digitalWrite(RDIR,HIGH);
}
void turn_R (char a,char b) {           //右转
	//add code here
}

void setup(void) { 
    int i;
    pinMode(LDIR, OUTPUT);  
    pinMode(RDIR, OUTPUT);  
    Serial.begin(19200);      //设置串口波特率
    Serial.println("w,s,a,d");
} 

void loop(void) { 
   if(Serial.available()>0){
     char val = Serial.read();
     if(val!=-1){
          switch(val){
             case 'w'://前进
                     advance (onspeed,onspeed);   //PWM调速
                     break;
             case 's'://后退
                     back_off (onspeed,onspeed);
                     break;
             case 'a'://左转
                     turn_L (onspeed,onspeed);
                     break;       
             case 'd'://右转
                     turn_R (onspeed,onspeed);
                     break;          
            }     
          delay(ontime); 
          stop();
       }
      else stop();  
   }
}


