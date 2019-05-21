- 3 threads are running concurrently in the project.

Color Sensor Thread: Gets data from the sensor and send the data to the WiFly Thread.

Blink Thread: Blinks an LED every 250ms (using software timer). This is a debug mechanism to see if the board is freezing or not. 

WiFly Thread: Receives the color data from the color thread and enables the UART_Transmit interrupt.

Interrupt (system_interrupt.c)
I2C: Not much going on here, I2C interrupts are enabled so that the I2C Harmony Drivers can be used.  
USART: Gets trigged whenever the Transmit Flag or the Received Flag is enabled. Performs operations according to the types of interrupt flags that are currently enabled. There is also the Error flag but that should never be enabled. 
