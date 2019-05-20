**COLOR SENSOR DRIVER**

This is an embedded C project that utilizes the TCS I2C Color Sensor on a PIC32 microcontroller. The project uses multithreading to allow one thread to read color data from the sensor and send that data to another thread. The other thread utilizes UART communication to operate a WiFly peripheral to send color data to a seperate server.   

Below are the configuration 

Microcontroller Board: PIC32MX795F512L

IDE: MPLabX 

Library: FreeRTOS + Harmony 

Wireless Peripheral: RN-171

Color Sensor: TCS34725, RGB Color Sensor with IR filter and White LED 
