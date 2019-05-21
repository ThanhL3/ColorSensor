#include "I2C.h"
#include "driver/i2c/src/drv_i2c_local.h"
#include "osal/osal.h"

void I2CInit()
{
    I2CHandler = DRV_I2C_Open(0, DRV_IO_INTENT_READWRITE | DRV_IO_INTENT_NONBLOCKING);
    if(I2CHandler == DRV_HANDLE_INVALID)
    {
        char s[20];
        sprintf(s, "Invalid Handle ");
        dbgUARTVal(s);
    }
    enableAddress = (0x29 << 1); //write address
	enableCmd[2] = {0b10000000, 0b00011011}; //enable command 
	uint8_t start2Read = 0b10010110; 
	voidBuff = 0x00;
	readAddress = 0x53; //read address
	slaveAddress2 = 0x17; //high red register 
	slaveAddress3 = 0x18; //low green register 
	slaveAddress4 = 0x19; //high green register
	slaveAddress5 = 0x1A; //low blue register
	slaveAddress6 = 0x1B; //high blue register 
}

int getStatus(DRV_I2C_BUFFER_HANDLE buffer)
{
    DRV_I2C_BUFFER_EVENT status;
    status = DRV_I2C_BufferStatus(buffer);
    if(status == DRV_I2C_BUFFER_EVENT_PENDING) return 0x1;
    else if (status == DRV_I2C_BUFFER_EVENT_COMPLETE) return 0x2;
    else if (status == DRV_I2C_BUFFER_EVENT_ERROR) return 0x3;
    else if (status == DRV_I2C_SEND_STOP_EVENT) return 0x4;
    else if (status == DRV_I2C_SEND_RESTART_EVENT) return 0x5;
    else if (status == DRV_I2C_BUFFER_SLAVE_READ_REQUESTED) return 0x6;
    else if (status == DRV_I2C_BUFFER_SLAVE_WRITE_REQUESTED) return 0x7;
    else if (status == DRV_I2C_BUFFER_SLAVE_READ_BYTE) return 0x8;
    else if (status == DRV_I2C_BUFFER_MASTER_ACK_SEND) return 0x9;
    else if (status == DRV_I2C_BUFFER_MASTER_NACK_SEND) return 0x10;
    else if (status == DRV_I2C_BUFFER_SLAVE_WRITE_BYTE) return 0x11;
    return 0;
}

NetworkData getValue(NetworkData *data)
{
    static STATE currState = WRITE; 
    char s[50];
	static int count = 0;
	static uint8_t red;
	static uint8_t green;
	static uint8_t blue;
	for (int x = 0; x < 8; x++)
	{
		//writing to Enable Register
        writeHandle = DRV_I2C_Transmit(I2CHandler, enableAddress, &enableCmd, sizeof(enableCmd), NULL);
            
        currState = READ;

            
        if      (count == 0) start2Read = 0b10010100; //CLEAR LOW
        else if (count == 1) start2Read = 0b10010101; //CLEAR HIGH 
        else if (count == 2) start2Read = 0b10010110; //RED LOW 
        else if (count == 3) start2Read = 0b10010111; //RED HIGH
        else if (count == 4) start2Read = 0b10011000; //GREEN LOW
        else if (count == 5) start2Read = 0b10011001; //GREEN HIGH
        else if (count == 6) start2Read = 0b10011010; //BLUE LOW
        else if (count == 7) start2Read = 0b10011011; //BLUE HIGH
                
        writeHandle = DRV_I2C_Transmit(I2CHandler, enableAddress, &start2Read, sizeof(start2Read), NULL);
        writeHandle = DRV_I2C_Transmit(I2CHandler, readAddress, &voidBuff, sizeof(voidBuff), NULL);
                
        if(count == 2)
        {
            readHandle = DRV_I2C_Receive(I2CHandler, readAddress, &readBuffer, sizeof(readBuffer), context);
                
            red = readBuffer;
        }
        else if (count == 4)
        {
            readHandle = DRV_I2C_Receive(I2CHandler, readAddress, &readBuffer2, sizeof(readBuffer2), context);
                
            green = readBuffer2;
        }
        else if (count == 6)
        {
            readHandle = DRV_I2C_Receive(I2CHandler, readAddress, &readBuffer3, sizeof(readBuffer3), context);
                
            blue = readBuffer3;
        }
        else
        {
            readHandle = DRV_I2C_Receive(I2CHandler, readAddress, &readBuffer3, sizeof(readBuffer3), context);        
        }
            
        count++;
        if(count == 8)
        {
            count = 0;
            data->red = red;
            data->green = green;
            data->blue = blue;
        }
	}
}