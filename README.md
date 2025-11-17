# RC-Boat "Ctrl + Sea"
"Ctrl + Sea" is a wireless RC boat powered by ESP-32 microcontrollers communicating via ESP-NOW a peer to peer protocol. This project implements FreeRTOS on both the transmitter(master) and receiver(slave) to better handle concurrent tasks that include, motor control, communication, and the steering of the vessel. This approach allows us to provide smooth, real-time control via joystick.
<br>

On the master (transmitter) side, FreeRTOS manages tasks for joystick readings and processing to successfully transfer control to data to the reciever.<br>
On the slave (receiver) side, FreeRTOS manages tasks for receiving transmitted data turning it into motor output (speed control), servo output (vessel steering).

*created by: Bryan Diaz & Junior Ortega | Focus: Embedded Systems, Wireless communication, Real time control system*

# Technologies and Components
## Hardware Related
- ESP-32 (X2)
- SG90 Servo Motor (X1) [steering control]
- 1.5V-6V DC Motor (X1) [speed control]
- Power bank (5000 MaH)
- Joystick Module (controller)
- Soldering of throuhg hole components

## Software Related
- Arduino IDE
- Fusion 360 (3D Modeling Boat shell, Propeller, and Rudder)
- C++ (Custom tasks for speed and steer control eliminating excess memory usage)
- FreeRTOS (Task managment)
- ESP-NOW (Sends data readings from controller to main esp)

# System Features
- Wireless communcation between boat and controller via ESP-NOW
- Real-time task scheduling using FreeRTOS
- Joystick controlled thrust and rudder steer

# System Preview
<img src = "https://github.com/user-attachments/assets/f2634312-231c-433a-907a-b48d7a73e2e3" width = "550" height = "550"/> 
<img src = "https://github.com/user-attachments/assets/f1c9924c-bdac-48ba-b3b4-989bdd321921" width = "550" height = "550"/> 



