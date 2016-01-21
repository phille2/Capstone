//setup button
int PB_Left_int = 0;
int PB_Right_int= 1;

///////////////
int buttonPushedLeft = 0;
int buttonPushedRight = 0;
int LEFT = 0;
int RIGHT= 1;
///////////////
//setup LEDs
int LED_Left = 10;
int LED_Right= 11;

volatile int direction_selected = 0;
void setup() {
  //set OUTPUTS
  pinMode(LED_Left, OUTPUT);
  pinMode(LED_Right,OUTPUT);
  
  //attach interrupt
  attachInterrupt(direction_selected,interrupt,RISING);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonStateLeft = digitalRead(PB_Left_int);
  int buttonStateRight= digitalRead(PB_Right_int);
  
  if(buttonStateLeft != 0){
    direction_selected = LEFT; // 0 referring to Left
    }
  if(buttonStateRight != 0){
    direction_selected = RIGHT; // 1 referring to Right
    }
}


void interrupt(){
    if (direction_selected == LEFT){
        digitalWrite (LED_Left, LOW);
        delay (500);
        digitalWrite (LED_Left, HIGH);
        delay (500);
      }else{digitalWrite (LED_Left, LOW);}
    if (direction_selected == RIGHT){
        digitalWrite (LED_Right, LOW);
        delay (500);
        digitalWrite (LED_Right, HIGH);
        delay (500);
      }else{digitalWrite(LED_Right, LOW);}
      
}
