//Eric Phillips-Sheldon
//January 2016
//Bluetooth send and receive code

int counter = 0;
int LED = 13;
char INBYTE;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(50);
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool request;
  request = msgReq();
  msgSend(request);
}
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
  counter++;
  Serial.print("This is message ");
  Serial.println(counter);
  delay(500);
  }
  request=false; //reset request to false
}

