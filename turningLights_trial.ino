
// digital pin 2 has a pushbutton attached to it.
int pushButton = 2;

// the setup routine :
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
  pinMode(13, OUTPUT);
}

// the loop routine:
void loop() {
  // read the input pin:
  int buttonState = digitalRead(pushButton);
  // print out the state of the button:
  Serial.println(buttonState);

  if (buttonState != 0){
      digitalWrite(13,HIGH);
      delay(1000);
      digitalWrite(13,LOW);
      delay(1000);
    }
  delay(1);        // delay in between reads for stability
}

