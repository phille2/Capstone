int rev;
int old_rev;
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
 old_rev = 0;
 rev = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("running");
 if (rev != old_rev){
    old_rev = rev;
    Serial.println(rev);
 }
}

void magnet_detected(){
  //Serial.println("detected");
  rev++;
    
  }
