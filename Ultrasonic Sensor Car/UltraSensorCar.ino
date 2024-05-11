#include <Servo.h>

#define TRIG_PINL 41
#define ECHO_PINL 40

#define TRIG_PINR 53
#define ECHO_PINR 52

#define TRIG_PINIL 31
#define ECHO_PINIL 30

#define TRIG_PINIR 44
#define ECHO_PINIR 45

#define TURN_PIN 5
#define THROTTLE_PIN 9

Servo turn;
Servo throttle;

long duration = 0;
int dist = 0;
int closeObject = 60;
int i = 0;


long distanceL = 0;
long distanceR = 0;
long distanceIL = 0;
long distanceIR = 0;

void setup() {
   Serial.begin(9600);
   turn.attach(TURN_PIN);
   throttle.attach(THROTTLE_PIN);
   throttle.writeMicroseconds(1500);

   Serial.print("Starting Test in: ");
   
   for(int i = 5; i >= 0; i--)
   {
    Serial.println(i);
    delay(1000);
   }

   throttle.writeMicroseconds(1560); //The neutral rest position.
   turn.write(90);


  pinMode(TRIG_PINL, OUTPUT);
  pinMode(ECHO_PINL, INPUT);
  pinMode(TRIG_PINR, OUTPUT);
  pinMode(ECHO_PINR, INPUT);
  pinMode(TRIG_PINIL, OUTPUT);
  pinMode(ECHO_PINIL, INPUT);
  pinMode(TRIG_PINIR, OUTPUT);
  pinMode(ECHO_PINIR, INPUT);
 
}

