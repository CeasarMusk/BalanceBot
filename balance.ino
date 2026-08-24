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
#define SCL 22
#define SDA 21

// ╔══════════════════════════════════════════════════════════╗
// ║                  Motor Shit                              ║
// ╚══════════════════════════════════════════════════════════╝
#define FREQ 20000
#define PWMCHANNEL 0
#define RESOLUTION 8 
#define DUTYCYCLE 220

#define DIR1 33
#define DIR2 26
#define PMW1 25
#define PMW2 32


//Adafruit_MPU6050 mpu;
AsyncWebServer server(80);

void setup(void) {
// ╔══════════════════════════════════════════════════════════╗
// ║                  Init Pins                               ║
// ╚══════════════════════════════════════════════════════════╝
  pinMode(DIR1,OUTPUT);
  pinMode(DIR2,OUTPUT);
  pinMode(PMW1,OUTPUT);
  pinMode(PMW2,OUTPUT);
  

  // Set these to low, I totally fried my first board because the pins were floating HIGH at startup
  digitalWrite(DIR1,LOW);
  digitalWrite(DIR2,LOW);
  digitalWrite(PMW1,LOW);
  digitalWrite(PMW2,LOW);



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
 // if (!mpu.begin()) {
 //   LOG_PRINTLN("Failed to find MPU6050 chip");
 //   while (1) {
 //     delay(10);
 //   }
 // }
 // LOG_PRINTLN("MPU6050 Found!");

 // mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
 // mpu.setGyroRange(MPU6050_RANGE_500_DEG);
 // mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);


 // LOG_PRINTLN("");
  delay(100);


  delay(1000);

}


void loop() {
  
  ElegantOTA.loop();
  LOG_PRINTf("Everything was Sucessful!3\n");
  //sensors_event_t a, g, temp;
  //mpu.getEvent(&a, &g, &temp);
  
  delay(5000);
   
  digitalWrite(PMW1,HIGH);
  digitalWrite(DIR1,HIGH);




  //First time programming esp32!! Not deleting this, its baller 
//  digitalWrite(LED_BUILTIN,HIGH);
//  delay(250);
//  digitalWrite(LED_BUILTIN,LOW);
//  delay(250);
}
