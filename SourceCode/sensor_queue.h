#include "FreeRTOS.h"
#include "queue.h"
#include "I2C.h"
#include "sensor_state.h"
#include "definition.h"

#ifndef SENSOR_QUEUE_H    /* Guard against multiple inclusion */
#define SENSOR_QUEUE_H


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

QueueHandle_t createQueue(QueueHandle_t handler, const UBaseType_t uxQueueLength, const UBaseType_t uxItemSize);

QueueHandle_t createTimeQueue (const UBaseType_t uxQueueLength, const UBaseType_t uxItemSize);    
QueueHandle_t createSensorQueue (const UBaseType_t uxQueueLength, const UBaseType_t uxItemSize);
QueueHandle_t createISRQueue (const UBaseType_t uxQueueLength, const UBaseType_t uxItemSize);

NetworkData readNetworkQueue ( QueueHandle_t handler);
NetworkData readNetworkQueueISR ( QueueHandle_t handler, BaseType_t *pxHigherPriorityTaskWoken);
BaseType_t writeNetworkQueueISR ( QueueHandle_t handler, void *ItemToQueue, BaseType_t *pxHigherPriorityTaskWoken);

int32_t readTimeQueue (void);
int32_t readISRQueue (void);
int32_t readTime2Queue (void);
Color_t readSensorQueue ( void );

BaseType_t writeSensorQueue (const void * const ItemToQueue);
BaseType_t writeSensorQueueISR (void *ItemToQueue);
BaseType_t writeTimerISR(void *ItemToQueue, BaseType_t *pxHigherPriorityTaskWoken);
BaseType_t writeISR(void *ItemToQueue, BaseType_t *pxHigherPriorityTaskWoken);

BaseType_t writeQueue ( QueueHandle_t handler, void *ItemToQueue);
#endif /* SENSOR_QUEUE_H */



/* *****************************************************************************
 End of File
 */