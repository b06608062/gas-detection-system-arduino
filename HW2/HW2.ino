// DHT
#include "DHT.h"
#define DHTPIN 7     
#define DHTTYPE DHT22  
DHT dht(DHTPIN, DHTTYPE);
float h, t;

// LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// MQ2
#define MQPin A0
float Vs = 5.0, RS, RO = 22.0;  // For air, RS / R0 = 9.8 for MQ2 gas sensor.
float sensor_value, sensor_volt;   
float RsR0ratio_33RH_20c, RsR0ratio_85RH_20c, RsR0ratio_65RH_20c;
float RsR0ratio_33RH_nowc, RsR0ratio_85RH_nowc, RsR0ratio_nowRH_nowc;
float adjust;
float RsR0ratio_adjust;
int alcolhol_ppm;


void setup() {
  Serial.begin(9600);
  
  // DHT
  Serial.println("DHTxx test!");
  dht.begin();

  // LCD
  lcd.init();  // 初始化 LCD 
  lcd.backlight();  // 開啟背光
  
  RsR0ratio_33RH_20c = exp(-0.01 * 20) * 1.387;
  RsR0ratio_85RH_20c = exp(-0.01 * 20) * 1.2554;
  RsR0ratio_65RH_20c = RsR0ratio_85RH_20c + (RsR0ratio_33RH_20c - RsR0ratio_85RH_20c) * ((65.0 - 33.0) / (85.0 - 33.0));
}



void loop() {
  DHT_Sensor();

  // 計算誤差比率
  RsR0ratio_33RH_nowc = exp(-0.01 * t) * 1.387;
  RsR0ratio_85RH_nowc = exp(-0.01 * t) * 1.2554;
  RsR0ratio_nowRH_nowc = RsR0ratio_85RH_nowc + (RsR0ratio_33RH_nowc - RsR0ratio_85RH_nowc) * ((h - 33.0) / (85.0 - 33.0));
  adjust = RsR0ratio_nowRH_nowc / RsR0ratio_65RH_20c;

  // 計算 Vout
  sensor_value = 0;
  for(int i = 0; i < 10; i++){
  sensor_value = sensor_value + analogRead(MQPin); 
  delay(300);   
  }
  sensor_value = sensor_value / 10;
  sensor_volt = (sensor_value * 5 / 1024);
  Serial.print("volt = ");
  Serial.println(sensor_volt);

  // 計算 RS
  RS = ((5.0 * 20.0) / sensor_volt) - 20.0;  // RL = 20.0k歐姆

  // 誤差校正
  RsR0ratio_adjust = (RS / RO) / adjust;
  Serial.print("RsR0ratio_adjust = ");
  Serial.println(RsR0ratio_adjust);

  // 換算成酒精濃度
  alcolhol_ppm = 21018 * exp(-1.71 * RsR0ratio_adjust);
  Serial.print("alcolhol_ppm : ");
  Serial.println(alcolhol_ppm);

  // LCD 顯示
  // 第一排
  lcd.setCursor(0, 0);
  lcd.print("H:");
  lcd.print(h);
  lcd.print("% ");
  lcd.print("T:");
  lcd.print((int)t);
  lcd.print(" *C"); 
  // 第二排
  lcd.setCursor(0, 1);
  lcd.print("Alc: ");
  lcd.print(alcolhol_ppm);
  lcd.print(" ppm            ");
  delay(5000);
}


void DHT_Sensor(){
  delay(2000);
  h = dht.readHumidity();
  t = dht.readTemperature();
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");
}
