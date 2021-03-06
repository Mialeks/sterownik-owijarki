#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
#include <EEPROM.h>

#define LCD_ADDR  0x27

#define BTN_BACK  10    // przycisk
#define BTN_NEXT  12     // przycisk dalej  
#define BTN_PREV  13      // przycisk cofnij
#define BTN_OK    11     //przycisk ok

int gestoscsznura;
int pauzapoczatek;
int pauzakoniec;
int czasdonoz;
int przerwanoz;
int czascofania;
int startsilownika;
int czasdonoz1;
int przerwanoz1;
int czascofania1;
int startsilownika1;
int gestoscsznura1;
int pauzapoczatek1;
int syg = 0;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int t1 = 0;
int t2 = 0;
int t3 = 0;
int t = 0;
int d = 0;
unsigned long aktualnyCzas333 = 0;
unsigned long zapamietanyCzas333 = 0;
unsigned long roznicaCzasu333 = 0;
unsigned long aktualnyCzas444 = 0;
unsigned long zapamietanyCzas444 = 0;
unsigned long roznicaCzasu444 = 0;

int aa = 1;
int aa1 = 0;




unsigned long aktualnyCzas = 0;
unsigned long zapamietanyCzas = 0;
unsigned long roznicaCzasu = 0;

unsigned long zapamietanyCzas22 = 0;
unsigned long roznicaCzasu22 = 0;

unsigned long zapamietanyCzas23 = 0;
unsigned long roznicaCzasu23 = 0;

unsigned long zapamietanyCzas24 = 0;
unsigned long roznicaCzasu24 = 0;

unsigned long zapamietanyCzas25 = 0;
unsigned long roznicaCzasu25 = 0;

unsigned long zapamietanyCzas1 = 0;
unsigned long roznicaCzasu1 = 0;

unsigned long zapamietanyCzas2 = 0;
unsigned long roznicaCzasu2 = 0;

unsigned long zapamietanyCzas3 = 0;
unsigned long roznicaCzasu3 = 0;

unsigned long zapamietanyCzas4 = 0;
unsigned long roznicaCzasu4 = 0;


unsigned long zapamietanyCzas5 = 0;
unsigned long roznicaCzasu5 = 0;


unsigned long zapamietanyCzas6 = 0;
unsigned long roznicaCzasu6 = 0;

int RPWM = 6;  // regulator silnika
int LPWM = 9;
// timer 0
int L_EN = 8;
//int R_EN = 8;

int p1 = 0;
int s = 0;
int s1 = 1;
int s2 = 0;
int s3 = 0;
int s4 = 0;
int s5 = 0;
int s6 = 0;
int s7 = 0;
int s8 = 0;
int s9 = 0;
int s10 = 0;
int s11 = 0;
int b1 = 0;
int b2 = 0;
int z1 = 0;
int z2 = 0;
int z = 0;
int x = 0;
int x1 = 0;
int x2 = 0;

int stan = 0;

int czasStop = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct {
  String label;
  int minVal;
  int maxVal;
  int currentVal;
  void (*handler)();
} STRUCT_MENUPOS;

typedef enum {
  BACK, NEXT, PREV, OK, NONE
} ENUM_BUTTON;

LiquidCrystal_PCF8574 lcd(LCD_ADDR);
STRUCT_MENUPOS menu[7];

int currentMenuPos = 0;
int menuSize;
bool isInLowerLevel = false;
int tempVal;









void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setBacklight(255);
  pinMode(A2, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(3, OUTPUT);
  zaladujParametry();
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(BTN_NEXT, INPUT_PULLUP);
  pinMode(BTN_PREV, INPUT_PULLUP);
  pinMode(BTN_BACK, INPUT_PULLUP);
  pinMode(BTN_OK, INPUT_PULLUP);

  menu[0] = {"Gestosc sznura", 0, 100, gestoscsznura, GESTOSC_SZNURA};
  menu[1] = {"Pauza poczatek", 0, 100, pauzapoczatek, PAUZA_POCZATEK};
  menu[2] = {"Pauza koniec", 0, 100, pauzakoniec, PAUZA_KONIEC};
  menu[3] = {"Czas do noz", 0, 100, czasdonoz, CZAS_DO_NOZ};
  menu[4] = {"Przerwa noz", 0, 100, przerwanoz, PRZERWA_NOZ};
  menu[5] = {"Czas cofania", 0, 100, czascofania, CZAS_COFANIA};
  menu[6] = {"start silownika", 0, 100, startsilownika, START_SILOWNIKA};


  menuSize = sizeof(menu) / sizeof(STRUCT_MENUPOS);
}

