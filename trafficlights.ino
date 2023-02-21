/*

*/
const int TrigPin=3;      //设置发射脚位
const int EchoPin=2;      //设置接收脚位
const int LED_G1=8;
const int LED_Y1=10;
const int LED_R1=12;
const int LED_G2=7;
const int LED_Y2=6;
const int LED_R2=5;
float cm;
float dis = 330;//浮点型数据类型（加小数点，提高精准度）
int mroad = 1;
int nroad = 0;

void setup() {
  
	Serial.begin(9600);

	pinMode(TrigPin,OUTPUT);
	pinMode(EchoPin,INPUT);
	pinMode(LED_G1, OUTPUT);
	pinMode(LED_R1, OUTPUT);
	pinMode(LED_Y1, OUTPUT);
	pinMode(LED_G2, OUTPUT);
	pinMode(LED_R2, OUTPUT);
	pinMode(LED_Y2, OUTPUT);

	digitalWrite(LED_G1, HIGH);
  	delay(300);   
  
	digitalWrite(LED_Y1, HIGH);   // turn the LED on (HIGH is the voltage level)                    // wait for a second
	delay(300);   
  	digitalWrite(LED_Y1, LOW);
  
  	digitalWrite(LED_R1, HIGH);
    delay(300); 
  	digitalWrite(LED_R1, LOW);
  
	digitalWrite(LED_G2, HIGH);
    delay(300);   
  	digitalWrite(LED_G2, LOW);

	digitalWrite(LED_Y2, HIGH);
    delay(300);   
  	digitalWrite(LED_Y2, LOW);

	digitalWrite(LED_R2, HIGH);
}

void loop() {
	digitalWrite(TrigPin,LOW);        //用低高低电平发送脉冲给Trigpin引脚
	delayMicroseconds(2);             //微秒级延时
	digitalWrite(TrigPin,HIGH);
	delayMicroseconds(10);
	digitalWrite(TrigPin,LOW);
	cm=pulseIn(EchoPin,HIGH)/58.0;    //读取脉冲宽度，换算成厘米
	Serial.print(cm);                 //显示距离
	Serial.print("cm");               //显示单位
	Serial.println();                 //回车
		if(cm<dis && mroad == 1){
  			mroad = 0;
  			digitalWrite(LED_G1, LOW);
      
  			digitalWrite(LED_Y1, HIGH);      	
    		delay(1000); 
    		digitalWrite(LED_Y1, LOW);
     		digitalWrite(LED_R2, LOW);       
    		delay(1000); 
    		digitalWrite(LED_Y1, HIGH);
        	digitalWrite(LED_R2, HIGH);
    		delay(1000); 
  			digitalWrite(LED_Y1, LOW);    
     		digitalWrite(LED_R2, LOW);
      		delay(1000);
      		digitalWrite(LED_G2, HIGH);
            digitalWrite(LED_R1, HIGH);
			}
  		if(cm>=dis && mroad == 0){
            mroad = 1;
  			digitalWrite(LED_G2, LOW);
      
  			digitalWrite(LED_Y2, HIGH);   //闪烁   	
    		delay(1000); 
    		digitalWrite(LED_Y2, LOW);
     		digitalWrite(LED_R1, LOW);       
    		delay(1000); 
    		digitalWrite(LED_Y2, HIGH);
        	digitalWrite(LED_R1, HIGH);
    		delay(1000); 
  			digitalWrite(LED_Y2, LOW);    
     		digitalWrite(LED_R1, LOW);
      		delay(1000);
      		digitalWrite(LED_G1, HIGH);
            digitalWrite(LED_R2, HIGH);
			}
  	delay(1000);	
}

 
 




