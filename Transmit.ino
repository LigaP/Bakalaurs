/*-----( biblioteku imports)-----*/
#include <SPI.h>   // periferijas interfeiss
#include "RF24.h"  // transmitera nRF24L01 bibliotka
RF24 myRadio (7, 8); // "myRadio" ir identifikators un 7,8  ir pini
/*-----( mainigie)-----*/
byte addresses[][6] = {"1Node"}; // radio kanala modulis
int dataTransmitted;  // parsutamie dati
const int analogInPin = A1;  // input pins 
int sensorValue = 0;   //sensora nolasitie dati

void setup()   /* uzstadijumi, izpildas tikai vienreiz pec arduino ieslegsanas vai plates reseta*/
{
  Serial.begin(115200); // uzstada datu plusumu 
  delay(1000);  // programmas pauze milisekundes
  myRadio.begin();  // inicialize nRF24L01 transmiteri
  myRadio.setChannel(108);  // kanals
  
  myRadio.setPALevel(RF24_PA_MIN); //jauda energijas paterins

  myRadio.openWritingPipe( addresses[0]); // izmanto sakotnejo ierakstu moduli -addresses
  delay(1000);
}//--(uzstadijumu beigas)---


void loop()   /****** muzigais cikls******/
{
  sensorValue = analogRead(analogInPin); //nolasa analogo vertibu
  myRadio.write( &sensorValue, sizeof(sensorValue) ); //  nosuta datus

  Serial.print(F("sensorValue = "));  //izvada datus
  Serial.print(sensorValue);
  Serial.println(F(" Netiek gaidits apstiprinajums"));
   delay(500);

}//--(cikla beigas)---
