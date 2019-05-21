/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c
  Summary:
    This file contains the source code for the MPLAB Harmony application.
  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.
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

#include "app.h"
#include "debug.h"
#include "system_config.h"
#include "system_definitions.h"
#include "definition.h"
#include "adc_functions.h"
#include "sensor_queue.h"
#include "sensor_state.h"
#include "I2C.h"
#include "timers.h"
#include "system/common/sys_common.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data
  Summary:
    Holds application data
  Description:
    This structure holds the application's data.
  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )
  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    ADC_POLL_INIT();
    dbgInit();
    dbgOutputLoc(APP_INIT_START);
    I2CInit();
    createSensorQueue (5, sizeof( Data_t ));
    createTimeQueue (5, sizeof (Data_t));
    createISRQueue (5, sizeof (Data_t));    
    I2CTimer = xTimerCreate("Timer for color thread",
                            pdMS_TO_TICKS(100),
                            pdTRUE,
                            0,
                            I2CTimeCallBack);
    xTimerStart(I2CTimer, 0);
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )
  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
    
    dbgOutputLoc(APP_TASK_INITIALIZATION);
    int32_t value;
    NetworkData data;
    dbgOutputLoc(APP_TASK_WHILE_LOOP);
    for( ;; )
    {
        value = readTimeQueue();
        dbgOutputLoc(0x16);
        getValue(&data);
        ADC_POLL_START();
        data.IR_Value = ADC_POLL_READ_CM_CONV () / 2;
        ADC_POLL_STOP();
        data.isColor = 1;
        data.isIR = 1;
        data.isTimer = 1;
        data.isRx = 0;
        dbgOutputLoc(I2C_GET_DATA);
        //writeSensorQueue(&data);
        writeQueue(networkQueue, &data);
        dbgOutputLoc(0x17);
    }
      
}

static void I2CTimeCallBack( TimerHandle_t xTimer)
{
    BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
    int32_t data = 1;
    dbgOutputLoc(0x55);
    writeTimerISR(&data, &pxHigherPriorityTaskWoken);
}
/*******************************************************************************
 End of File
 */