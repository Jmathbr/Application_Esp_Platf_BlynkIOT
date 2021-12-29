

//user interface HTML code----------------
String Wifi_SSID,Wifi_PASS;
String html = R"***(
<!DOCTYPE html>
<html><head>    
    <title>WIFI</title>
  </head>
  
  <body>
    <h1>Connect WIFI</h1>
      <table width="400" border="1">
        <tbody>
          <form method="post" action="/datasubmit">
          <tr>
            <td>
              <label for="textfield">User:</label>
              <input type="text" name="textfield" id="txtuser">
            </td>
          </tr>
          <tr>
            <td>
              <label for="textfield">Password:</label>
              <input type="text" name="textfield" id="txtpass">
            </td>
          </tr>

          <tr>
            <td>
             <input name="Submit" type="Submit" value="Submit" class="submit">
             
            </td>
          </tr>
          </form>
      </tbody></table>
  
</body></html>
)***";

const char* Sssid = "ESP_CLOUD_LIGHT";

//--------------------------------------
void handleRoot()
{
  server.send(200, "text/html", html);
}
void data(){
  //Wifi_SSID = server.arg(0);
  //Wifi_PASS = server.arg(1);
  StaticJsonDocument<100> new_doc;

  new_doc["SSID"] = server.arg(0);
  new_doc["PASS"] = server.arg(1);

  String new_wifi;
  
  //Serial.println("NEW PASS: " + Wifi_PASS);
  
  serializeJson(new_doc, new_wifi);
  serializeJson(new_doc, Serial);
  Serial.println("<WIFI NEW, RESET>");
  post_fs(new_wifi);
  delay(3000);
  
  ESP.reset();
  
  //Serial.println("NEW SSID: " + Wifi_SSID);
  //Serial.println("NEW PASS: " + Wifi_PASS);
}    

void setup_acess_point(){
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAP(Sssid);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.on("/datasubmit", data);
  server.begin();
  Serial.println("HTTP server started");
}

bool wifi_check(String ssid,String password){
  WiFi.begin(ssid, password);
  int count = 0;
  while(WiFi.status()!= WL_CONNECTED && count<= 150){ 
    delay(100);
    Serial.print(".");
    count = count + 1;
    if(WiFi.status() == WL_CONNECTED){
      Serial.println();     
      return true; 
    }
  }
  Serial.println();
  return false;
}
