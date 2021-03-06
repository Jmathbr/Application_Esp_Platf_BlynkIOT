#include <FS.h>
#include <ArduinoJson.h>


void setup_fs(void){
  if(!SPIFFS.begin()){
    SPIFFS.check();
    Serial.println("Mount SPIFFS Failed");
    //return true;
  }else{
    Serial.println("Mount SPIFFS Sucess");
    //return false;
  }
}
void post_fs(String msg){
  File file = SPIFFS.open("/Data.txt", "w");
  file.print(msg);
  file.close();
}
void check_fs(void){
  if((SPIFFS.exists("/Data.txt")) == false){
    Serial.println("Creat data wifi");
    post_fs("{\"SSID\":\"admin\",\"PASS\":\"12345678\"}");
  }else{
    Serial.println("<Search Sucessfull>");
  }
}

String get_fs(){
  File file = SPIFFS.open("/Data.txt", "r");
  //isso tem que ser serializado em um json
  String msg = file.readString();
  file.close();
  return msg;
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  setup_fs(); 
  check_fs(); 
  post_fs("{\"SSID\":\"admin\",\"PASS\":\"12345678\"}");
  get_fs();
  Serial.println(get_fs());
}
 
void loop(){}
