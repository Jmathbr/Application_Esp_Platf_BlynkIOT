#include <FS.h>

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

void check_fs(void){
  if((SPIFFS.exists("/data.txt")) == false){
    Serial.println("Creat data wifi");
    File file = SPIFFS.open("/data.txt", "w");
    file.print("Data Wifi: ");
    file.close();
  }else{
    Serial.println("<Empty>");
  }
}

void post_fs(String msg){
  File file = SPIFFS.open("/data.txt", "w");
  file.print(msg);
  file.close();
}
void get_fs(){
  File file = SPIFFS.open("/data.txt", "r");
  while(file.available()){
    Serial.write(file.read());
  }
  size_t msg = Serial.write(file.read());
  file.close();
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  setup_fs(); 
  check_fs();

  post_fs("joao");
  
  get_fs();
}
 
void loop(){}
