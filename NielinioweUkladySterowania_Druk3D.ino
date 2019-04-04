
// piny konfigurujace silnik x
#define X_STEP_PIN 54
#define X_DIR_PIN 55
#define X_ENABLE_PIN 38

// piny konfigurujace silnik y
#define Y_STEP_PIN 60
#define Y_DIR_PIN 61
#define Y_ENABLE_PIN 56

// piny konfigurujace silnik z
#define Z_STEP_PIN 46
#define Z_DIR_PIN 48
#define Z_ENABLE_PIN 62


#define X_MIN_PIN 3
#define X_MAX_PIN 2
#define Y_MIN_PIN 14
#define Y_MAX_PIN 15
#define Z_MIN_PIN 18
#define Z_MAX_PIN 19

#include <stdlib.h>

int kieruneka = 0, kierunekb = 0, kierunekc = 0;
int kroki = 0;
bool czy_mam_odpowiedziec = 0;

String a;
int kroka = 0, krokb = 0, krokc = 0;

void setup() {
  Serial.begin(115200); // max 250000
  pinMode(X_ENABLE_PIN, OUTPUT); // ustawienie pinu jako wyjscie
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(X_STEP_PIN, OUTPUT);
  digitalWrite(X_ENABLE_PIN, LOW);
  digitalWrite(X_DIR_PIN, LOW);

  pinMode(Z_ENABLE_PIN, OUTPUT); // ustawienie pinu jako wyjscie
  pinMode(Z_DIR_PIN, OUTPUT);
  pinMode(Z_STEP_PIN, OUTPUT);
  digitalWrite(Z_ENABLE_PIN, LOW);
  digitalWrite(Z_DIR_PIN, LOW);

  pinMode(Y_ENABLE_PIN, OUTPUT); // ustawienie pinu jako wyjscie
  pinMode(Y_DIR_PIN, OUTPUT);
  pinMode(Y_STEP_PIN, OUTPUT);
  digitalWrite(Y_ENABLE_PIN, LOW);
  digitalWrite(Y_DIR_PIN, LOW);

  pinMode(X_MAX_PIN, INPUT_PULLUP);
  pinMode(Y_MAX_PIN, INPUT_PULLUP);
  pinMode(Z_MAX_PIN, INPUT_PULLUP);
}

void loop() {

  while (Serial.available() > 0 ) {
    a = Serial.readStringUntil('\n');

    sscanf(a.c_str(),"a %d b %d c %d", &kroka, &krokb, &krokc);

    czy_mam_odpowiedziec = 1;

    kieruneka = kroka < 0; // sprawdzanie czy jest minus czy nie i uzaleznienie od tego kierunku
    kierunekb = krokb < 0;
    kierunekc = krokc < 0;

    digitalWrite(X_DIR_PIN, kieruneka); // przypisanie danego kierunku
    digitalWrite(Y_DIR_PIN, kierunekb);
    digitalWrite(Z_DIR_PIN, kierunekc);

    kroka = abs(kroka); // gdyby minus to zamien ilisc krokow na plus
    krokb = abs(krokb);
    krokc = abs(krokc);
  } 

  if(!digitalRead(X_MAX_PIN) && kroka > 0) {
    digitalWrite(X_STEP_PIN, HIGH);      
    kroka--;
  }
 
  if (!digitalRead(Y_MAX_PIN) && krokb > 0) {
    digitalWrite(Y_STEP_PIN, HIGH);
    krokb--;
  }
    
  if (!digitalRead(Z_MAX_PIN) && krokc > 0) {
    digitalWrite(Z_STEP_PIN, HIGH);
    krokc--;
  }
    
  delay(1);
  digitalWrite(X_STEP_PIN, LOW);
  digitalWrite(Y_STEP_PIN, LOW);
  digitalWrite(Z_STEP_PIN, LOW);
  delay(1);

  if(kroka == 0 && krokb == 0 && krokc == 0 && czy_mam_odpowiedziec == 1) {
    Serial.println("ok");
    czy_mam_odp = 0;
  }
}
