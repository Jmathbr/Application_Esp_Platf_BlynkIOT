#define BLYNK_TEMPLATE_ID           "TMPLqeW-DK22"
#define BLYNK_DEVICE_NAME           "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "YMu4vd6-miu0MNBDTfySz9oLcyERjPsl"
#define BLYNK_PRINT Serial

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <FS.h>
#include <BlynkSimpleEsp8266.h>

void handleRoot();
void data();
void setup_acess_point();
bool wifi_check(String ssid,String password);
void setup_fs(void);
void check_fs(void);
void post_fs(String msg);
String get_fs();

char auth[] = BLYNK_AUTH_TOKEN;

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.println();
  setup_fs();
  check_fs();
  
  StaticJsonDocument<100> doc;
  String data_json = get_fs();

  deserializeJson(doc, data_json);
 
  String key_ssid = doc["SSID"];
  String key_pass = doc["PASS"];

  Serial.println("Check Wifi Connectivity");
  Serial.println("ssid -> "+key_ssid);
  Serial.println("PASS -> "+key_pass);
  Serial.println("<Making Connection>");
  
  if (wifi_check(key_ssid,key_pass)== true){
    Serial.println("Wifi stable");
    Serial.println("Active BLYNK");

    char out_ssid[(key_ssid.length()+1)]; 
    key_ssid.toCharArray(out_ssid,(key_ssid.length()+1));

    char out_pass[(key_pass.length()+1)]; 
    key_pass.toCharArray(out_pass,(key_pass.length()+1));
    
    Blynk.begin(auth, out_ssid, out_pass);
    while(true){
      Blynk.run();
      }
    
  }else{
    Serial.println("Wifi unstable");
    Serial.println("Active Acess Point");
    setup_acess_point();
    while(true){
      server.handleClient();
      }
  } 
   
}

void loop() {}
