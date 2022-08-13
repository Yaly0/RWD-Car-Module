#include <LiquidCrystal.h>
#include <Servo.h>

const double WD = 0.02; // wheel diameter in m
const int RPM = 5470; // max rpm
const double MAXS = RPM * WD
              * 4 * atan(1) * 60 / 1000; // max speed
const int INANG = 35; // max inner angle
const int OUTANG = 25; // max outer angle
const int BEEPDUR = 100; // Beep duration
const int BEEPFR = 840; // Beep frequency
const double SSPD = 0.0343; // Sound speed in cm/us

const byte MF = 6; // Motor forward pin
const byte MR = 5; // Motor reverse pin
const byte LS = 9; // Left servo pin
const byte RS = 10; // Right servo pin
const byte BZ = 7; // Buzzer pin
const byte TPOT = A0; // Turning potentiometer pin
const byte DPOT = A1; // Driving potentiometer pin
const byte USS = A2; // Ultrasonic sensor pin



Servo rServo, lServo;

LiquidCrystal lcd(2, 3, 4, 8, 11, 12);

int val, read, cm, currentSpeed = 0, a = 0;
unsigned long previousMillis = 0;

void setup() {
  analogWrite(MF, 0);
  analogWrite(MR, 0);
    
  rServo.attach(RS);
  lServo.attach(LS);
  
  lcd.begin(16, 2);
  lcd.print("Speed:0km/h");
  lcd.setCursor(0, 1);
  lcd.print("Shift:P");
}

void loop() {
  drive();
  turn();
  checkSensor();
  delay(200);
}

void drive() {
  read = analogRead(DPOT);
  val = round(map2(read, 0, 1023, -int(MAXS), int(MAXS)));
  if(val > currentSpeed) currentSpeed++;
  else if(val < currentSpeed) currentSpeed--;
  setSpeed(currentSpeed);
  printS(currentSpeed);
}

void turn() {
  read = analogRead(TPOT);
  if(read < 512) { // turn right
    val = map(read, 0, 1023, 90 - INANG, 90 + INANG);
    rServo.write(val);
    val = map(read, 0, 1023, 90 - OUTANG, 90 + OUTANG);
    lServo.write(val);
  } else { // turn left
    val = map(read, 0, 1023, 90 - OUTANG, 90 + OUTANG);
    rServo.write(val);
    val = map(read, 0, 1023, 90 - INANG, 90 + INANG);
    lServo.write(val);
  }
}

void checkSensor() {
  cm = SSPD/2 * readUltrasonicDistance(USS, USS);
  if(cm < 200) beep(cm);
}

void setSpeed(double speed) { // "speed" in km/h
  int pwm = 255 * speed / MAXS;
  if(abs(speed) > MAXS) return;
  if(speed >= 0 ) {
    analogWrite(MF, pwm);
    analogWrite(MR, 0);
  } else {
    analogWrite(MR, -pwm);
    analogWrite(MF, 0);
  }
}

void printS(int S) {
  String speed = String(abs(S)) + "km/h ", shift = "P";
  lcd.setCursor(6, 0);
  lcd.print(speed);
  if(S > 0) shift = "D";
  if(S < 0) shift = "R";
  lcd.setCursor(6, 1);
  lcd.print(shift);
}

long readUltrasonicDistance(int trig, int echo) {
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  pinMode(echo, INPUT);
  return pulseIn(echo, HIGH);
}

void beep(int cm) {
  int dur = cm * 2;
  unsigned long currentMillis = millis();
  if (cm < 25) {
    tone(BZ, BEEPFR, BEEPDUR * 4);
  } else if (a && currentMillis - previousMillis >= dur) {
    previousMillis = currentMillis;
    a = !a;
  tone(BZ, BEEPFR, BEEPDUR);
  } else if (!a && currentMillis - previousMillis >= BEEPDUR) {
    previousMillis = currentMillis;
    a = !a;
    noTone(BZ);
  }
}

double map2(double x, double in_min, 
            double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) 
                      / (in_max - in_min) + out_min;
} // same as map but using double instead of long
