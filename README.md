# RC-Boat "Ctrl + Sea"
Ctrl + Sea is a wireless RC boat powered by ESP-32 microcontrollers communicating via ESP-NOW a peer to peer protocol. This project implements FreeRTOS on both the transmitter(master) and receiver(slave) to better handle concurent tasks that include, motor control, communication, and steering of the vessel. This approach allows us to provide smoother-real time control via joystick.

<br>
On the master side FreeRTOS manages tasks for joystick readings and processing to sucessfully transfer control to data to the reciever.
<br>
On the slave side FreeRTOS manages tasks for recieving transmitted data turning it into motor output (speed control), servo output (vessel steering).

*created by: Bryan Diaz & Junior Ortega | Focus: Embedded Systems, Wireless communication, Real time control system*

# Technologies and Components
## Hardware Related

- 
## Software Related
- Arduino IDE
- Fusion 360 (3D Modeling Boat shell, Propeller, and Rudder)
- C++ (Libraries:
- FREE RTOS
- ESP-NOW (Send Data readings from controller to main esp)
- 


# System Features



# System Preview



