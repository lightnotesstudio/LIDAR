
#include <RPLidar.h>

RPLidar lidar;

#define RPLIDAR_MOTOR 7 
                        
void setup() {
  Serial1.begin(115200);
  Serial.begin(115200);
  lidar.begin(Serial);
  
  pinMode(RPLIDAR_MOTOR, OUTPUT);

}

void loop() {
//  if (Serial1.available()) {
//    int inByte = Serial1.read();
//    Serial.write(inByte);
//  }
//  
  if (IS_OK(lidar.waitPoint())) {
    float distance = lidar.getCurrentPoint().distance; 
    float angle    = lidar.getCurrentPoint().angle; 
  
    Serial.print(" ");
    Serial.print(distance);
    Serial.print("-");
    Serial.println(angle);
   
  } else {
    analogWrite(RPLIDAR_MOTOR, 0); 

    rplidar_response_device_info_t info;
    if (IS_OK(lidar.getDeviceInfo(info, 100))) {
       
       lidar.startScan();
       analogWrite(RPLIDAR_MOTOR, 255);
       delay(1000);
    }
  }
}
