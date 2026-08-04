#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <ElegantOTA.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

//trying to not end it all
//Add ENV var's


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


// ╔══════════════════════════════════════════════════════════╗
// ║                  OTA Maybe?                              ║
// ╚══════════════════════════════════════════════════════════╝
#define ssid 


Adafruit_MPU6050 mpu;
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

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  delay(100);

  ledcAttachChannel(PWMA,FREQ,RESOLUTION,PWMCHANNEL);
  ledcAttachChannel(PWMB,FREQ,RESOLUTION,PWMCHANNEL);

  delay(1000);

}


void loop() {
 
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" degC");

  Serial.println("");
  delay(100);
  

  digitalWrite(AIN2,HIGH);
  digitalWrite(AIN1,LOW);











  //First time programming esp32!! Not deleting this, its baller 
//  digitalWrite(LED_BUILTIN,HIGH);
//  delay(250);
//  digitalWrite(LED_BUILTIN,LOW);
//  delay(250);
}
