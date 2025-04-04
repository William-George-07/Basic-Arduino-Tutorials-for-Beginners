#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 10, 11, 12, 13); // REGISTER SELECT PIN,ENABLE PIN,D4 PIN,D5 PIN, D6 PIN, D7 PIN
char ADCSHOW[5]; //initializing a character of size 5 for showing the ADC result
void setup()
{
// set up the LCD's number of columns and rows:
lcd.begin(16, 2);
}
void loop()
{
// set the cursor to column 0, line 1
lcd.print("   CIRCUIT DIGEST"); //print name
lcd.setCursor(0, 1); // set the cursor to column 0, line
lcd.print("ADC RESULT:"); //print name
String ADCVALUE = String(analogRead(A0)); //intailizing a string and storing ADC value in it 
ADCVALUE.toCharArray(ADCSHOW, 5); // convert the reading to a char array 
lcd.print(ADCSHOW); //showing character of ADCSHOW
lcd.print("   ");
lcd.setCursor(0, 0); // set the cursor to column 0, line1
}