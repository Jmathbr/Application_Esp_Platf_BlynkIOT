
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <FS.h>

#define BLYNK_TEMPLATE_ID           "TMPLqeW-DK22"
#define BLYNK_DEVICE_NAME           "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "YMu4vd6-miu0MNBDTfySz9oLcyERjPsl"


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp8266.h>
String key_ssidG;
String key_passG;

void handleRoot();
void data();
void setup_acess_point();
bool wifi_check(String ssid,String password);
void setup_fs(void);
void check_fs(void);
void post_fs(String msg);
String get_fs();


char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
/*
void string_to_char(String message){
  int len = (message.length()+1);
  char out[len];
  for(int j=0 ;j<len ;j++){
    out[j] = message.charAt(j);
  }
  return out;
}
*/
char *bck(String copy){
  int lencp = (copy.length()+1);
  char cp[lencp];
    for(int l=0 ;l<lencp ;l++){
      cp[l] = copy.charAt(l);
    }
  return cp;
}

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.println();
  setup_fs();
  check_fs();
  //post_fs("{\"SSID\":\"admin\",\"PASS\":\"12345678\"}");
  StaticJsonDocument<600> doc;
  String data_json = get_fs();
  //Serial.print(data_json);
  deserializeJson(doc, data_json);
  //serializeJsonPretty(doc, Serial);
  //Serial.println(doc); 
  String key_ssid = doc["SSID"];
  String key_pass = doc["PASS"];
  
  //setup_acess_point();
  //Blynk.begin(auth, key_ssid, key_pass);
  
  key_ssidG = key_ssid;
  key_passG = key_pass;
   
}

void loop() {
  Serial.println("Check Wifi Connectivity.");
  if (wifi_check(key_ssidG,key_passG)== true){
    Serial.println("Wifi stable");
    Serial.println("Active BLYNK");

    char out_ssid[(key_ssidG.length()+1)]; 
    key_ssidG.toCharArray(out_ssid,(key_ssidG.length()+1));

    
    /*
    int len = (key_ssidG.length()+1);
    char out_ssid[len];
    for(int j=0 ;j<len ;j++){
      out_ssid[j] = key_ssidG.charAt(j);
    }
    */
    int len = (key_passG.length()+1);
    char out_pass[len];
    for(int k=0 ;k<len ;k++){
      out_pass[k] = key_passG.charAt(k);
    }
  
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
  /*
  server.handleClient();
  Blynk.run();
  */
}
