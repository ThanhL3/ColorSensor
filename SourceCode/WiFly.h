#ifndef _APP3_H
#define _APP3_H



#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif


typedef enum
{
	/* Application's state machine's initial state. */
	APP3_STATE_INIT=0,
	APP3_STATE_SERVICE_TASKS,

	/* TODO: Define states used by the application state machine. */

} APP3_STATES;

typedef enum UART_STATE {UART_IDLE, UART_RX, UART_TX, UART_ER,
                         UART_PUT_ZERO, UART_GET_ZERO, UART_PUT_ONE,   UART_GET_ONE,
                         UART_PUT_TWO,  UART_GET_TWO,  UART_PUT_THREE, UART_GET_THREE,
                         UART_PUT_FOUR, UART_GET_FOUR, UART_PUT_FIVE,  UART_GET_FIVE,
                         UART_PUT, UART_GET} UART_STATE;
                         
typedef struct
{
    /* The application's current state */
    APP3_STATES state;

    /* TODO: Define any additional data used by the application. */

} APP3_DATA;



void APP3_Initialize ( void );



void APP3_Tasks( void );

static void uartTimerCallback( TimerHandle_t xTimer );

#endif /* _APP3_H */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

/*******************************************************************************
 End of File
 */

