
#include <ArduinoJson.h>

#define trigPin 2
#define echoPin 3
#define led 11
#define led2 10

const int buttonPin_distance = 4;
const int buttonPin_temp = 5;
const int laserPin = 6;

int buttonState_distance = 0;         // current state of the button
int lastButtonState_distance = 0;     // previous state of the button

int buttonState_temp = 0;         // current state of the button
int lastButtonState_temp = 0;     // previous state of the button

int ThermistorPin = A0;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin_distance, INPUT);
  pinMode(buttonPin_temp, INPUT);
  pinMode(laserPin, OUTPUT);

}

void loop() {
  long duration, distance;

  // read the pushbutton input pin:
  buttonState_distance = digitalRead(buttonPin_distance);
  // read the pushbutton input pin:
  buttonState_temp = digitalRead(buttonPin_temp);

  // compare the buttonState to its previous state
  if (buttonState_distance != lastButtonState_distance) {
    // if the state has changed, increment the counter
    if (buttonState_distance == HIGH) {
      // if the current state is HIGH then the button went from off to on:
      Serial.println("button push");

      ////////////////////////////////////////
      //get height
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = (duration / 2) / 29.1;

      for (int ii = 0; ii < 5; ii++) {
        // print distance
        if (distance >= 200 || distance <= 0) {
          Serial.println("Out of range");
        }
        else {
          Serial.print(distance);
          Serial.println(" cm");
        }
      }

      delay(1000);
    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState_distance = buttonState_distance;







  // compare the buttonState to its previous state
  if (buttonState_temp != lastButtonState_temp) {
    // if the state has changed, increment the counter
    if (buttonState_temp == HIGH) {
      // if the current state is HIGH then the button went from off to on:
      Serial.println("button push");

      ////////////////////////////////
      // laser workings
      digitalWrite(laserPin, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(5000);                       // wait for a second
      digitalWrite(laserPin, LOW);    //  the LED off by making the voltage LOW
      delay(1000);   // wait for a second


      ///////////////////////////////
      // for temp
      Vo = analogRead(ThermistorPin);
      R2 = R1 * (1023.0 / (float)Vo - 1.0);
      logR2 = log(R2);
      T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
      Tc = T - 273.15;
      Tf = (Tc * 9.0) / 5.0 + 32.0;

      Serial.print("Temperature: ");
      Serial.print(Tf);
      Serial.print(" F; ");


    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState_temp = buttonState_temp;

}
