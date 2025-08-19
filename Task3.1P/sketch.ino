#include <Wire.h>                // for I2C connection
#include <BH1750.h>              // for light sensor BH1750
#include <WiFiNINA.h>            // to connect wifi in arduino
#include <ArduinoHttpClient.h>   // to send data to internet (IFTTT)

// ====== my wifi details ======
char ssid[] = "realme 8";             // my wifi name
char pass[] = "dharmandersingh";      // my wifi password

// ====== my IFTTT details ======
String IFTTT_Key   = "f6W9W0t-OjoHn6HeTPL6TDM1kKLK5QV7aZXDWP3D1-t"; // my ifttt key
String IFTTT_Event = "light_trigger";   // my event name in ifttt

// ====== objects for sensor and wifi ======
BH1750 lightMeter;                     // this is my light sensor
WiFiSSLClient wifi;                    // this is my wifi client
HttpClient client = HttpClient(wifi, "maker.ifttt.com", 443); // this is my http client to send data

void setup() {
  Serial.begin(115200);      // start serial monitor
  Wire.begin();              // start I2C for sensor

  // start my BH1750 light sensor
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println("BH1750 sensor started.");
  } else {
    Serial.println("BH1750 not found, please check wires!");
    while (1);  // stop if not working
  }

  // connect my arduino to wifi
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {  // keep trying
    Serial.print(".");
    delay(2000);
  }
  Serial.println("\nWiFi connected!");
  Serial.print("My IP Address: ");
  Serial.println(WiFi.localIP());  // show IP address
}

void loop() {
  // read light in lux from sensor
  float lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lux");

  // send this light value to ifttt
  sendToIFTTT(lux);

  delay(10000); // wait 10 sec and then repeat
}

// ====== function to send data to IFTTT ======
void sendToIFTTT(float lux) {
  // path for ifttt
  String path = "/trigger/" + IFTTT_Event + "/with/key/" + IFTTT_Key;
  
  // tell we are sending JSON
  String contentType = "application/json";
  
  // send my lux value inside value1
  String body = "{\"value1\":\"" + String(lux, 2) + "\"}";

  Serial.println("Sending request to IFTTT...");

  // make the request
  client.beginRequest();
  client.post(path);                          // post request
  client.sendHeader("Content-Type", contentType);  // header
  client.sendHeader("Content-Length", body.length()); // length of data
  client.beginBody();
  client.print(body);                         // send the lux value
  client.endRequest();

  // get answer back from IFTTT
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  // show status in serial monitor
  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);
}
