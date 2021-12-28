
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
  String msg = file.readString();
  file.close();
  return msg;
}
