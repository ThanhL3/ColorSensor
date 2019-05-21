
#ifndef _APP2_H
#define _APP2_H


#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "definition.h"
#include "driver/i2c/src/drv_i2c_local.h"
#include "osal/osal.h"
#include "C:\microchip\harmony\v2_06\framework\driver\driver_common.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif


typedef enum
{
	/* Application's state machine's initial state. */
	APP2_STATE_INIT=0,
	APP2_STATE_SERVICE_TASKS,

	/* TODO: Define states used by the application state machine. */

} APP2_STATES;




typedef struct
{
    /* The application's current state */
    APP2_STATES state;

    /* TODO: Define any additional data used by the application. */

} APP2_DATA;


void APP2_Initialize ( void );


void APP2_Tasks( void );
static void send_task ( void *);
static void ledTimerCallback( TimerHandle_t xTimer );

#endif /* _APP2_H */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

/*******************************************************************************
 End of File
 */