void loop() {

  drawMenu();

  aktualnyCzas = millis();

  roznicaCzasu22 = aktualnyCzas - zapamietanyCzas22;
  roznicaCzasu23 = aktualnyCzas - zapamietanyCzas23;
  roznicaCzasu24 = aktualnyCzas - zapamietanyCzas24;
  roznicaCzasu25 = aktualnyCzas - zapamietanyCzas25;

  roznicaCzasu = aktualnyCzas - zapamietanyCzas;
  roznicaCzasu1 = aktualnyCzas - zapamietanyCzas1;
  roznicaCzasu2 = aktualnyCzas - zapamietanyCzas2;
  roznicaCzasu3 = aktualnyCzas - zapamietanyCzas3;
  roznicaCzasu4 = aktualnyCzas - zapamietanyCzas4;
  roznicaCzasu5 = aktualnyCzas - zapamietanyCzas5;
  roznicaCzasu6 = aktualnyCzas - zapamietanyCzas6;
//  digitalWrite(R_EN, HIGH);
  digitalWrite(L_EN, HIGH);

  if ((digitalRead(2) == LOW) && (p1 == 0)) {

    zapamietanyCzas = aktualnyCzas;
    Serial.println("start");
    p1 = 1;
    s = 1;
  }
  if ((roznicaCzasu >= 95000UL) && (s == 1)) {   // czas ponownego zalaczenia belki
    p1 = 0;
    Serial.println("stop");
    s = 0;
    s1 = 1;

  }
  ///////////////////////  p1 = 1 start programu /////////////////////////////////////
  pauzapoczatek1 = map(pauzapoczatek, 0, 1, 0, 100);
  czasStop = map(pauzakoniec, 0, 1, 0, 100);
  czasdonoz1 = map(czasdonoz, 0, 1, 0, 100);
  przerwanoz1 = map(przerwanoz, 0, 1, 0, 100);
  czascofania1 = map(czascofania, 0, 1, 0, 100);
  gestoscsznura1 = map(gestoscsznura, 0, 100, 0, 255);
  startsilownika1 = map(startsilownika, 0, 1, 0, 100);
  ///////////////// silnik w prawo na okreslony czas ///////////////////////////////
  if ((p1 == 1) && (s1 == 1) && (digitalRead(2) == LOW)) {
    Serial.println("silnik prawo");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Start");
    lcd.setCursor(0, 1);
    lcd.print("Silownika");
    Serial.print(startsilownika1);
    
    tone(A1, 3500);
  
   // syg = 1;
    digitalWrite(3, HIGH);
    analogWrite(RPWM, 250); // silownik prawo
    roznicaCzasu1 = 0;
    zapamietanyCzas1 = aktualnyCzas;
    s1 = 0;
    s2 = 1;
    stan = 1;
  }
  if ((roznicaCzasu1 >= 3500UL) && (s2 == 1)) {
  //  digitalWrite(A2, HIGH);
  //  
//  lcd.clear();
  //  lcd.setCursor(0, 0);
  //  lcd.print("Rozpoczynam");
  }



  if ((roznicaCzasu1 >= startsilownika1) && (s2 == 1)) {
    Serial.println("stop silnik prawo");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pauza");
    lcd.setCursor(0, 1);
    lcd.print("Poczatek");
    
    noTone(A1);
   // syg = 0;
    analogWrite(RPWM, 0);
    s2 = 0;
    s3 = 1;
    roznicaCzasu2 = 0;
    zapamietanyCzas2 = aktualnyCzas;
    Serial.println("przerwa uzytkownika");
  }
  //////////////////// stop okreslony przez uzytkowinika ////////////////////////////
  if ((roznicaCzasu2 >= pauzapoczatek1) && (s3 == 1)) {
    Serial.println("koniec przerwy uzytkownika");
    s3 = 0;
    s4 = 1;
    


  }




  ///////////////////////// silnik w lewo z predkoscia okreslona przez uzytkowinika ///////////////////////
  if (s4 == 1) {
    Serial.println("silnik lewo predkosc uzytkow, oczek. na krancowke");
    analogWrite(LPWM, gestoscsznura); // silownik prawo
    s4 = 0;
    s5 = 1;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Gestosc");
    lcd.setCursor(0, 1);
    lcd.print("Sznura");
  }

  /////////////////////////////////// krancowka stop na czas przez uzytkownika /////////////
  if ((digitalRead(4) == LOW) && (s5 == 1)) {
    Serial.println("silnik stop lewo krancowka");
    Serial.println("przerwa uzytkownika");
    analogWrite(LPWM, 0); // silownik stop

    s5 = 0;
    s6 = 1;

    roznicaCzasu3 = 0;
    zapamietanyCzas3 = aktualnyCzas;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pauza");
    lcd.setCursor(0, 1);
    lcd.print("Koniec");

  }

  ////////////  stop przez uzytkownika   //////////////////////////////////////
  if ((roznicaCzasu3 >= czasStop) && (s6 == 1)) {
    Serial.println("koniec przerwy uzytkownika");
    s6 = 0;
    s7 = 1;

  }

  //////////// uciecie sznurka //////////////////////////////////////
  if (s7 == 1) {
    Serial.println("uciecie sznurka");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ucinanie");
    lcd.setCursor(0, 1);
    lcd.print("Sznurka");
    
    analogWrite(LPWM, 255);

    s7 = 0;
    s8 = 1;

    roznicaCzasu4 = 0;
    zapamietanyCzas4 = aktualnyCzas;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Czas do ");
    lcd.setCursor(0, 1);
    lcd.print("Noz");
  }

  if ((roznicaCzasu4 >= czasdonoz1) && (s8 == 1)) {
    Serial.println("stop silownik");
    s8 = 0;
    s9 = 1;
    analogWrite(LPWM, 0); // silownik stop
    roznicaCzasu5 = 0;
    zapamietanyCzas5 = aktualnyCzas;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Przerwa ");
    lcd.setCursor(0, 1);
    lcd.print("Noz");
  }

  /////// 1s przerwy /////////////////////

  if ((roznicaCzasu5 >= przerwanoz1) && (s9 == 1)) {
    Serial.println("ciecie...");
    

    s9 = 0;
    s10 = 1;

  }





  /////////////// powrot na do krancowki /////////////////////

  if (s10 == 1) {
    Serial.println("silownik w miejce gotowosci");
    analogWrite(RPWM, 250);
    digitalWrite(3, LOW);
    s10 = 0;
    s11 = 1;

    roznicaCzasu6 = 0;
    zapamietanyCzas6 = aktualnyCzas;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Czas");
    lcd.setCursor(0, 1);
    lcd.print("Cofania ");
  }

  if ((roznicaCzasu6 >= czascofania1) && (s11 == 1)) {
    Serial.println("oczekiwanie na sygnal");
    s11 = 0;

    analogWrite(RPWM, 0); // silownik stop
    stan = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Oczekiwanie ");
    lcd.setCursor(0, 1);
    lcd.print("Na sygnal");
  }
/*
if(syg == 1) {
  aktualnyCzas333 = millis();
  roznicaCzasu333 = aktualnyCzas333 - zapamietanyCzas333;
  
   if ((roznicaCzasu333 >= 200UL) && (aa == 1)) {
  
    zapamietanyCzas333 = aktualnyCzas333;  //Zapamietaj aktualny czas
               tone(A3, 3500);
               aa = 0;
              aa1 = 1;
}
//Pobierz liczbe milisekund od startu   

  
  //Je??li r????nica wynosi ponad 10s
  if ((roznicaCzasu333 >= 400UL) && (aa1 == 1)) {
  
   
  aa1 = 0;
  aa = 1;
  tone(A2, 3800);
          
}
*/

  int stopp = 0;
  int stopp2 = 0;

  if ((stan == 1) && (stopp == 1)) {
    stopp = 0;
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("OWIJANIE");
    stopp2 = 1;
  }

  if ((stan == 0) && (stopp2 == 1)) {
    stopp2 = 0;
    stopp = 1;
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Oczekiwanie");
  }


}

