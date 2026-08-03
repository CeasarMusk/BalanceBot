#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>



#define LED_BUILTIN 2
#define PWMA 15
#define AIN2 2
#define AIN1 4
#define BIN1 16
#define BIN2 5
#define PWMB 17
#define SCL 22
#define SDA 21

Adafruit_MPU6050 mpu;


void setup() {
  Serial.begin(115200);
  delay(3000);
  Wire.begin();
  Serial.println("Testing IMU connection");
  delay(5000);
  //Attempts to initialize IMU
  if(!mpu.begin()){
    Serial.println("FUCK");
    for(;;){
      delay(500);
    }
  }
  Serial.println("IMU Found");
  


  //Pins
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PWMB,OUTPUT);
  pinMode(PWMA,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
  pinMode(BIN1,OUTPUT);

}



void loop() {
 Serial.printf("millis = %lu\n", millis());
  delay(1000);












  //First time programming esp32!! Not deleting this, its baller 
//  digitalWrite(LED_BUILTIN,HIGH);
//  delay(250);
//  digitalWrite(LED_BUILTIN,LOW);
//  delay(250);
}
