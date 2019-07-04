void status_led_setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void control_status_led(int value) {
  digitalWrite(LED_BUILTIN, value);
}
