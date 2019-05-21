#include "definition.h"

QueueHandle_t myQueue;
QueueHandle_t timeQueue;
QueueHandle_t ISRQueue;

QueueHandle_t txUARTQueue;
QueueHandle_t rxUARTQueue;
QueueHandle_t erUARTQueue;

QueueHandle_t networkQueue;
QueueHandle_t timerUARTQueue;
QueueHandle_t IR_Queue;

TimerHandle_t I2CTimer;
TimerHandle_t ledTimer;
TimerHandle_t uartTimer;
TimerHandle_t IR_Timer;