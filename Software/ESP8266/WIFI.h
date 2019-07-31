char* ssid = "hackcube";
char* password = "hackcube";


//String AP_Name;
#include "stdlib_noniso.h"

const bool debug = true;
void sendHeader(int code, String type, size_t _size) {
  server.setContentLength(_size);
  server.send(code, type, "");
  Serial.print("setsize");
  Serial.println(_size);
}

#define bufSize 2500
int bufc = 0; //buffer counter;
char data_websiteBuffer[bufSize];

void startAPScan() {
  //scanMode = "scanning...";
  if (apScan.start()) {
    Serial.println("scanning");
    // apScan.sort();
    server.send ( 200, "text/json", "true");
    //    attack.stopAll();
    //    scanMode = "SCAN";
  }
  Serial.println("scanend");
}
void sendBuffer() {
  if (bufc > 0) {
    server.sendContent_P(data_websiteBuffer, bufc);
    bufc = 0;
  }
}
void sendToBuffer(String str) {
  size_t len = str.length();
  if (bufc + len > bufSize) {
    server.sendContent_P(data_websiteBuffer, bufc);
    bufc = 0;
  }
  memcpy(data_websiteBuffer + bufc, str.c_str(), len);
  bufc += len;
}

void sendAPResults() {
  apScan.sendResults();
}

void selectAP() {
  if (server.hasArg("num")) {
    apScan.select(server.arg("num").toInt());
  }
}
void ResultsJSON() {
  apScan.getResultsJSON();
}



String   getmac() {
  byte mac[8] ;
  String MACS = "HackCUBESpecial_";
  WiFi.macAddress(mac);
  for (int i = 3; i < 6; i++) {
    if (mac[i] < 0x10) {
      MACS += "0";
    }
    //itoa(0xaa, MACB, 16);
    MACS += String(mac[i], HEX);
  }
  return MACS;
}
void ConnectWif() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}


IPAddress string2ip(const char* str) {
  int ip1, ip2, ip3, ip4;
  
  //Serial.println("string:");
  //Serial.println(str);
  sscanf(str, "%d.%d.%d.%d", &ip1, &ip2, &ip3, &ip4);

//  Serial.println("string to IP");
//  Serial.println(ip1);
//  Serial.println(ip2);
//  Serial.println(ip3);
//  Serial.println(ip4);

  return IPAddress(ip1, ip2, ip3, ip4);
}

void ConfigWifiAP() {
  Serial.println("ConfigWifiAP()");
  
  JsonObject root = configDoc.as<JsonObject>();

  const char* wifi_ssid_default = getmac().c_str();
  const char* wifi_password_default = "hackcube";
  const char* wifi_local_ip_default = "192.168.6.1";
  const char* wifi_gateway_default = "192.168.6.1";
  const char* wifi_subnet_default = "255.255.255.0";
    
  const char* wifi_ssid = root.containsKey("wifi_ssid") ? configDoc["wifi_ssid"] : wifi_ssid_default;
  const char* wifi_password = root.containsKey("wifi_password") ? configDoc["wifi_password"] : wifi_password_default;
  const char* wifi_local_ip = root.containsKey("wifi_local_ip") ? configDoc["wifi_local_ip"] : wifi_local_ip_default;
  const char* wifi_gateway = root.containsKey("wifi_gateway") ? configDoc["wifi_gateway"] : wifi_gateway_default;
  const char* wifi_subnet = root.containsKey("wifi_subnet") ? configDoc["wifi_subnet"] : wifi_subnet_default;
  
  Serial.print("wifi_ssid:");
  Serial.println(wifi_ssid);
  Serial.print("wifi_password:");
  Serial.println(wifi_password);
  Serial.print("wifi_local_ip:");
  Serial.println(wifi_local_ip);  
  Serial.print("wifi_gateway:");
  Serial.println(wifi_gateway);
  Serial.print("wifi_subnet:");
  Serial.println(wifi_subnet);
  
  IPAddress local_IP = string2ip(wifi_local_ip);
  IPAddress gateway = string2ip(wifi_gateway);
  IPAddress subnet = string2ip(wifi_subnet);

  WiFi.mode(WIFI_AP);
//  String AP_Name = getmac();
  Serial.print("SSID:");
//  Serial.println(AP_Name);
  Serial.println(wifi_ssid);
  Serial.print("Setting soft-AP configuration ... ");
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");
  Serial.print("Setting soft-AP ... ");
//  Serial.println(WiFi.softAP(AP_Name.c_str(), "hackcube") ? "Ready" : "Failed!");
  Serial.println(WiFi.softAP(wifi_ssid, wifi_password) ? "Ready" : "Failed!");
  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());
  delay(100);
}

void connectWifi() {
  unsigned long outtime = millis();
  bool outflag = false;
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED && !outflag) {
    delay(500);
    Serial.print(".");
    if (millis() - outtime > 10000)
      outflag = true;
  }
  if (outflag) {
    ConfigWifiAP();
    Serial.println("out");
  } else {
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
}
