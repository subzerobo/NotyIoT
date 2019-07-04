#include <OneButton.h>

#define BUTTON_PIN    0

// Push Button Pin
OneButton button(BUTTON_PIN, true);


void reset_button_setup() {
  //set push button as input
  button.attachClick(myClickFunction);
  button.attachLongPressStop(myLongPressFunction);
}


void myClickFunction() {
  Serial.println("Clicked !");
}

void myLongPressFunction() {
  Serial.println("Long Pressed !");
  WiFi.disconnect();
  ESP.eraseConfig();
  ESP.reset();
  ESP.restart();
} 

void ButtonTick() {
  button.tick();
}
