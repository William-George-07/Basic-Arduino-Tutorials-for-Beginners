PROGRAM ON TRANSMITTER SIDE:
#include <avr/io.h>
//header to enable data flow control over pins
#define F_CPU 1000000UL
//telling controller crystal frequency attached
#include <util/delay.h>
//header to enable delay function in program
int main(void)
{
                DDRB =0;//PORTB is set as INPUT
                DDRD |= 1 << PIND1;//pin1 of portD as OUTPUT
                DDRD &= ~(1 << PIND0);//pin0 of portD as INPUT
                PORTD |= 1 << PIND0;
                int UBBRValue = 6;//AS described before setting baud rate 9600BPS
                //Put the upper part of the baud number here (bits 8 to 11)
                UBRRH = (unsigned char) (UBBRValue >> 8);
                //Put the remaining part of the baud number here
                UBRRL = (unsigned char) UBBRValue;
                //Enable the receiver and transmitter
                UCSRB = (1 << RXEN) | (1 << TXEN);
                //Set 2 stop bits and data bit length is 8-bit
                UCSRC = (1 << USBS) | (3 << UCSZ0);
                while (1)
                {
                                if (bit_is_clear(PINC,0))//once button is pressed
                                {
                                                while (! (UCSRA & (1 << UDRE)) );
                                                {
                                                                UDR = 0b11110000;//once transmitter is ready sent eight bit data
                                                }             
                                                _delay_ms(220);
                                }
PROGRAM ON RECEIVER SIDE:
int receiveddata =0;
void setup()
{
                Serial.begin(9600);//serial data rate is set for 9600BPS
                pinMode(0,INPUT);//RXD pin is set for INPUT
                pinMode(1,OUTPUT);
                pinMode(7,OUTPUT);//PIN1,PIN7 are set for output
}
void loop()
{
                if (Serial.available() > 0) //if data received is available
                {
        receiveddata = Serial.read();//read serial data available
                                if (receiveddata == 0)//compare the data received
                                {
                                                PORTD^=(1<<7);//id data matches toggle the LED.
                                }
                }
}