CAN Transmitter Code (Arduino Nano):
#include <SPI.h>          //Library for using SPI Communication 
#include <mcp2515.h>      //Library for using CAN Communication
#include <DHT.h>          //Library for using DHT sensor 
#define DHTPIN A0       
#define DHTTYPE DHT11
struct can_frame canMsg;
MCP2515 mcp2515(10);
DHT dht(DHTPIN, DHTTYPE);     //initilize object dht for class DHT with DHT pin with STM32 and DHT type as DHT11
void setup() 
{
  while (!Serial);
  Serial.begin(9600);
  SPI.begin();               //Begins SPI communication
  dht.begin();               //Begins to read temperature & humidity sesnor value
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS,MCP_8MHZ); //Sets CAN at speed 500KBPS and Clock 8MHz
  mcp2515.setNormalMode();
}
void loop() 
{
  int h = dht.readHumidity();       //Gets Humidity value
  int t = dht.readTemperature();    //Gets Temperature value
  canMsg.can_id  = 0x036;           //CAN id as 0x036
  canMsg.can_dlc = 8;               //CAN data length as 8
  canMsg.data[0] = h;               //Update humidity value in [0]
  canMsg.data[1] = t;               //Update temperature value in [1]
  canMsg.data[2] = 0x00;            //Rest all with 0
  canMsg.data[3] = 0x00;
  canMsg.data[4] = 0x00;
  canMsg.data[5] = 0x00;
  canMsg.data[6] = 0x00;
  canMsg.data[7] = 0x00;
  mcp2515.sendMessage(&canMsg);     //Sends the CAN message
  delay(1000);
}
CAN Receiver Code (Arduino UNO):
#include <SPI.h>              //Library for using SPI Communication 
#include <mcp2515.h>          //Library for using CAN Communication
#include <LiquidCrystal.h>    //Library for using LCD display
const int rs = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8;  
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);  //Define LCD display pins RS,E,D4,D5,D6,D7
struct can_frame canMsg; 
MCP2515 mcp2515(10);                 // SPI CS Pin 10 
void setup() {
  lcd.begin(16,2);                   //Sets LCD as 16x2 type
  lcd.setCursor(0,0);                //Display Welcome Message
  lcd.print("CIRCUIT DIGEST");
  lcd.setCursor(0,1);
  lcd.print("CAN ARDUINO");
  delay(3000);
  lcd.clear();
  SPI.begin();                       //Begins SPI communication
  Serial.begin(9600);                //Begins Serial Communication at 9600 baudrate 
  mcp2515.reset();                          
  mcp2515.setBitrate(CAN_500KBPS,MCP_8MHZ); //Sets CAN at speed 500KBPS and Clock 8MHz 
  mcp2515.setNormalMode();                  //Sets CAN at normal mode
}
void loop() 
{
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) // To receive data (Poll Read)
  {
     int x = canMsg.data[0];         
     int y = canMsg.data[1];       
      lcd.setCursor(0,0);          //Display Temp & Humidity value received at 16x2 LCD
      lcd.print("Humidity : ");
      lcd.print(x);
      lcd.setCursor(0,1);
      lcd.print("Temp : ");
      lcd.print(y);
      delay(1000);
      lcd.clear();
    }
}