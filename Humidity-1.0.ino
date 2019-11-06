#include <LiquidCrystal.h>
#include <DFR_Key.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

#define INJECTION 6
#define INJVOLT 51    //51xVolt

//#define LUCE 255
#define ANA_IN_0 0
#define TESTER 1
#define btnRIGHT 0
#define btnUP 1
#define btnDOWN 2
#define btnLEFT 3
#define btnSELECT 4
#define btnNONE 5
int adc_key_in = 0;
int lcd_key = 0;
int luce=64;

float misura_di_tensione = 0.0;
float muro;

DFR_Key keypad;
int localKey = 0;

void setup() {
  analogWrite(10,luce);
  stop_inj;
  credit();
  keypad.setRate(10);
  delay(2500);
}

void start_inj()
{
  analogWrite(INJECTION, INJVOLT);  
}

void stop_inj()
{
  analogWrite(INJECTION,0);
}


void credit() {
lcd.begin(16, 2);
lcd.setCursor(0, 0);
lcd.print("Humidity 1.0");
lcd.setCursor(0,1);
lcd.print("by Zaino Marco");
}

void loop() {
misura_di_tensione = analogRead(TESTER);
muro=misura_di_tensione*5/1023;
lcd.clear();

if (muro < 3)
{
  lcd.setCursor(0, 0);
  lcd.print("Volt muro: ");
  lcd.print(muro);
}
else
{
  lcd.setCursor(0, 0);
  lcd.print("Attesa sonda");
}

lcd.setCursor(0,1);
if ((muro > 0)&&(muro < 3))
{
  start_inj();
  lcd.print("Injection 1 Volt");
}
else
{
  stop_inj();
}

localKey = keypad.getKey();

  switch (localKey)
  {
    case 1:
    credit();
    break;
  case 3:
  luce+=64;
  if (luce>255)
    {
      luce = 255;
    }
  analogWrite(10,luce);
  break;
  case 4:
  luce-=64;
  if (luce<0)
    {
      luce = 0;
    }
  analogWrite(10,luce);
  break;
  }

delay(1000);
}
