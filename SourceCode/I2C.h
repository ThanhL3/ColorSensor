#ifndef _I2C_H    /* Guard against multiple inclusion */
#define _I2C_H

#include "driver/i2c/src/drv_i2c_local.h"
#include "osal/osal.h"
#include "debug.h"

typedef struct
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} Color_t;

typedef struct 
{
    int32_t isTimer;
    int32_t isRx;
    int32_t isColor;
    int32_t isIR;
    int32_t num_bytes;
    uint8_t data_stream[300];
    uint8_t frame;
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t IR_Value;
} NetworkData;

DRV_HANDLE I2CHandler;
uint8_t enableAddress;
uint8_t enableCmd[2]; //writing to Enable Register
uint8_t enableCmd2[2]; //writing to Persistence Register
uint8_t start2Read; //command to read from sensor


uint8_t voidBuff;
uint8_t commandBuffer;

uint8_t readBuffer;
uint8_t readBuffer2;
uint8_t readBuffer3;
uint8_t readBuffer4;
uint8_t readBuffer5;
uint8_t readBuffer6;

uint8_t readAddress;
uint8_t slaveAddress2;
uint8_t slaveAddress3;
uint8_t slaveAddress4;
uint8_t slaveAddress5;
uint8_t slaveAddress6;


DRV_I2C_BUFFER_HANDLE writeHandle;
DRV_I2C_BUFFER_HANDLE readHandle;
void * context;
DRV_I2C_BUFFER_EVENT currentStatus;

void I2CInit();
NetworkData getValue(NetworkData *data);
int getStatus(DRV_I2C_BUFFER_HANDLE buffer);
#endif
/* *****************************************************************************
 End of File
 */
