/* 
 * File:   debug.h
 * Author: cheng
 *
 * Created on January 31, 2019, 8:56 AM
 */

#ifndef DEBUG_H
#define	DEBUG_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
//#include <peripheral/peripheral.h>
#include "system_config.h"
#include "system_definitions.h"
#include "definition.h"

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum
{
    APP_TASK_INITIALIZATION = 0x0,
    APP_TASK_WHILE_LOOP = 0x1,
            APP_TASK_READY_TO_SEND_RECIEVE = 0x2,
            APP_TASK_AFTER_SEND_RECIEVE = 0x3,
            ISR_INITIALIZATION = 0x4,
            ISR_LEAVING = 0x5,
            ISR_READY_TO_SEND_RECIEVE = 0x6,
            ISR_AFTER_SEND_RECIEVE = 0x7,
            ISR_TIMER_SEND = 0x8,
            ISR_TIMER_ENTER = 0x9,
            ISR_TIMER_LEAVING = 0x10,
            TIMER_RECEIVE = 0x11,
            COLOR_SEND = 0x12,
            I2C_GET_DATA = 0x13,
            WRITE_COLOR = 0x14,
            COLOR_RECEIVE = 0x15,
            ISR_RECEIVE = 0x16
} LOCATIONS;
    
void dbgOutputVal(unsigned int outVal);
void dbgOutputLoc(unsigned int outVal);
void dbgUARTVal(unsigned char *outVal);
void dbgStop(unsigned int outVal);
void dbgInit(void);

#ifdef	__cplusplus
}
#endif

#endif	/* DEBUG_H */