ENUM_BUTTON getButton() {
  if (!digitalRead(BTN_BACK)) return BACK;
  if (!digitalRead(BTN_NEXT)) return NEXT;
  if (!digitalRead(BTN_PREV)) return PREV;
  if (!digitalRead(BTN_OK)) return OK;

  return NONE;
}

void drawMenu() {
  static unsigned long lastRead = 0;
  static ENUM_BUTTON lastPressedButton = OK;
  static unsigned int isPressedSince = 0;
  int autoSwitchTime = 500;

  ENUM_BUTTON pressedButton = getButton();

  if (pressedButton == NONE && lastRead != 0) {
    isPressedSince = 0;
    return;
  }
  if (pressedButton != lastPressedButton) {
    isPressedSince = 0;
  }

  if (isPressedSince > 3) autoSwitchTime = 70;
  if (lastRead != 0 && millis() - lastRead < autoSwitchTime && pressedButton == lastPressedButton) return;

  isPressedSince++;
  lastRead = millis();
  lastPressedButton = pressedButton;

  switch (pressedButton) {
    case NEXT: handleNext(); break;
    case PREV: handlePrev(); break;
    case BACK: handleBack(); break;
    case OK: handleOk(); break;
  }

  lcd.home();
  lcd.clear();
  if (isInLowerLevel) {
    lcd.print(menu[currentMenuPos].label);
    lcd.setCursor(0, 1);
    lcd.print(F("> "));

    if (menu[currentMenuPos].handler != NULL) {
      (*(menu[currentMenuPos].handler))();
    } else {
      lcd.print(tempVal);
    }
  } else {
    lcd.print(F("Menu glowne"));
    lcd.setCursor(0, 1);
    lcd.print(F("> "));

    lcd.print(menu[currentMenuPos].label);
  }
}

