/*-----( Import needed libraries )-----*/
#include <PinChangeInterrupt.h>
/*-----( Declare Constants and Pin Numbers )-----*/
#define LED_Left 13
#define LED_Right 12
/*-----( Declare Variables )-----*/
////setup buttons
int PB_Left_int = 8;
int PB_Right_int= 7;
///////////////State of buttons
boolean buttonPushedLeft = false;
boolean buttonPushedRight = false;
////////Bluetooth///////////
char INBYTE;
unsigned long oldTime = millis();
unsigned long newTime= millis();
unsigned long elapseTime;
long sendrev;
long prevrev;
bool request;
bool conn;
int wait;
//////Hall Effect Sensor///////
long rev;
long old_rev;
volatile int old_time; // in order to store the time value of the current state, to be used in next state
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
  long sendrev=0;
  long prevrev=0;
  bool request=false;
  bool conn=false;
  int wait=0;
  //////////////////
  //Hall Sensor//
  attachPinChangeInterrupt (18, magnet_detected, RISING);
  old_time = 0;
  old_rev = 0;
  rev = 0;
  //////////////////
}

void loop() {
  ///////////////////HALL SENSOR/////////////////////////
  if (rev != old_rev){
    old_rev = rev;
 }
  ///////////////////////////////////////////////////////
  ///////////////////BLUETOOTH///////////////////////////
  request = msgReq();
  msgSend(request);
  ///////////////////////////////////////////////////////
  ////////////////////TURNING LIGHTS/////////////////////
  int buttonStateLeft = digitalRead(PB_Left_int);
  int buttonStateRight= digitalRead(PB_Right_int);
  if (buttonPushedLeft == true){
    blink_left();
    }else {digitalWrite(LED_Left,LOW);}
  if (buttonPushedRight == true){
    blink_right();
    }else {digitalWrite(LED_Right, LOW);}
  ///////////////////////////////////////////////////////
  
}

/*-----( Functions )-----*/

//////////////////////////TURNING LIGHTS////////////////////////////////////////
//Interrupts
void ISR_left(){
  buttonPushedLeft = !buttonPushedLeft;
  
  }
 void ISR_right(){
  buttonPushedRight = !buttonPushedRight;
  }
///////////////////////////////////////////////////
void blink_left(){
      // blinking loop
        digitalWrite (LED_Left, LOW);
        delay (500);
        digitalWrite (LED_Left, HIGH);
        delay (500);
}
void blink_right(){      
      // blinking loop
        digitalWrite (LED_Right, LOW);
        delay (500);
        digitalWrite (LED_Right, HIGH);
        delay (500);
}
////////////////////////////////////////////////////////////////////////////////
//////////////////////////////BLUETOOTH/////////////////////////////////////////
bool msgReq() {//wait for command to be sent
  INBYTE = Serial.read();
  if (INBYTE == '1') {
    return true;
  }
  else {
    return false;
  }
}
void msgSend(bool request) {
  if (request) {
    //Get the time elapsed
    newTime= millis();
    elapseTime= newTime-oldTime;
    //number of revs since last request
    sendrev=rev-prevrev;
    prevrev=rev;
    //reset time counter
    oldTime=millis();
    //send data
    Serial.println(elapseTime);
    Serial.println(sendrev);
    }
  
  request=false; //reset request to false
}
////////////////////////////////////////////////////////////////////////////////
/////////////////////////////HALL SENSOR////////////////////////////////////////
void magnet_detected(){
  rev++;
  }
////////////////////////////////////////////////////////////////////////////////

