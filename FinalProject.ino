#include <Adafruit_NeoPixel.h>
#include <IRremote.h>

Adafruit_NeoPixel strip1(8, 7);
Adafruit_NeoPixel strip2(8, 8);

const int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

uint32_t purple = strip1.Color(130, 0, 252);
uint32_t yellow = strip1.Color(232, 218, 0);
uint32_t cyan = strip1.Color(0, 231, 252);
uint32_t off = strip1.Color(0, 0, 0);

boolean power1 = false;
boolean power2 = false;
boolean power3 = false;

int ledPin1 = 9;
int ledPin2 = 10;

void setup() {
  strip1.begin();
  strip2.begin();
  strip1.clear();
  strip2.clear();
  strip1.show();
  strip2.show();

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);


  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop() {
  lightControl();
}


void lightControl(){
if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume();

    if (results.value == 0xFF7A85 && power1 == false) {
      for (int index = 0; index < strip1.numPixels(); index++) {
        strip1.setPixelColor(index, purple);
        strip1.show();
        digitalWrite(ledPin1, HIGH);
        strip2.setPixelColor(index, off);
        strip2.show();
        digitalWrite(ledPin2, LOW);

      }
      power1 = !power1;

    } 
    else if(results.value == 0xFF7A85 && power1 == true) {
      for (int index = 0; index < strip1.numPixels(); index++) {
        strip1.setPixelColor(index, off);
        strip1.show();
        digitalWrite(ledPin1, LOW);

      }
      power1 = !power1;
    }
    if (results.value == 0xFF30CF && power2 == false) {
      for (int index = 0; index < strip2.numPixels(); index++) {
        strip2.setPixelColor(index, cyan);
        strip2.show();
        digitalWrite(ledPin2, HIGH);
        strip1.setPixelColor(index, off);
        strip1.show();
        digitalWrite(ledPin1, LOW);

      }
      power2 = !power2;
    } 
    else if (results.value == 0xFF30CF && power2 == true) {
for (int index = 0; index < strip2.numPixels(); index++) {
        strip2.setPixelColor(index, off);
        strip2.show();
        digitalWrite(ledPin2, LOW);

      }
      power2 = !power2;

    }
    if (results.value == 0xFF18E7 && power3 == false) {
      for (int index = 0; index < strip1.numPixels(); index++) {
        strip1.setPixelColor(index, yellow);
        strip2.setPixelColor(index, yellow);
        digitalWrite(ledPin2, HIGH);
        digitalWrite(ledPin1, HIGH);


        strip1.show();
        strip2.show();
      }
      power3 = !power3;
    } 
    else if (results.value == 0xFF18E7 && power3 == true) {
     for (int index = 0; index < strip1.numPixels(); index++) {
        strip1.setPixelColor(index, off);
        strip1.show();
        strip2.setPixelColor(index, off);
        strip2.show();
        digitalWrite(ledPin2, LOW);
        digitalWrite(ledPin1, LOW);
      }
     power3 = !power3;
     power1 = false;
     power2 = false;

    }
  }



}
