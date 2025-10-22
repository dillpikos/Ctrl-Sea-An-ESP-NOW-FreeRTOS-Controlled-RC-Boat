#include <esp_now.h>
#include <WiFi.h>

//Pick which core FreeRTOS will run on based on device that's used

#if CONFIG_FREERTOS_UNICORE //single core device
  static const BaseType_t app_cpu = 0;

#else //dual core device 
  static const BaseType_t app_cpu = 1;

#endif


#define CHANNEL 1 //Channel for communcation between transmitter and reciever device
esp_now_peer_info_t slave; //store mac address of reciever

// Pin delcartions and variables to store information
int xPin = 34,
    yPin = 35,
    xPosition,
    yPosition,
    motorSpeed;

//Data thats sent//
uint8_t data = 3;

typedef struct joyStickData{

  int xPos;
  int yPos;

}joyStickData;

joyStickData xData;

void readJoystick(void *placeholder){

  while(true){

    //Read joystick values
    xPosition = analogRead(xPin) /3;
    yPosition = analogRead(yPin) /3;

    //map joystick value to fit PWM rating for DC motor control
    motorSpeed = map(yPosition,0,1365,0,255);

    if(motorSpeed <= 120){ //when joystick is in idle set speed to 0

      motorSpeed = 0;

    }

    else{}

    //Map x-Postition of joystick to control angle of servo and store that into struct
    xData.xPos = map(xPosition,0,1365,70,110);

    xData.yPos = motorSpeed; //store motor speed into struct
    
    esp_now_send(slave.peer_addr,(uint8_t *) &xData, sizeof(xData)); //function that sends struct values to reciever

    vTaskDelay(5 / portTICK_PERIOD_MS); //pause this task and run it every 5 mili-seconds
      
  }


}


void setup() {

  Serial.begin(115200);
  WiFi.mode(WIFI_STA); //puts esp in station mode
  esp_now_init();      //initilizes ESP now
  esp_now_register_send_cb((esp_now_send_cb_t)OnDataSent);    //Call back function that runs everytime data is send
  ScanForSlave(); // WiFi.macAddress()
  esp_now_add_peer(&slave); 

  //Set the pins on the jotStick to input for reading
  pinMode(xPin,INPUT);
  pinMode(yPin,INPUT);

  //Task to handle joystick reading and send it to reciever
  xTaskCreatePinnedToCore(
    readJoystick,
    "Read Joystick",
    4096,
    NULL,
    24,
    NULL,
    app_cpu

  );

}

void loop() {
  // Loop is empty because function is handled as task using freeRTOS //
}

// Function that scans for target reciever
void ScanForSlave() {
  int8_t scanResults = WiFi.scanNetworks();

  for (int i = 0; i < scanResults; ++i) {
    String SSID = WiFi.SSID(i);
    String BSSIDstr = WiFi.BSSIDstr(i);

    if (SSID.indexOf("RX") == 0) {

      int mac[6];
      if ( 6 == sscanf(BSSIDstr.c_str(), "%x:%x:%x:%x:%x:%x",  &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5] ) ) {
        for (int ii = 0; ii < 6; ++ii ) {
          slave.peer_addr[ii] = (uint8_t) mac[ii];
        }
      }

      slave.channel = CHANNEL; // pick a channel
      slave.encrypt = 0; // no encryption
      break;
    }
  }
}

//Function that runs everytime data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("I sent my data -> ");
  Serial.println(xData.xPos);
  Serial.print("I also sent ->");
  Serial.println(xData.yPos);
}