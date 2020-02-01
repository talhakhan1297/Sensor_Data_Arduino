#include <Wire.h>
#include <Adafruit_ADS1015.h>
Adafruit_ADS1115 ads;

int count = 0;
float t0 = 0;
float t1 = 0;
float t2 = 0;
float t3 = 0;
float t4 = 0;
    
void setup() 
{ 
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  
  Serial.begin(9600);

  ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  ads.begin();
}

void loop() 
{
  //Serial.println("Start");
  current();
  Serial.println(volt_1());
  Serial.println(volt_2());
  Serial.println(volt_3());
  Serial.println(volt_4());
  Serial.println(volt_t());
  Mux();
  delay(1000);
}

void current()
{
  int16_t results;
  
  float multiplier = 0.0078125F; /* ADS1115  @ +/- 0.256V gain (16-bit results) */

  results = ads.readADC_Differential_0_1();  
  float c = (results * multiplier)/0.00075;
  Serial.println(c/1000, 5);
}

float volt_1()
{
  float reading = analogRead(A1);
  float v = (reading * 4.683) / 1024;
  //Serial.println(v);
  return v;
}

float volt_2()
{
  float reading = analogRead(A2);
  float v = (reading * 8.4639) / 1024;
  //Serial.println(v);
  v = v - volt_1();
  return v;
} 

float volt_3 ()
{
  float reading = analogRead(A3);
  float v = (reading * 12.967) / 1024;
  //Serial.println(v);
  v = v - volt_2() - volt_1();
  return v;
}

float volt_4()
{
  int r0 = bitRead(5,0);    
  int r1 = bitRead(5,1);    
  int r2 = bitRead(5,2);  
    
  digitalWrite(3, r0);
  digitalWrite(4, r1);
  digitalWrite(5, r2);

  float reading =  analogRead(A0);
  float v = (reading * 16.562) / 1024;
  //Serial.println(v);
  v = v - volt_3() - volt_2() - volt_1();
  return v;
}

float volt_t()
{
  int r0 = bitRead(5,0);    
  int r1 = bitRead(5,1);    
  int r2 = bitRead(5,2);  
    
  digitalWrite(3, r0);
  digitalWrite(4, r1);
  digitalWrite(5, r2);

  float reading =  analogRead(A0);
  float v = (reading * 16.562) / 1024;
  //Serial.println(v);
  return v;
}

float Temperature()
{
  delay(1000);
  float reading = analogRead(A0);
//  reading = (reading * 5000) / 1023;
//  float t = (-1) * (reading - 500) / 10;
  float t = (reading * 500) / (1024);
  return t;
}

void Mux()
{  
  int r0 = bitRead(count,0);    
  int r1 = bitRead(count,1);    
  int r2 = bitRead(count,2);  
    
  digitalWrite(3, r0);
  digitalWrite(4, r1);
  digitalWrite(5, r2);

  if(count == 0)
  {
    t0 = Temperature();
  }
  
  else if(count == 1)
  {
    t1 = Temperature();
  }
  
  else if(count == 2)
  {
    t2 = Temperature();
  }
  
  else if(count == 3)
  {
    t3 = Temperature();
  }
  
  else if(count == 4)
  {
    t4 = Temperature();
  }
//  Serial.print(count);
//  Serial.println("");  
  count++;

  if(count == 5)
  {
    count = 0;
  }


  Serial.println(t0);
  Serial.println(t1);
  Serial.println(t2);
  Serial.println(t3);
  Serial.println(t4);
 }
