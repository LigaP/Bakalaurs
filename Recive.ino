/*-----( biblioteku imports)-----*/
#include <SPI.h>   // periferijas interfeiss
#include "RF24.h"  // transmitera nRF24L01 bibliotka
RF24 myRadio (7, 8); // "myRadio" ir identifikators un 7,8  ir pini
/*-----( mainigie)-----*/
byte addresses[][6] = {"1Node"}; // radio kanala modulis
int dataReceived;  // sanemtie dati

void setup()   /*uzstadijumi, izpildas tikai vienreiz pec arduino ieslegsanas vai plates reseta*/
{
  Serial.begin(115200); //uzstada datu plusumu 
  delay(1000);  // programmas pauze milisekundes
  Serial.println(F("tests"));

  myRadio.begin();  // inicialize nRF24L01 reciveri
  myRadio.setChannel(108);  //kanals
  myRadio.setPALevel(RF24_PA_MIN);  //jauda energijas paterins

  myRadio.openReadingPipe(1, addresses[0]); // izmanto moduli
  myRadio.startListening(); // klausisanas uzsaksana

}//--(uzstadijumu beigas)---


void loop()   /****** muzigais cikls******/
{

  if ( myRadio.available()) // parbauda vai tiek sutiti dati
  {
    while (myRadio.available())  // kamer dati ir pieejami
    {
      myRadio.read( &dataReceived, sizeof(dataReceived) ); // nolasa datus
    }
        Serial.println(dataReceived); // izvada datus
  }  // IF BEIGAS *** if ( myRadio.available()) ***

} //--(programmas beigas)---
