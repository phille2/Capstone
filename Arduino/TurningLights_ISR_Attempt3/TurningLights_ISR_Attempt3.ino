#include <PinChangeInterrupt.h>
////setup button
int PB_Left_int = 8;
int PB_Right_int= 7;



///////////////State of buttons
boolean buttonPushedLeft = false;
boolean buttonPushedRight = false;


#define LED_Left 13
#define LED_Right 12
//#define PB_Left 8
//#define PB_Right 7


void setup() {
  //set OUTPUTS
  Serial.begin(9600);
  pinMode(LED_Left, OUTPUT);
  pinMode(LED_Right,OUTPUT);
  pinMode(PB_Left_int, INPUT);
  pinMode(PB_Right_int, INPUT);
  
  //attach interrupt
  attachPinChangeInterrupt(0,ISR_left,RISING);
  attachPinChangeInterrupt(23,ISR_right,RISING);

}
///////////////////////////////////////////////////
void loop() {
  // put your main code here, to run repeatedly:
  int buttonStateLeft = digitalRead(PB_Left_int);
  int buttonStateRight= digitalRead(PB_Right_int);
  Serial.println(buttonStateLeft);
  Serial.println(buttonStateRight);
  if (buttonPushedLeft == true){
    blink_left();
    }else {digitalWrite(LED_Left,LOW);}
  if (buttonPushedRight == true){
    blink_right();
    }else {digitalWrite(LED_Right, LOW);}
  }
/////////////////////////////////////////////////
 void ISR_left(){
  Serial.println("enters ISR_Left");
  buttonPushedLeft = !buttonPushedLeft;
  
  }
 void ISR_right(){
  Serial.println("enters ISR_right");
  buttonPushedRight = !buttonPushedRight;
  }
///////////////////////////////////////////////////
void blink_left(){
      // blinking loop
        Serial.println("enters LEFT");
        digitalWrite (LED_Left, LOW);
        delay (500);
        digitalWrite (LED_Left, HIGH);
        delay (500);
}
void blink_right(){      
      // blinking loop
        Serial.println("enters RIGHT");
        digitalWrite (LED_Right, LOW);
        delay (500);
        digitalWrite (LED_Right, HIGH);
        delay (500);
}
