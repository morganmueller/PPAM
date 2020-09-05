#include <Servo.h>

Servo criticalServo;

int pos = 0;

char incoming_char = 0;
long ptime;
int delay_time = 2000;
int state = 0;
int otherState = 0;

int increment;        // increment to move for each interval
  int  updateInterval;      // interval between updates
  unsigned long lastUpdate; // last update of position

boolean forward = false ;   // state variable

unsigned long ts = millis () ;   // time accounting.
#define DELAY 20



void setup() {

  Serial.begin(9600);
  pinMode(13, OUTPUT);
  Serial.println("setup over, Move to loop");
  ptime = millis();

  criticalServo.attach(9);
}

void loop() {
  //if (Serial.available()) {



  incoming_char = Serial.read();
  if (millis() - ptime > delay_time ) {
    state++;
    ptime = millis();
  }
  

//  while (otherState <= 5) {
//    for (pos = 0; pos <= 180; pos += 1) {
//      criticalServo.write(pos);
//     // delay(15);
//      Serial.println(otherState);
//
//    }
//
//    for (pos = 45; pos >= 0; pos -= 1) {
//      criticalServo.write(pos);
//    //  delay(15);

 if (millis () - ts >= DELAY && millis() < 10000)
  {
    ts += DELAY ;   // setup timestamp for next time.
    if (forward)
    {
      criticalServo.write (-- pos) ;  // progress the servo
      if (pos == 0)  // test for reverse
        forward = false ;
       // delay(5000);
    }
    else
    {
      criticalServo.write (++ pos) ;  // progress the servo
      if (pos == 90)  // test for reverse
        forward = true ;
    }
  }

  
   if (state % 2 == 0 && millis() > 12000) {
    digitalWrite(13, HIGH);
    Serial.println("ON");
    Serial.println(state);
  }

   if ( state % 2 == 1 && millis() > 15000) {

    digitalWrite(13, LOW);
    Serial.println("OFF");
  }
  // state = state %2
  //}
}
