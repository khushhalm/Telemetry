#include <RFID.h>

/*
  Read a card using a mfrc522 reader on your SPI interface
  Pin layout should be as follows (on Arduino Uno):
  MOSI: Pin 11 / ICSP-4
  MISO: Pin 12 / ICSP-1
  SCK: Pin 13 / ISCP-3
  SS/SDA: Pin 10
  RST: Pin 9

  signal wire hall 2;    // the pin that the pushbutton is attached to
  relay wire hall = 3;// the pin that the LED is attached to

  int buzz = 5;
  int act = 6;
  int led = 7;

*/

#include <SPI.h>
#include <RFID.h>

#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN, RST_PIN);
int buzz = 5;
int act = 6;
int led = 7;
int power = 8;
int serNum[5];
int cards[][5] = {
  {22, 34, 24, 2, 46}
};

bool access = false;

const int  buttonPin = 2;    // the pin that the pushbutton is attached to
const int ledPin = 3;// the pin that the LED is attached to

int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
  pinMode(act, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(power, OUTPUT);
  pinMode(buzz, OUTPUT);
  digitalWrite(led, LOW);

  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
  // initialize the LED as an output:
  pinMode(ledPin, OUTPUT);
  digitalWrite(power, HIGH);
  digitalWrite(ledPin, HIGH);
}

void loop() {

  if (rfid.isCard()) {

    if (rfid.readCardSerial()) {
      Serial.print(rfid.serNum[0]);
      Serial.print(" ");
      Serial.print(rfid.serNum[1]);
      Serial.print(" ");
      Serial.print(rfid.serNum[2]);
      Serial.print(" ");
      Serial.print(rfid.serNum[3]);
      Serial.print(" ");
      Serial.print(rfid.serNum[4]);
      Serial.println("");

      for (int x = 0; x < sizeof(cards); x++) {
        for (int i = 0; i < sizeof(rfid.serNum); i++ ) {
          if (rfid.serNum[i] != cards[x][i]) {
            access = false;
            break;
          } else {
            access = true;
          }
        }
        if (access) break;
      }

    }

    if (access) {
      Serial.println("Welcome!");
      digitalWrite(led, HIGH);
      delay(1000);
      // digitalWrite(led, LOW);
      digitalWrite(power, LOW);
      delay(1000);
      digitalWrite(act, HIGH);
      delay(1000);
      // digitalWrite(power, LOW);

    } else {
      Serial.println("Not allowed!");
      digitalWrite(led, HIGH);
      delay(500);
      digitalWrite(led, LOW);
      delay(500);
      digitalWrite(led, HIGH);
      delay(500);
      digitalWrite(led, LOW);
    }
  }

  rfid.halt();

  buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes:  ");
      Serial.println(buttonPushCounter);
    } else {
      // if the current state is LOW then the button
      // wend from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state,
  //for next time through the loop
  lastButtonState = buttonState;

  // turns on the LED every four button pushes by
  // checking the modulo of the button push counter.
  // the modulo function gives you the remainder of
  // the division of two numbers:
  if (buttonPushCounter % 2 == 0) {
    digitalWrite(ledPin, LOW);
    digitalWrite(buzz, HIGH);
  } else {
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzz, LOW);
  }
}
