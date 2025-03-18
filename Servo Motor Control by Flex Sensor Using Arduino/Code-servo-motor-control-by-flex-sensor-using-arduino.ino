#include <Servo.h>
// header for controller servo
Servo servo; //keeping name of servo SERVO itself
int sensorvalue =0;
void setup()
{
            pinMode(A0,INPUT);// voltage divider value input
            pinMode(3,OUTPUT);// PWM output to servo
            servo.attach(3);// telling where signal pin of servo attached(must be a PWM pin)
}
void loop()
{
            sensorvalue = analogRead(A0); //read analog value from sensor
            servo.write((sensorvalue-250)/2); //to avoid initial positioning of servo we need to neutralize the default voltage provided by voltage divider( setting servo position based on ADC result)
}