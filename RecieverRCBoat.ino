#include <esp_now.h>
#include <WiFi.h>
#include <ESP32Servo.h>
#define CHANNEL 1 
Servo Servo1;

#if CONFIG_FREERTOS_UNICORE //single core device
  static const BaseType_t app_cpu = 0;

#else //dual core device
  static const BaseType_t app_cpu = 1;

#endif

int servoPin = 12,
    newServoX,
    newServoY,
    servoDirections;

int motorPin = 13,
    motorSpeed;


// JOYSTICK CODE AND TEST //

int xPin = 34,
    yPin = 35,
    buttonPin = 4,
    yPosition,
    buttonState,
    xScreenPosition,
    yScreenPosition;

typedef struct joyStickData{

  int xPos;
  int yPos;

}joyStickData;

joyStickData incomingX;

uint8_t newData; //initializes unsigned integer newData

void readJoy(void *values){

  while(true){
    Serial.print("I did this to data -> "); // manipulates data received
    Serial.println(newData * 5);

    analogWrite(motorPin,incomingX.yPos);

    Serial.println(motorSpeed);


    Servo1.write(incomingX.xPos);


    vTaskDelay(20 / portTICK_PERIOD_MS);
  }


}

void setup() {  
  Serial.begin(115200);
  
  WiFi.mode(WIFI_AP); 
  WiFi.softAP("RX_1", "RX_1_Password", CHANNEL, 0); // Configures the AP
  
  esp_now_init(); // initializes esp_now
  esp_now_register_recv_cb(OnDataRecv);  // callback function to data received

  pinMode(motorPin, OUTPUT);

  Servo1.attach(servoPin, 500,2400);  //attach servoPin to object


  xTaskCreatePinnedToCore(
    readJoy,               //Function that's called
    "readJoy",             //Name of Task
    4096,                   //Stack size (1024 good for smaller tasks, in this case 4096)
    NULL,                   //Parameter for function
    24,                      //Task Priority 0-24 (0 lowest priority & 24 highest priority )
    NULL,                   //Task handler
    app_cpu);       //run task on core selected at the top
  
}

void loop() { // loop empty due to while true function used with RTOS
}

/** callback when data is recv from Master **/


void OnDataRecv(const esp_now_recv_info *info, const uint8_t *data, int data_len) { //callback signature takes data and displays.
  
  memcpy(&incomingX, data, sizeof(incomingX));

  Serial.println(incomingX.xPos);
  Serial.println(incomingX.yPos);


  //Serial.print("I just received -> ");
  //Serial.println(data.);
}
