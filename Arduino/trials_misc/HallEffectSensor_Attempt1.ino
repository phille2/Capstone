int rev;
int rpm;
volatile int old_time; // in order to store the time value of the current state, to be used in next state
int perimeter;// pi*diameter
int diameter; // diameter of the tire
void setup() {
  // put your setup code here, to run once:

 Serial.begin(9600);
 attachInterrupt (0, magnet_detected, RISING);
 old_time = 0;
 perimeter = 0;
 diameter = 20;
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("running");
 
}

void magnet_detected(){
  rev++;
  Serial.println(rev);
  Serial.println("Magnet detected");
//   if (rev == 5){
//    Serial.println("20 revoloutions completed");
//   // old_time = millis();
//    Serial.println(old_time);
//    }
  }
