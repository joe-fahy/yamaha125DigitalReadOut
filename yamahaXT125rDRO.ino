
/*
** Example Arduino sketch for SainSmart I2C LCD Screen 16x2
** based on https://bitbucket.org/celem/sainsmart-i2c-lcd/src/3adf8e0d2443/sainlcdtest.ino
** by
** Edward Comer
** LICENSE: GNU General Public License, version 3 (GPL-3.0)

** This example uses F Malpartida's NewLiquidCrystal library. Obtain from:
** https://bitbucket.org/fmalpartida/new-liquidcrystal

** Modified - Ian Brennan ianbren at hotmail.com 23-10-2012 to support Tutorial posted to Arduino.cc

** Written for and tested with Arduino 1.0
**
** NOTE: Tested on Arduino Uno whose I2C pins are A4==SDA, A5==SCL

*/
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR    0x27 // <<----- Add your address here.  Find it from I2C Scanner
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

int n = 1;

LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

void setup()
{
 lcd.begin (20,4); //  <<----- My LCD was 16x2

 
// Switch on the backlight
lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
lcd.setBacklight(HIGH);
lcd.home (); // go home

//Pin 12 Supplies Ref Voltage(5v) to Temp sensor
pinMode(12,OUTPUT);
digitalWrite(12,HIGH);

 lcd.print("Yamaha XT125R");
 lcd.setCursor(0,2);
 lcd.print("Fork Travel");
 delay(1500);  
 lcd.print("              ");
 lcd.home();
 lcd.print("                  ");
 lcd.setCursor(0,2);
 lcd.print("                        ");
 
}//setup()



void loop()
{

//Init variables
char str_forkTrav[15];
char str_battVoltage[15];
char str_xGforce[15];
char str_yGforce[15];
char str_zGforce[15];

char str_tempVolts[15];

char str_tempReading[15];

  
 // Backlight on/off every 3 seconds
// lcd.setCursor (0,1);        // go to start of 2nd line
// lcd.print(n++,DEC);
 lcd.home();
 lcd.print("Frk:");
 int rawForkTrav = analogRead(0);
 lcd.print(dtostrf((rawForkTrav), 2, 1, str_forkTrav));
 lcd.print(" ");
 lcd.print("Bat:");
 float rawVal = (float)analogRead(1);
 float battVoltage = ((rawVal*(5.0/1023.0))*550.9)/83.9;
 lcd.print(dtostrf((battVoltage), 2, 2, str_battVoltage));

 lcd.setCursor(0,1);
 
 float xraw = (float)analogRead(7);
 float xVolt = xraw*(5.0/1023.0);
 float xAccel = (xVolt - 1.65)/0.3; //Calculate Acceleration on Axis.
 float xGforce = xAccel/9.8; //Divide to account for acceleration due to gravity(9.8m/s2).
 lcd.print("x");
 lcd.print(dtostrf((xGforce), 2, 2, str_xGforce));

  float yraw = (float)analogRead(6);
 float yVolt = yraw*(5.0/1023.0);
  float yAccel = (yVolt - 1.65)/0.3; //Calculate Acceleration on Axis.
 float yGforce = yAccel/9.8; //Divide to account for acceleration due to gravity(9.8m/s2).
 lcd.print(" y");
 lcd.print(dtostrf((yGforce), 2, 2, str_yGforce));

  float zraw = (float)analogRead(2);
 float zVolt = zraw*(5.0/1023.0);
  float zAccel = (zVolt - 1.65)/0.3; //Calculate Acceleration on Axis.
 float zGforce = zAccel/9.8; //Divide to account for acceleration due to gravity(9.8m/s2).
 lcd.print(" z");
 lcd.print(dtostrf((zGforce), 2, 2, str_zGforce));

 //Find total acceleration in any direection.
 //Total acceleration = sqrt(x^2 + y^2 + z^2)
 double totalg = sqrt((pow(xGforce,2))+(pow(yGforce,2))+(pow(zGforce,2)));
 lcd.setCursor(0,2);
 lcd.print("G-Force:");
 lcd.print(totalg);

//Print Temp Sensor readings.
  lcd.setCursor(0,3);
 lcd.print("Air Temp:");

 //Calculate temperature in degrees celsius.
 //First Read in analog value.
 int tempRaw = analogRead(3);
 //Convert to a voltage.
 float tempVolts = tempRaw*(5.0/1023.0);
 //Subtract 0.4, as 400mv is 0 degrees. Then divide by 0.0195, as this sensor has 19.5mV per degree.
 float tempReading = (tempVolts - 0.4)/0.0195;
 
 lcd.print(dtostrf((tempReading), 2, 2, str_tempReading));
 //lcd.print("  ");
 //lcd.print(dtostrf((tempVolts), 2, 2, str_tempVolts));


 

 delay(100);



 

}

