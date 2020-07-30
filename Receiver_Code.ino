

#include <SPI.h>
#include <printf.h>
#include <nRF24L01.h>
#include <RF24_config.h>
#include <RF24.h>

//defining pins to be used in the setup - if you change connections, renumber them accordingly here
//-------------------
#define CE_PIN 2
#define CS_PIN 10
#define MOSI_PIN 11
#define MISO_PIN 12
#define SCK_PIN 13

#define BUTTON_PIN 3

#define LED_PIN 5
//-------------------

int buttonPress = 0;                               //variable to track whether the button is pressed

RF24 radio(CE_PIN, CS_PIN);                        //specifying the CE and CSN pins respectively

const byte address = "00001";                      //address is used by the transceivers to communicate with each other

void setup() {
  //defining input and output pins
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  
  radio.begin();                                   //initializing the radio
  radio.openReadingPipe(0, address);               //start the channel to receive data
  radio.setPALevel(RF24_PA_MIN);                   //setting the power amplification level
  radio.startListening();                          //makes this module a receiver 
}

void loop() {
  if (radio.available()) {                         //first checking if there is any available data
    radio.read(&buttonPress, sizeof(buttonPress)); //receiving the actual data

      if(buttonPress) {
        digitalWrite(LED_PIN, HIGH);  //turning on the LED
      }
      else {
        digitalWrite(LED_PIN, LOW);
      }
  }

  

}
