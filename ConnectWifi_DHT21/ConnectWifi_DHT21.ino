#include <DHT.h>
#include <DHT_U.h>
#include <ArduinoJson.h> // Thêm thư viện ArduinoJson
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <HTTPClient.h>


#define DHTPIN 26     // what digital pin we're connected to
#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

  // Gửi HTTP POST request -----
  HTTPClient http;

void setup() {
    // WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
    // it is a good practice to make sure your code sets wifi mode how you want it.

    // put your setup code here, to run once:
    Serial.begin(115200);

    //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wm;

    // reset settings - wipe stored credentials for testing
    // these are stored by the esp library
    // wm.resetSettings();

    // Automatically connect using saved credentials,
    // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
    // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
    // then goes into a blocking loop awaiting configuration and will return success result
    bool res;
    // res = wm.autoConnect(); // auto generated AP name from chipid
    // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
    res = wm.autoConnect("ESP32_AccessPoint","password"); // password protected ap
    if(!res) {
        Serial.println("Cannot connect to wifi");
        ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("Connected!!!!!!!!!!!!!!!!!!!! :)");
        dht.begin();
    }

}



void loop() {
    // Wait a few seconds between measurements.
  delay(3000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" || ");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");

  // Compute heat index in Celsius (isFahreheit = false)
  // float hic = dht.computeHeatIndex(t, h, false);

  /*

  // Địa chỉ URL của server bạn muốn gửi request đến
  String url = "http://10.13.131.1:8080/v1/api/templogs";

  // Dữ liệu bạn muốn gửi trong request
 StaticJsonDocument<200> doc; // 200 là kích thước tối đa của JSON
  doc["value"] = 50.5; // Thay đổi giá trị này bằng giá trị thực của độ ẩm
//  doc["temperature"] = 25.3; // Thay đổi giá trị này bằng giá trị thực của nhiệt độ

  // Chuyển đổi JSON thành chuỗi
  String jsonString;
  serializeJson(doc, jsonString);

  // Gửi POST request
  http.begin(url);
  // http.addHeader("Content-Type", "application/json");

  // // Gửi request và nhận kết quả
  // int httpResponseCode = http.POST(jsonString);
  
  // Gửi request và nhận kết quả
  int httpResponseCode = http.GET();


  if (httpResponseCode > 0) {
    String response = http.getString(); // Nhận phản hồi từ server
    Serial.println(httpResponseCode);
    Serial.print("Response: ");
    Serial.println(response);
  } else {
    Serial.print("Error on HTTP request: ");
    Serial.println(httpResponseCode);
  }

  http.end(); // Kết thúc kết nối HTTP
*/
}
