void connectToWiFi(const char ssidName [], const char pass []) {

  Serial.println("Starting...");
  Serial.println("Connecting to WiFi.");

  int conn = WiFi.begin(ssidName, pass);

  if (conn == WL_CONNECTED) {
    Serial.println("ok");
  } else if (conn == WL_IDLE_STATUS) {
    Serial.println("Idle");
  } else {
    Serial.println("unknown responce");
  }
}