void handleNext() {
  if (isInLowerLevel) {
    tempVal++;
    if (tempVal > menu[currentMenuPos].maxVal) tempVal = menu[currentMenuPos].maxVal;
  } else {
    currentMenuPos = (currentMenuPos + 1) % menuSize;
  }
}

void handlePrev() {
  if (isInLowerLevel) {
    tempVal--;
    if (tempVal < menu[currentMenuPos].minVal) tempVal = menu[currentMenuPos].minVal;
  } else {
    currentMenuPos--;
    if (currentMenuPos < 0) currentMenuPos = menuSize - 1;
  }
}

void handleBack() {
  if (isInLowerLevel) {
    isInLowerLevel = false;
  }
}

void handleOk() {
  if (menu[currentMenuPos].handler != NULL && menu[currentMenuPos].maxVal <= menu[currentMenuPos].minVal) {
    (*(menu[currentMenuPos].handler))();
    return;
  }
  if (isInLowerLevel) {
    menu[currentMenuPos].currentVal = tempVal;
    isInLowerLevel = false;
  } else {
    tempVal = menu[currentMenuPos].currentVal;
    isInLowerLevel = true;
  }
}

/* Funkcje-uchwyty u??ytkownika */

void GESTOSC_SZNURA() {
  lcd.print(tempVal / 1);
  gestoscsznura = (tempVal / 1);
  EEPROM.update(1, gestoscsznura);
}
void PAUZA_POCZATEK() {
  lcd.print(tempVal / 1);
  pauzapoczatek = (tempVal / 1);
  EEPROM.update(2, pauzapoczatek);
}
void PAUZA_KONIEC() {
  lcd.print(tempVal / 1);
  pauzakoniec = (tempVal / 1);
  EEPROM.update(3, pauzakoniec);
}
void CZAS_DO_NOZ() {
  lcd.print(tempVal / 1);
  czasdonoz = (tempVal / 1);
  EEPROM.update(4, czasdonoz);

}
void PRZERWA_NOZ() {
  lcd.print(tempVal / 1);
  przerwanoz = (tempVal / 1);
  EEPROM.update(5, przerwanoz);

}
void CZAS_COFANIA() {
  lcd.print(tempVal / 1);
  czascofania = (tempVal / 1);
  EEPROM.update(6, czascofania);
}
void START_SILOWNIKA() {
  lcd.print(tempVal / 1);
  startsilownika = (tempVal / 1);
  EEPROM.update(7, startsilownika);
}

void zaladujParametry() {
  Serial.print('Rozmiar pamieci EEPROM: ');
  Serial.println(EEPROM.length());
  //  if ( EEPROM.length() == 7 ) { //w jakis sposob sprawdzic czy pamiec jest zainicjalizowania
  Serial.println("Czytam wartosci z pamieci");
  gestoscsznura = EEPROM.read(1);
  pauzapoczatek = EEPROM.read(2);
  pauzakoniec = EEPROM.read(3);
  czasdonoz = EEPROM.read(4);
  przerwanoz = EEPROM.read(5);
  czascofania = EEPROM.read(6);
  startsilownika = EEPROM.read(7);
  //  } else {
  //   Serial.println('Inicjalizuje pamiec domyslna');
  //   temperaturaUST = 60;
  //   SERWO_ZAMKNIJ  = 7;
  //   SERWO_SRODEK   = 0;
  //   SERWO_UCHYL    = 0;
  //  EEPROM.update(1, gestoscsznura);
  //   EEPROM.update(2, pauzapoczatek);
  //  EEPROM.update(3, pauzakoniec);
  //  EEPROM.update(4, czasdonoz);
  //    EEPROM.update(5, przerwanoz);
  //   EEPROM.update(5, czascofania);
  //   EEPROM.update(5, startsilownika);
  // }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
