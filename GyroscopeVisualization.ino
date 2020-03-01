#include <Adafruit_MPU6050.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

//LED Pins:
const int onder = 2;
const int midden = 3;
const int links = 4;
const int boven = 5;
const int rechts = 6;

void setup() {
  pinMode(onder, OUTPUT);
  pinMode(midden, OUTPUT);
  pinMode(links, OUTPUT);
  pinMode(boven, OUTPUT);
  pinMode(rechts, OUTPUT);
  Serial.begin(115200);

  //MPU6050 Gyro:
  if (!mpu.begin()) {
    Serial.println("Sensor init failed");
    while (1)
      yield();
  }
  Serial.println("Found a MPU-6050 sensor");

  //SSD1306 Display:
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { //Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display();
  delay(500);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setRotation(0);
}

void loop() {
  digitalWrite(onder, LOW);
  digitalWrite(midden, LOW);
  digitalWrite(links, LOW);
  digitalWrite(boven, LOW);
  digitalWrite(rechts, LOW);

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Accelerometer:");
  display.print(a.acceleration.x, 1);
  display.print(", ");
  display.print(a.acceleration.y, 1);
  display.print(", ");
  display.print(a.acceleration.z, 1);
  display.println("");
  display.display();

  Serial.print("Accelerometer:");
  Serial.print(" X: ");
  Serial.print(a.acceleration.x, 1);
  Serial.print(" Y: ");
  Serial.print(a.acceleration.y, 1);
  Serial.print(" Z: ");
  Serial.println(a.acceleration.z, 1);
  Serial.print("Gyroscope:");
  Serial.print(" X: ");
  Serial.print(g.gyro.x, 1);
  Serial.print(" Y: ");
  Serial.print(g.gyro.y, 1);
  Serial.print(" Z: ");
  Serial.println(g.gyro.z, 1);

  //LED'S:
  if (a.acceleration.x < 1 && a.acceleration.x > -1 && a.acceleration.y < 1 && a.acceleration.y > -1) {
    digitalWrite(midden, HIGH);
  }
  if (a.acceleration.x > 5) {
    digitalWrite(links, HIGH);
    display.drawLine(0, 32, 128, 16, WHITE);
    display.display();
  }
  if (a.acceleration.x < -5) {
    digitalWrite(rechts, HIGH);
    display.drawLine(0, 16, 128, 32, WHITE);
    display.display();
  }
  if (a.acceleration.y > 5) {
    digitalWrite(onder, HIGH);
  }
  if (a.acceleration.y < -5) {
    digitalWrite(boven, HIGH);
  }
  delay(250);
}
