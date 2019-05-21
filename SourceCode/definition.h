#include "FreeRTOS.h"
#include "queue.h"
#include "timers.h"

extern QueueHandle_t myQueue;
extern QueueHandle_t timeQueue;
extern QueueHandle_t ISRQueue;

extern TimerHandle_t I2CTimer;
extern TimerHandle_t ledTimer;
extern TimerHandle_t uartTimer;
extern TimerHandle_t IR_Timer;

extern QueueHandle_t txUARTQueue;
extern QueueHandle_t rxUARTQueue;
extern QueueHandle_t erUARTQueue;

extern QueueHandle_t networkQueue;
extern QueueHandle_t timerUARTQueue;
extern QueueHandle_t IR_Queue;

#define SENSOR_QUEUE_WRITE 0x40
#define WRITE_QUEUE_ERROR 0x41
#define WRITE_QUEUE_SUCCESS 0x42
#define SENSOR_QUEUE_READ 0x43
#define READ_QUEUE_ERROR 0x44
#define READ_QUEUE_SUCCESS 0x45
#define SENSOR_READ 0x46
#define TIMER_ISR_START 0x47
#define TIMER_ISR_EXIT 0x48
#define APP_TASK_START 0x49
#define APP_TASK 0x50
#define APP_INIT_START 0x51




