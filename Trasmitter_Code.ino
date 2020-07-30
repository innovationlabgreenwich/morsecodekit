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

int buttonPress = 0;                              //variable to track whether the button is pressed

RF24 radio(CE_PIN, CS_PIN);                       //specifying the CE and CSN pins respectively

const byte address = "00001";                     //address is used by the transceivers to communicate with each other

void setup() {
  //defining input and output pins
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);
  
  radio.begin();                                  //initializing the radio
  radio.openWritingPipe(address);                 //start the channel to send data
  radio.setPALevel(RF24_PA_MIN);                  //setting the power amplification level
  radio.stopListening();                          //makes this module a transmitter 
}

void loop() {
  buttonPress = digitalRead(BUTTON_PIN);             //checks whether the button is pressed
  Serial.println(buttonPress);

  radio.write(&buttonPress, sizeof(buttonPress)); //transmits the value of buttonPress 
  delay(100);                                     //0.1s delay between transmissions
}
