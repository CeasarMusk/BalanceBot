#define LED_BUILTIN 2
#define PWMA 15
#define AIN2 2
#define AIN1 4
#define BIN1 16
#define BIN2 5
#define PWMB 17
#define SCL 22
#define SDA 21




void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PWMB,OUTPUT);
  pinMode(PWMA,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(SCL,INPUT);
  pinMode(SDA,INPUT);

}



void loop() {
  digitalWrite(LED_BUILTIN,HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN,LOW);
  delay(250);
}