void loop() {
  distanceL = distance(TRIG_PINL, ECHO_PINL);
  distanceR = distance(TRIG_PINR, ECHO_PINR);
  distanceIR = distance(TRIG_PINIR, ECHO_PINIR);
  distanceIL = distance(TRIG_PINIL, ECHO_PINIL);
 
  //For Debugging
  Serial.print("------------------------------- \n\r");
  Serial.print("Time Elapsed: "); Serial.println(i);
  Serial.print("\n\r\n\r");
  Serial.print("Lsensor: "); Serial.println(distanceL);
  Serial.print("IRsensor: "); Serial.println(distanceIR);
  Serial.print("Rsensor: "); Serial.println(distanceR);
  Serial.print("ILsensor: "); Serial.println(distanceIL);
  Serial.print("\n\r");
  Serial.print("---------------------------");

  ++i;
  delay(1000);

  if (distanceL <= closeObject && distanceIR >= closeObject && distanceIL >= closeObject)
  {
    turn.write(120);
    Serial.print("------------------------------- \n\r");
  Serial.print("\n\r\n\r");
  Serial.print("Lsensor: "); Serial.println(distanceL);
  Serial.print("IRsensor: "); Serial.println(distanceIR);
  Serial.print("Rsensor: "); Serial.println(distanceR);
  Serial.print("ILsensor: "); Serial.println(distanceIL);
  Serial.print("\n\r");
    Serial.println("Suppose to turn 120");
    Serial.print("\n\r---------------------------");
    delay(300);
  }

  else if (distanceL <= closeObject && distanceIR <= closeObject && distanceIL >= closeObject)
  {
    turn.write(150);
    Serial.print("------------------------------- \n\r");
  Serial.print("\n\r\n\r");
  Serial.print("Lsensor: "); Serial.println(distanceL);
  Serial.print("IRsensor: "); Serial.println(distanceIR);
  Serial.print("Rsensor: "); Serial.println(distanceR);
  Serial.print("ILsensor: "); Serial.println(distanceIL);
  Serial.print("\n\r");
    Serial.println("Suppose to turn 150");
    Serial.print("\n\r---------------------------");
    delay(300);
  }

  else if ((distanceL <= closeObject && distanceIR <= closeObject && distanceIL <= closeObject) || (distanceL <= closeObject && distanceIL <= closeObject))
  {
    turn.write(180);
    Serial.print("------------------------------- \n\r");
  Serial.print("\n\r\n\r");
  Serial.print("Lsensor: "); Serial.println(distanceL);
  Serial.print("IRsensor: "); Serial.println(distanceIR);
  Serial.print("Rsensor: "); Serial.println(distanceR);
  Serial.print("ILsensor: "); Serial.println(distanceIL);
  Serial.print("\n\r");
    Serial.println("Suppose to turn 180");
    Serial.print("\n\r---------------------------");
    delay(300);
  }

  else if (distanceR <= closeObject && distanceIL >= closeObject && distanceIR >= closeObject)
  {
    turn.write(60);
    Serial.print("------------------------------- \n\r");
  Serial.print("\n\r\n\r");
  Serial.print("Lsensor: "); Serial.println(distanceL);
  Serial.print("IRsensor: "); Serial.println(distanceIR);
  Serial.print("Rsensor: "); Serial.println(distanceR);
  Serial.print("ILsensor: "); Serial.println(distanceIL);
  Serial.print("\n\r");
    Serial.println("Suppose to turn 60");
    Serial.print("\n\r---------------------------");
    delay(300);
  }

  else if (distanceR <= closeObject && distanceIL <= closeObject && distanceIR >= closeObject && distanceL >= closeObject)
  {
    turn.write(30);
    Serial.print("------------------------------- \n\r");
  Serial.print("\n\r\n\r");
  Serial.print("Lsensor: "); Serial.println(distanceL);
  Serial.print("IRsensor: "); Serial.println(distanceIR);
  Serial.print("Rsensor: "); Serial.println(distanceR);
  Serial.print("ILsensor: "); Serial.println(distanceIL);
  Serial.print("\n\r");
    Serial.println("Suppose to turn 30");
    Serial.print("\n\r---------------------------");
    delay(300);
  }

  else if ((distanceR <= closeObject && distanceIR <= closeObject && distanceIL <= closeObject) || (distanceR <= closeObject && distanceIR <= closeObject))
  {
    turn.write(0);
    Serial.print("------------------------------- \n\r");
  Serial.print("\n\r\n\r");
  Serial.print("Lsensor: "); Serial.println(distanceL);
  Serial.print("IRsensor: "); Serial.println(distanceIR);
  Serial.print("Rsensor: "); Serial.println(distanceR);
  Serial.print("ILsensor: "); Serial.println(distanceIL);
  Serial.print("\n\r");
    Serial.println("Suppose to turn 0");
    Serial.print("\n\r---------------------------");
    delay(300);
  }

  else if (distanceIL <= closeObject && distanceIR <= closeObject )
  {
    turn.write(180);
    Serial.print("------------------------------- \n\r");
  Serial.print("\n\r\n\r");
  Serial.print("Lsensor: "); Serial.println(distanceL);
  Serial.print("IRsensor: "); Serial.println(distanceIR);
  Serial.print("Rsensor: "); Serial.println(distanceR);
  Serial.print("ILsensor: "); Serial.println(distanceIL);
  Serial.print("\n\r");
    Serial.println("Suppose to turn 180");
    Serial.print("\n\r---------------------------");
    delay(300);
  }

  else if ((distanceR <= closeObject && distanceIR <= closeObject && distanceIL <= closeObject && distanceL <= closeObject) || (distanceR <= closeObject && distanceL <= closeObject && distanceIL >= closeObject && distanceIR >= closeObject) || (distanceIR <= closeObject && distanceIL <= closeObject && distanceL >= closeObject && distanceR >= closeObject) ||
  (distanceR <= 3 || distanceIR <= 3 || distanceIL <= 3 || distanceL <= 3))
  {
    Serial.print("------------------------------- \n\r");
  Serial.print("\n\r\n\r");
  Serial.print("Lsensor: "); Serial.println(distanceL);
  Serial.print("IRsensor: "); Serial.println(distanceIR);
  Serial.print("Rsensor: "); Serial.println(distanceR);
  Serial.print("ILsensor: "); Serial.println(distanceIL);
  Serial.print("\n\r");
 
    Serial.println("Suppose to Reverse");
    Serial.print("\n\r---------------------------");
    turn.write(150);
    throttle.writeMicroseconds(1420);
    delay(2000);
    throttle.writeMicroseconds(1500);
    delay(2000);
    turn.write(90);
    throttle.writeMicroseconds(1560);
  }

  else
  {
    turn.write(90);
    throttle.writeMicroseconds(1560);
    delay(500);
  }

}


int distance(const int& t, const int& e)
{
  digitalWrite(t, LOW);
  delayMicroseconds(2);

  digitalWrite(t, HIGH);
  delayMicroseconds(10);

  digitalWrite(t, LOW);
  duration = pulseIn(e, HIGH);
  dist = duration * 0.034/2;

  return dist;
  delayMicroseconds(2);
}