/*******************************************************************************
 System Interrupts File

  File Name:
    system_interrupt.c

  Summary:
    Raw ISR definitions.

  Description:
    This file contains a definitions of the raw ISRs required to support the
    interrupt sub-system.

  Summary:
    This file contains source code for the interrupt vector functions in the
    system.

  Description:
    This file contains source code for the interrupt vector functions in the
    system.  It implements the system and part specific vector "stub" functions
    from which the individual "Tasks" functions are called for any modules
    executing interrupt-driven in the MPLAB Harmony system.

  Remarks:
    This file requires access to the systemObjects global data structure that
    contains the object handles to all MPLAB Harmony module objects executing
    interrupt-driven in the system.  These handles are passed into the individual
    module "Tasks" functions to identify the instance of the module to maintain.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "system/common/sys_common.h"
#include "app.h"
#include "led_blink.h"
#include "uart_test.h"
#include "rx_test.h"
#include "system_definitions.h"
#include "definitions.h"
#include "sensor_state.h"
#include "sensor_queue.h"
#include "debug.h"
#include "adc_functions.h"
#include "pwm_arm.h"

// *****************************************************************************
// *****************************************************************************
// Section: System Interrupt Vector Functions
// *****************************************************************************
// *****************************************************************************


void IntHandlerDrvI2CInstance0(void)
{
    DRV_I2C_Tasks(sysObj.drvI2C0);
 
}
     
void IntHandlerDrvUsartInstance0(void)
{
    BaseType_t pxHigherPriorityTaskWoken=pdFALSE;
    static int8_t temp[300];
    uint8_t c;
    dbgOutputLoc(0x60);
    static int32_t index = 0;
    static int8_t frame = 0;
    static int32_t isEnd = 0;
    static uint8_t f1[10];
    static NetworkData networkdata;
    
    if(SYS_INT_SourceStatusGet(INT_SOURCE_USART_1_RECEIVE)) {
        dbgOutputLoc(0x69);
        c = PLIB_USART_ReceiverByteReceive(USART_ID_1);
        SYS_INT_SourceStatusClear(INT_SOURCE_USART_1_RECEIVE);
    }
    /**/
    if(SYS_INT_SourceStatusGet(INT_SOURCE_USART_1_TRANSMIT)) {
        dbgOutputLoc(0x62);      
        if(index == 0) {
            dbgOutputLoc(0x10);
            networkdata = readNetworkQueueISR(txUARTQueue, &pxHigherPriorityTaskWoken);
            strcpy(temp, networkdata.data_stream);
            PLIB_USART_TransmitterByteSend(USART_ID_1, networkdata.frame);
            index = index + 1;
        }
        else if(!isEnd) {
            dbgOutputLoc(0x11);
            PLIB_USART_TransmitterByteSend(USART_ID_1, temp[index-1]);
            if(temp[index-1] == '}') {
                isEnd = 1;
            } else if(index > 298) {
                isEnd = 1;
            }
            else
                index = index + 1;
        } else {
            dbgOutputLoc(0x12);
            PLIB_USART_TransmitterByteSend(USART_ID_1, networkdata.frame);
            SYS_INT_SourceDisable(INT_SOURCE_USART_1_TRANSMIT);
            index = 0;
            isEnd = 0;
        }    
    }
    
    if(SYS_INT_SourceStatusGet(INT_SOURCE_USART_1_ERROR)) {
        SYS_INT_SourceDisable(INT_SOURCE_USART_1_ERROR);
        SYS_INT_SourceStatusClear(INT_SOURCE_USART_1_ERROR);
    }
    
    SYS_INT_SourceStatusClear(INT_SOURCE_USART_1_TRANSMIT);
    portEND_SWITCHING_ISR(pxHigherPriorityTaskWoken);
}
 
void IntHandlerDrvTmrInstance0(void)
{   
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_2);
}

 
/*******************************************************************************
 End of File
*/