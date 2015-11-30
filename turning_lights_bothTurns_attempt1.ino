// digital pin 2 has a pushbutton attached to it.
//int pushButton = 2;
int pushButtonLeft = 2;
int buttonPushedLeft = 0;
int pushButtonRight = 3;
int buttonPushedRight = 0;
// the setup routine :
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pushButtonLeft, INPUT);
  pinMode (pushButtonRight, INPUT);
  pinMode(13, OUTPUT);// output for LEFT SIGNAL
  pinMode(1, OUTPUT);// output for RIGHT SIGNAL
  
}

// the loop routine:
void loop() {
  // read the input pin:
  int buttonStateLeft = digitalRead(pushButtonLeft);
  int buttonStateRight = digitalRead(pushButtonRight);
  // print out the state of the button:
  Serial.println(buttonStateLeft);//set button to pushed
  if (buttonStateLeft !=0){
    buttonPushedLeft = 1;
    delay(10);
  }
  if (buttonStateRight !=0){
    buttonPushedRight = 1;
    delay(10);
  }
  Serial.println(buttonPushedLeft);
  //Serial.println(buttonStateRight); //check if we put in two inputs into one Serial Port
  if (buttonPushedLeft == 1){
    buttonPushedRight = 0;
    digitalWrite(13,LOW);
    delay(500);
    digitalWrite(13,HIGH);
    delay(500);
    int buttonStateLeft = digitalRead(pushButtonLeft);
    Serial.println(buttonStateLeft);
    if (buttonStateLeft !=0){
      buttonPushedLeft = 0;
    }
  }else {
    digitalWrite(13,LOW);
  }
  if (buttonPushedRight == 1){
    buttonPushedLeft = 0;
    digitalWrite(1,LOW);
    delay(500);
    digitalWrite(1,HIGH);
    delay(500);
    int buttonStateRight = digitalRead(pushButtonRight);
    if(buttonStateRight != 0){
      buttonPushedRight=0;
    }
  }else {
    digitalWrite(1,LOW);
  }
  delay(1);        // delay in between reads for stability
}



