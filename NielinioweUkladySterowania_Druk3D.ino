//----------------------------------------------------------------------------------------------------------------------
//                                                        PINY
//----------------------------------------------------------------------------------------------------------------------

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

// piny extruder
#define E0_STEP_PIN 26
#define E0_DIR_PIN 28
#define E0_ENABLE_PIN 24

// piny ograniczenia
#define X_MAX_PIN 2
#define Y_MAX_PIN 15
#define Z_MAX_PIN 19

// wentylatory
#define FAN_0 9
#define FAN_1 44

//grzalki
#define HEATER_0 9

//termistory
#define TEMP_0_PIN 13
#define TEMP_1_PIN 15
#define TEMP_BED_PIN 14

//----------------------------------------------------------------------------------------------------------------------
//                                                       Nagrzewanie
//----------------------------------------------------------------------------------------------------------------------
#define a -4.52095923146464e-07 // Zmienne pobrane z Matlba
#define b 0.000771676586865781
#define c -0.546501992496493
#define d 242.002559782888

//----------------------------------------------------------------------------------------------------------------------
//                                                       Biblioteki
//----------------------------------------------------------------------------------------------------------------------

#include <stdlib.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(16, 17, 23, 25, 27, 29);

//----------------------------------------------------------------------------------------------------------------------
//                                                      Zmienne globalne
//----------------------------------------------------------------------------------------------------------------------

//ruch
int kieruneka = 0, kierunekb = 0, kierunekc = 0, kieruneke = 0;
int kroki = 0;
bool czy_mam_odp = 0;
String mes;
int kroka = 0, krokb = 0, krokc = 0, kroke = 0;

//grzalka
double x, y;
int temp, i = 0;
double e, calka;
int u, P;



//----------------------------------------------------------------------------------------------------------------------
//                                                           Kod
//----------------------------------------------------------------------------------------------------------------------
void setup() {
  setUp();
  leveling();
  Serial.print("leveling complite \n");
  while(y < 200) {
    heat();
  }
  Serial.print("heat complite \n");
}

void loop() {
  heat();
  if(y > 195 && y <= 205) {
    while (Serial.available() > 0 ) {
      receiveData();
    } 
    moveMotors();
  }
  finishMove();
}

//----------------------------------------------------------------------------------------------------------------------
//                                                       Funkcje
//----------------------------------------------------------------------------------------------------------------------

void setUp() {
  //ruch
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

  pinMode(E0_ENABLE_PIN, OUTPUT); // ustawienie pinu jako wyjscie
  pinMode(E0_DIR_PIN, OUTPUT);
  pinMode(E0_STEP_PIN, OUTPUT);
  digitalWrite(E0_ENABLE_PIN, LOW);
  digitalWrite(E0_DIR_PIN, LOW);

  pinMode(X_MAX_PIN, INPUT_PULLUP);
  pinMode(Y_MAX_PIN, INPUT_PULLUP);
  pinMode(Z_MAX_PIN, INPUT_PULLUP);

  //grzalka
  lcd.begin( 20, 4);
  pinMode(HEATER_0,OUTPUT);
  pinMode(FAN_0, OUTPUT);
  pinMode(FAN_1, OUTPUT);
  pinMode(FAN_0, HIGH);
  pinMode(FAN_1, HIGH);
}

//ruch
void receiveData() {
  mes = Serial.readStringUntil('\n');

  sscanf(mes.c_str(),"a %d b %d c %d e %d", &kroka, &krokb, &krokc, &kroke);

  czy_mam_odp = 1;

  kieruneka = kroka < 0; // sprawdzanie czy jest minus czy nie i uzaleznienie od tego kierunku
  kierunekb = krokb < 0;
  kierunekc = krokc < 0;
  kieruneke = kroke < 0;

  digitalWrite(X_DIR_PIN, kieruneka); // przypisanie danego kierunku
  digitalWrite(Y_DIR_PIN, kierunekb);
  digitalWrite(Z_DIR_PIN, kierunekc);
  digitalWrite(E0_DIR_PIN, kieruneke);

  kroka = abs(kroka); // gdyby minus to zamien ilisc krokow na plus
  krokb = abs(krokb);
  krokc = abs(krokc);
  kroke = abs(kroke);
}

