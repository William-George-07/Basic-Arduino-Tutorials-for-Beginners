#include<LiquidCrystal.h>            //LCD display library
#define ledPin 7
LiquidCrystal lcd(8,9,10,11,12,13);
float value = 3035;                   //Preload timer value (3035 for 4 seconds)
void setup()
{
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("ARDUINO TIMERS");
  delay(2000);
  lcd.clear();
  pinMode(ledPin, OUTPUT);
  pinMode(2,INPUT);
  pinMode(4,INPUT);
  noInterrupts();                       // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = value;                        // preload timer
  TCCR1B |= (1 << CS10)|(1 << CS12);    // 1024 prescaler 
  TIMSK1 |= (1 << TOIE1);               // enable timer overflow interrupt ISR
  interrupts();                         // enable all interrupts
}
ISR(TIMER1_OVF_vect)                    // interrupt service routine for overflow
{
  TCNT1 = value;                                // preload timer
  digitalWrite(ledPin, digitalRead(ledPin) ^ 1);  //Turns LED ON and OFF
}
void loop()
{
  if(digitalRead(2) == HIGH)
  {
    value = value+10;             //Incement preload value
  }
  if(digitalRead(4)== HIGH)
  {
    value = value-10;            //Decrement preload value
  }
  lcd.setCursor(0,0);
  lcd.print(value);
}