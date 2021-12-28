//====================================
//ESP8266 Access Point Control of LED
//====================================
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

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

const char* ssid = "ESP_CLOUD_LIGHT";
ESP8266WebServer server(80);
//--------------------------------------
void handleRoot()
{
  server.send(200, "text/html", html);
}
void data(){
  Wifi_SSID = server.arg(0);
  Wifi_PASS = server.arg(1);
  
  Serial.println("User: " + Wifi_SSID);
  Serial.println("Password: " + Wifi_PASS);
}

void setup_acess_point(){
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.on("/datasubmit", data);
  server.begin();
  Serial.println("HTTP server started");
}
//===============================================
void setup(){
  Serial.begin(115200);
  setup_acess_point();
}
//===============================================
void loop()
{
  server.handleClient();
}
