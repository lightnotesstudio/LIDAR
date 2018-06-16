#include <RPLidar.h>
RPLidar lidar;

#define RPLIDAR_MOTOR 7 // The PWM pin for control the speed of RPLIDAR's motor.
                       
void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  lidar.begin(Serial1);  

  pinMode(RPLIDAR_MOTOR, OUTPUT);
}

void loop() {

  if (Serial1.available()) {
    int inByte = Serial1.read();
    Serial.write(inByte);
  }
  
  if (IS_OK(lidar.waitPoint())) {
    float distance = lidar.getCurrentPoint().distance; //distance value in mm unit
    float angle    = lidar.getCurrentPoint().angle; //anglue value in degree
    bool  startBit = lidar.getCurrentPoint().startBit; //whether this point is belong to a new scan
    byte  quality  = lidar.getCurrentPoint().quality; //quality of the current measurement
    
    Serial.print(" ");
    Serial.print(distance);
    Serial.print("-");
    Serial.print(angle); 
    Serial.print("-");
    Serial.println(quality);
    
    
  } else {
    analogWrite(RPLIDAR_MOTOR, 0); //stop the rplidar motor

    rplidar_response_device_info_t info;
    if (IS_OK(lidar.getDeviceInfo(info, 100))) {
       lidar.startScan();
       analogWrite(RPLIDAR_MOTOR, 255);
       delay(1000);
    }
  }
}
