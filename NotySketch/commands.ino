#include <StringSplitter.h>       //https://github.com/aharshac/StringSplitter

// Command Parser
void commandParse(String command) {
  StringSplitter *splitter = new StringSplitter(command, ',', 3);
  int itemCount = splitter->getItemCount();
  if (itemCount < 2) {
    Serial.println("Command Parse Error, cmd:" + command);
  }
  String cmd_channel = splitter->getItemAtIndex(0);
  String cmd_type    = splitter->getItemAtIndex(1);
  String cmd_extra   = "";
  if (itemCount == 3){
    cmd_extra = splitter->getItemAtIndex(2);
  }
  commandRoute(cmd_channel, cmd_type, cmd_extra);
}

// Commad Router
void commandRoute(String ch, String ty, String ex) {
  // Statu LED
  if (ch == "S") {
    HandleLedStatus(ty.toInt());
  }
  // WS2818 Strip
  if (ch == "L") {
    HandleStrip(ty, ex);
  }
  // OLED Display
  if (ch == "D") {
    
  }
}

// Status Led Controller
void HandleLedStatus(int ty) {
  Serial.println("Status Command with Type:" + String(ty));
  control_status_led(ty);
}

void HandleStrip(String ty, String extra) {
  Serial.println("Strip Command with Type:" + ty + " and Extra :" + extra);
  if (ty == "S") {
    solid(extra);
  }
  if (ty == "C") {
    chase(extra);
  }
  if (ty == "R") {
    chaseRainbow(extra.toInt());
  }
}
