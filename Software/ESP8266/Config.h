
// JSON CONFIG FILE PATH
String CONFIG_JSON_PATH = "/config.json";
// Json config object
//StaticJsonDocument<512> CONFIG_DOC; //stack
DynamicJsonDocument CONFIG_DOC(4096); //heap

void loadJsonConfig() {
  if (!SPIFFS.exists(CONFIG_JSON_PATH)) {
    Serial.println(F(sprintf("ERROR: config file '%s' is NOT found!!!", CONFIG_JSON_PATH.c_str())));
  }
  File file = SPIFFS.open(CONFIG_JSON_PATH, "r");

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(CONFIG_DOC, file);
  
  if (error) {
    Serial.println(F("Failed to read file, using default configuration"));
    Serial.println(error.c_str());
  }

  file.close();
  
  // Copy values from the JsonDocument to the Config
//  char wifi_ssid[64]; 
//  strlcpy(wifi_ssid,                  // <- destination
//          configDoc["wifi_ssid"] | "example.com",  // <- source
//          sizeof(wifi_ssid)); 
//
//  Serial.println(wifi_ssid);
}

char* loadJsonConfigString() {
  char buffer[4096];
  char message[256];
  if (serializeJsonPretty(CONFIG_DOC, buffer, 4096)==0){
    sprintf(message, "Failed to write to file '%s", CONFIG_JSON_PATH.c_str());
    Serial.println(message);
  }
  
  return buffer;
}

char* saveJsonConfig(const String jsonConfig) {
  char buffer[128]="";
  if (!SPIFFS.exists(CONFIG_JSON_PATH)) {
      sprintf(buffer, "ERROR: config file '%s' is NOT found!!!", CONFIG_JSON_PATH.c_str());
  } else {
    File file = SPIFFS.open(CONFIG_JSON_PATH, "w");

    if (jsonConfig.length() <= 0) {
      // save global json to config
      if (serializeJsonPretty(CONFIG_DOC,file)==0){
        sprintf(buffer, "Failed to write to file '%s", CONFIG_JSON_PATH.c_str());
      }
    } else {
      DynamicJsonDocument doc(4096); //heap
      // save input json string to config
      DeserializationError error = deserializeJson(doc, jsonConfig);
  
      // Test if parsing succeeds.
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
        Serial.print("JSON content");
        Serial.println(jsonConfig.c_str());
        sprintf(buffer, "deserializeJson '%s", jsonConfig.c_str());
      } else {
        if (serializeJsonPretty(doc,file)==0){
          sprintf(buffer, "Failed to write to file '%s", CONFIG_JSON_PATH.c_str());
        }
      }
    }
    // Close the file
    file.close();
  }
  
  return buffer;
}
