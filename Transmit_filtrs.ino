/*-----( biblioteku imports)-----*/
#include <SPI.h>   // periferijas interfeiss
#include "RF24.h"  // transmitera nRF24L01 bibliotka
RF24 myRadio (7, 8); // "myRadio" ir identifikators un 7,8  ir pini
/*-----( mainigie)-----*/
byte addresses[][6] = {"1Node"}; // radio kanala modulis
int dataTransmitted;  // parsutamie dati
const int analogInPin = A1; //input pins 
int sensorValue = 0; //sensora nolasitie dati

const int numReadings5 = 5; // filtrs ar 5 lasijumu kapacitati
int readings5[numReadings5]; //datu lasijumi no analaoga
int readIndex5 = 0; // indekss
int total5 = 0; 

void setup()   /* uzstadijumi, izpildas tikai vienreiz pec arduino ieslegsanas vai plates reseta*/
{
  Serial.begin(115200); // uzstada datu plusumu 
  delay(1000); //programmas pauze milisekundes
  myRadio.begin();  // inicialize nRF24L01 transmiteri
  myRadio.setChannel(108);  // kanals
  myRadio.openWritingPipe( addresses[0]); // izmanto sakotnejo ierakstu moduli -addresses
  myRadio.setPALevel(RF24_PA_MIN); //jauda energijas paterins
  delay (1000);

  for (int thisReading = 0; thisReading < numReadings5; thisReading++)  // inicializēt lasījumus uz nulli 
  {
    readings5[thisReading] = 0;
  }
  }

//--(uzstadijumu beigas)---

void loop()   /***** muzigais cikls*****/
{
  total5 = total5 - readings5[readIndex5];  // atnem pedejo lasijumu
  readings5[readIndex5] = analogRead(analogInPin); // nozime nolasito vertibu 
  total5 = total5 + readings5[readIndex5]; //pieskaita nolasito vertibu
  readIndex5 = readIndex5 + 1;  //dodas uz nakamo poziciju masiva

  if (readIndex5 >= numReadings5) {  // ja atrodas masiva beigas 
    readIndex5 = 0;  // sak no sakuma
  }
  int average = total5 / numReadings5; // videjas vertibas aprekins
  
  myRadio.write( &average, sizeof(average) ); //  nosuta datus

  Serial.print(F("sensorValue = ")); //izvada datus
  Serial.print(average,DEC);
  Serial.println(F(" Netiek gaidits apstiprinajums"));
  delay(40);

}//--(cikla beigas)---
