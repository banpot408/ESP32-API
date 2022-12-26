#include <WiFi.h>
#include <HTTPClient.h>


const char* ssid = "Creammy_2.4G";
const char* password = "0637365282";

// replace the MAC address below by the MAC address printed on a sticker on the Arduino Shield 2
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

//WiFiClient client;



void setup() {
  
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
  delay(1000);
  Serial.println("Connecting…");
  }
  Serial.println("CONNECTED");



}


/*
var client = new RestClient("http://asphere-smart-office/api/token");
var request = new RestRequest(Method.POST);
request.AddHeader("Content-Type", "text/plain");
request.AddParameter("text/plain", "grant_type=password&userName=root&password=root!", ParameterType.RequestBody);
IRestResponse response = client.Execute(request);

grant_type=password&userName=root&password=root!

*/


void loop() {
// Make a POST request with the data if WiFi is connected

    String ID, AQI, NO2, O3, AQIjson;

    ID = "tenant@thingsboard.org";
    AQI = "Ya@min01$";



    
    
    // {"id": "AABBCCDD", "aqi": 10.0, "no2": 20.0, "o3": 30.0}    
    //{"username":"tenant@thingsboard.org","password":"Ya@min01$"}
//    AQIjson = "{\"username\": " + ID + ", \"password\": " + AQI + "}"; // "{\"username\":\"tenant@thingsboard.org\",\"password\":\"Ya@min01$\"}"
//    AQIjson = "{\"username\":\"tenant@thingsboard.org\",\"password\":\"Ya@min01$\"}"; // "{\"username\":\"tenant@thingsboard.org\",\"password\":\"Ya@min01$\"}"
    // grant_type=password&userName=root&password=root!
//    AQIjson = "grant_type=password&userName=root&password=root!";
//    AQIjson = "grant_type=password&userName=root&password=root!";
//    AQIjson = "{\"grant_type\":\"password\",\"userName\":\"root\",\"password\":\"root!\"}"; // "{\"username\":\"tenant@thingsboard.org\",\"password\":\"Ya@min01$\"}"

    AQIjson = "grant_type=password&userName=root&password=root";
    Serial.println ("JSON: \n" + AQIjson);



    if ((WiFi.status() == WL_CONNECTED))
    {
      //Check the current connection status
      HTTPClient http;
      
//      http.begin("http://asphere-smart-office//api/auth/login"); // "http://asphere-smart-office/api/token"
      http.begin("http://asphere-smart-office/api/token"); // "http://asphere-smart-office/api/token"
      http.addHeader("Content-Type", "text/plain"); //application/json
      int httpResponseCode = http.POST(AQIjson);   //Send the actual POST request
  
      if(httpResponseCode>0)
      {
        String response = http.getString();                       //Get the response to the request
        Serial.println(httpResponseCode);   //Print return code
        Serial.println(response);           //Print request answer
      }
      else
      {
        Serial.print("Error on sending POST request: ");
        Serial.println(httpResponseCode);
      }
      
      http.end();  //Free resources
    }
    else
    {
      Serial.println ("Something wrong with WiFi?");
    }

    delay (10*60*1000);  // 10 * 60 seconds between updates
}
