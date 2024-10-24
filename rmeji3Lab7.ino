/*
// Rafael Mejia, 679124181 rmeji3
// Jose Leal, 674903709 jleal9
// TA - 
// Lab 7
// Description -
make 2 arduinos communicate by using a push button and leds. One button should activate the other's led
// References - https://www.instructables.com/Arduino-Serial-Communication/
https://www.arduino.cc/reference/tr/language/functions/communication/serial/
https://docs.arduino.cc/built-in-examples/digital/Debounce/

*/

char msg[2] =  "1";
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50; 
int ledState = LOW;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;
int buttonPin = 2;
void setup(){
// Begin the Serial at 9600 Baud
	Serial.begin(9600);
  	pinMode(2,INPUT);
  	pinMode(3, OUTPUT);
}
void loop() {
  
  if (Serial.available() > 0){
    char t[2];
    Serial.readBytes(t, 2);
    ledState = !ledState;
    digitalWrite(3, ledState);
  }
  int reading = digitalRead(buttonPin);


  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
       buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        Serial.write(msg, 2);
      }
    }
  }
  lastButtonState = reading;
}