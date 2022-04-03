# Environmental automatic system design and programming application

## HW2([Task description](https://github.com/b06608062/gas-detection-system-arduino/blob/master/環境自動化－作業二.pdf))
Gas sensors are designed to measure the concentration of gases in the environment. MQ2 gas sensor is suitable for detecting H2, LPG, CH4, CO, Alcohol, Smoke or Propane. Due to its high sensitivity and fast response time, measurement can be taken as soon as possible.
![This is an image](https://github.com/b06608062/gas-detection-system-arduino/blob/master/demo_image/截圖%202022-04-03%20下午5.24.05.png)
![This is an image](https://github.com/b06608062/gas-detection-system-arduino/blob/master/demo_image/截圖%202022-04-03%20下午1.47.18.png)

## Demo
[Demo Link](https://youtu.be/3q7xyJ9aPls)

## Adjustment table
![This is an image](https://github.com/b06608062/gas-detection-system-arduino/blob/master/demo_image/截圖%202022-04-03%20下午1.18.25.png)

## Calculation of RS
```
// RS = ((Vin * RL) / Vout) - RL
RS = ((5.0 * 20.0) / sensor_volt) - 20.0;
```
