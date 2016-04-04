/*-----( Import needed libraries )-----*/
#include <PinChangeInterrupt.h>
/*-----( Declare Constants and Pin Numbers )-----*/
#define LED_Left 13
#define LED_Right 12
/*-----( Declare Variables )-----*/
//Copy in both sets of variables, check for conflicts, Verify.
////setup button
int PB_Left_int = 8;
int PB_Right_int= 7;
///////////////State of buttons
boolean buttonPushedLeft = false;
boolean buttonPushedRight = false;
////////SendRec///////////
int counter = 0;
int LED = 11;
char INBYTE;
unsigned long oldTime = millis();
unsigned long newTime= millis();
unsigned long elapseTime;
//////Hall Effect Sensor///////
int rev;
int old_rev;
int rpm;
volatile int old_time; // in order to store the time value of the current state, to be used in next state
int perimeter;// pi*diameter
int diameter; // diameter of the tire
///////////////////////////////end of variables
void setup() {
  //Turning Lights//
  //set OUTPUTS
  Serial.begin(9600);
  pinMode(LED_Left, OUTPUT);
  pinMode(LED_Right,OUTPUT);
  pinMode(PB_Left_int, INPUT);
  pinMode(PB_Right_int, INPUT);
  //attach interrupt
  attachPinChangeInterrupt(0,ISR_left,RISING);
  attachPinChangeInterrupt(23,ISR_right,RISING);
  //////////////////
  //Bluetooth//

  //////////////////
  //Hall Sensor//
  attachInterrupt (0, magnet_detected, RISING);
  old_time = 0;
  perimeter = 0;
  diameter = 20;
  old_rev = 0;
  rev = 0;
  //////////////////
}

void loop() {
  ///////////////////HALL SENSOR/////////////////////////
  if (rev != old_rev){
    old_rev = rev;
    Serial.println(rev);
 }
  ///////////////////////////////////////////////////////
  ///////////////////BLUETOOTH///////////////////////////
  bool request;
  request = msgReq();
  msgSend(request);
  ///////////////////////////////////////////////////////
  ////////////////////TURNING LIGHTS/////////////////////
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
  ///////////////////////////////////////////////////////
  
}

/*-----( Declare User-written Functions )-----*/

//////////////////////////TURNING LIGHTS////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
//////////////////////////////BLUETOOTH/////////////////////////////////////////
bool msgReq() {
  Serial.println("Press 1 to request Arduino data");
  while(!Serial.available());
  INBYTE = Serial.read();
  if (INBYTE == '1') {
    digitalWrite(LED, LOW);
    delay(50);
    digitalWrite(LED, HIGH);
    return true;
  }
  else {
    return false;
  }
}
void msgSend(bool request) {
  if (request) {
    //newTime=now();
    newTime= millis();
    elapseTime= newTime-oldTime;
    counter++;
    //oldTime=now();
    oldTime=millis();
    Serial.print("Time since last request:  ");
    Serial.println(elapseTime);
    Serial.print("Request number: ");
    Serial.println(counter);
    delay(500);
  }
  request=false; //reset request to false
}
////////////////////////////////////////////////////////////////////////////////
/////////////////////////////HALL SENSOR////////////////////////////////////////
void magnet_detected(){
  //Serial.println("detected");
  rev++;    
  }
////////////////////////////////////////////////////////////////////////////////