void moveMotors() {
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

  if (kroke > 0) {
    digitalWrite(E0_STEP_PIN, HIGH);
    kroke--;
  }
    
  delay(1);
  digitalWrite(X_STEP_PIN, LOW);
  digitalWrite(Y_STEP_PIN, LOW);
  digitalWrite(Z_STEP_PIN, LOW);
  digitalWrite(E0_STEP_PIN, LOW);
  delay(1);
}

void finishMove() {
  if(kroka == 0 && krokb == 0 && krokc == 0 && kroke == 0 && czy_mam_odp == 1) {
    Serial.println("ok");
    czy_mam_odp = 0;
  }
}

void leveling() {
  int finish = 1;
  while(finish){
  if(!digitalRead(X_MAX_PIN)) {
    digitalWrite(X_STEP_PIN, HIGH);      
    kroka--;
  }
 
  if (!digitalRead(Y_MAX_PIN)) {
    digitalWrite(Y_STEP_PIN, HIGH);
    krokb--;
  }
    
  if (!digitalRead(Z_MAX_PIN)) {
    digitalWrite(Z_STEP_PIN, HIGH);
    krokc--;
  }
    
    delay(1);
    digitalWrite(X_STEP_PIN, LOW);
    digitalWrite(Y_STEP_PIN, LOW);
    digitalWrite(Z_STEP_PIN, LOW);
    delay(1);

    if(digitalRead(X_MAX_PIN) && digitalRead(Y_MAX_PIN) && digitalRead(Z_MAX_PIN)) {
      finish = 0;
    }
  }
  int counter = 4000;
  kieruneka = 1;
  kierunekb = 1;
  kierunekc = 1;
  kieruneke = 1;
  digitalWrite(X_DIR_PIN, kieruneka); // przypisanie danego kierunku
  digitalWrite(Y_DIR_PIN, kierunekb);
  digitalWrite(Z_DIR_PIN, kierunekc);
  digitalWrite(E0_DIR_PIN, kieruneke);
  while(counter > 0) {
    digitalWrite(X_STEP_PIN, HIGH);
    digitalWrite(Y_STEP_PIN, HIGH);
    digitalWrite(Z_STEP_PIN, HIGH);
    delay(1);
    digitalWrite(X_STEP_PIN, LOW);
    digitalWrite(Y_STEP_PIN, LOW);
    digitalWrite(Z_STEP_PIN, LOW);
    delay(1);
    counter--;
  }
  kieruneka = 0;
  kierunekb = 0;
  kierunekc = 0;
  kieruneke = 0;
  digitalWrite(X_DIR_PIN, kieruneka); // przypisanie danego kierunku
  digitalWrite(Y_DIR_PIN, kierunekb);
  digitalWrite(Z_DIR_PIN, kierunekc);
  digitalWrite(E0_DIR_PIN, kieruneke);
}

//grzanie
void heat() {
  lcd.setCursor(0, 0);
  lcd.print(analogRead(13));
  temp = analogRead(13);
  x = (double)temp;
  y = a * x * x * x + b * x * x + c * x + d;
  lcd.print(" => ");
  lcd.print(y);
  lcd.setCursor(0,2);
  lcd.print(P);
  lcd.setCursor(0,3);
  lcd.print(calka);
  if(y < 220) {
    e = 200 - y;
    if(y < 200) {
      calka = calka + 0.2 * e;
    }
    if(y > 202 && y <= 210) {
      calka = calka + 0.2 * e;
    }
    if(y > 195 && y <= 202) {
      calka = 630;
    }
    u = round(255/180 * e + 0.1 * calka);
    P = round(255/180 * e);
    if (u > 255) {
      u*255; 
    }
    if ( u < 0) {
      u = 0;
    }
    analogWrite(10, u);
  }
  P = round(255/180 * e);
}
