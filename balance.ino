#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <ElegantOTA.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WebSerial.h>

//Please remember to change the Macros in this file
#include <secrets.h>

//trying to not end it all

#define LOG_PRINTf(x)   \
    do {               \
        Serial.printf(x);    \
        WebSerial.printf(x); \
    } while (0)
#define LOG_PRINTLN(x) \
    do {               \
        Serial.println(x);    \
        WebSerial.println(x); \
    } while (0)
// ╔══════════════════════════════════════════════════════════╗
// ║                  Init Pins                               ║
// ╚══════════════════════════════════════════════════════════╝
#define LED_BUILTIN 2
#define PWMA 15
#define AIN2 2
#define AIN1 4
#define BIN1 16
#define BIN2 5
#define PWMB 17
#define SCL 22
#define SDA 21

// ╔══════════════════════════════════════════════════════════╗
// ║                  Motor Shit                              ║
// ╚══════════════════════════════════════════════════════════╝
#define FREQ 30000
#define PWMCHANNEL 0
#define RESOLUTION 8 
#define DUTYCYCLE 200



Adafruit_MPU6050 mpu;
AsyncWebServer server(80);

void setup(void) {
// ╔══════════════════════════════════════════════════════════╗
// ║                  Init Pins                               ║
// ╚══════════════════════════════════════════════════════════╝
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PWMB,OUTPUT);
  pinMode(PWMA,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
  pinMode(BIN1,OUTPUT);


  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  LOG_PRINTf("ESP32 Booting up\n");
  delay(5000); // This is needed during Programming phase, the serial connection will output tons of garbage without it

// ╔══════════════════════════════════════════════════════════╗
// ║                  OTA Maybe?                              ║
// ╚══════════════════════════════════════════════════════════╝

  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID,WIFI_PASSWORD);
  LOG_PRINTf("Testing WiFi\n");

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    LOG_PRINTf(".");
  }
  Serial.printf("\nConnected to %s\n IP Address: %s\n", SSID,WiFi.localIP().toString().c_str());
  WebSerial.printf("\nConnected to %s\n IP Address: %s\n", SSID,WiFi.localIP().toString().c_str());
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hi! I am ESP32.");
  });

  server.begin();
  LOG_PRINTLN("HTTP server started");

  ElegantOTA.begin(&server);    // Start ElegantOTA
  WebSerial.begin(&server);
  

// ╔══════════════════════════════════════════════════════════╗
// ║                  MPU Init                                ║
// ╚══════════════════════════════════════════════════════════╝
  LOG_PRINTLN("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    LOG_PRINTLN("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  LOG_PRINTLN("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);


  LOG_PRINTLN("");
  delay(100);

  ledcAttachChannel(PWMA,FREQ,RESOLUTION,PWMCHANNEL);
  ledcAttachChannel(PWMB,FREQ,RESOLUTION,PWMCHANNEL);

  delay(1000);

}


void loop() {
  ElegantOTA.loop();
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  LOG_PRINTf("THIS IS A TEST");
  /* Print out the values */
 // Serial.print("Acceleration X: ");
 // Serial.print(a.acceleration.x);
 // Serial.print(", Y: ");
 // Serial.print(a.acceleration.y);
 // Serial.print(", Z: ");
 // Serial.print(a.acceleration.z);
 // LOG_PRINTLN(" m/s^2");

 // Serial.print("Rotation X: ");
 // Serial.print(g.gyro.x);
 // Serial.print(", Y: ");
 // Serial.print(g.gyro.y);
 // Serial.print(", Z: ");
 // Serial.print(g.gyro.z);
 // LOG_PRINTLN(" rad/s");

 // Serial.print("Temperature: ");
 // Serial.print(temp.temperature);
 // LOG_PRINTLN(" degC");

 // LOG_PRINTLN("");
  delay(100);
  

  digitalWrite(AIN2,HIGH);
  digitalWrite(AIN1,LOW);











  //First time programming esp32!! Not deleting this, its baller 
//  digitalWrite(LED_BUILTIN,HIGH);
//  delay(250);
//  digitalWrite(LED_BUILTIN,LOW);
//  delay(250);
}
