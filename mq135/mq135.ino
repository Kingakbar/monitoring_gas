#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const int MQ_PIN = A0; // Pin analog untuk sensor MQ-135
const char* ssid = "Ank Kratos";
const char* password = "akbarget21";
const char* serverAddress = "http://192.168.216.239:8080/api/gas-data"; // Alamat API gas di Laravel

void setup() {
  pinMode(MQ_PIN, INPUT);
  Serial.begin(9600);
  connectWiFi();
  Serial.println("NodeMCU ESP8266 dan MQ-135 Gas Sensor");
}

void loop() {
  int sensorValue = analogRead(MQ_PIN);
  int ppm = analogToPpm(sensorValue);
  Serial.print("PPM Gas CO2: ");
  Serial.println(ppm);
  
  sendDataToAPI(ppm); // Kirim data ke API
  delay(5000); // Tunggu 5 detik sebelum mengirim data lagi
}

float analogToPpm(int analogValue) {
  float voltage = (analogValue / 1023.0) * 3.3;
  float ppm = 116.6020682 * pow(voltage / 3.3, -2.769034857);
  return ppm; // Mengembalikan nilai ppm dalam tipe data float
}

void connectWiFi() {
  Serial.println();
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
}

void sendDataToAPI(int ppm) {
  // Buat objek WiFiClient
  WiFiClient client;
  
  // Buat objek HTTPClient dengan objek WiFiClient sebagai argumen
  HTTPClient http;
  
  // Buat URL untuk endpoint API
  String url = serverAddress;
  
  // Mulai permintaan POST ke API
  http.begin(client, url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded"); // Atur header Content-Type
  
  // Buat payload untuk dikirim ke API
  String payload = "gas_level=" + String(ppm); // Mengonversi ppm menjadi string
  
  // Kirim data POST ke API
  int httpResponseCode = http.POST(payload);
  
  // Cek kode respons
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  
  // Akhir permintaan HTTP
  http.end();
}
