#include "sensor_queue.h"
#include "sensor_state.h"
#include "projdefs.h"
#include "task.h"
#include "definition.h"
#include "debug.h"
//#include "queue.h"
#include "system_definitions.h"
#include <stdlib.h>
#include <string.h>

QueueHandle_t createQueue(QueueHandle_t handler, const UBaseType_t uxQueueLength, const UBaseType_t uxItemSize)
{
    handler = xQueueGenericCreate(uxQueueLength, uxItemSize, queueQUEUE_TYPE_BASE );
   if(handler == NULL)
   {
       dbgOutputLoc(0x99);
       dbgStop(0x02);
   }
    return handler;
}

NetworkData readNetworkQueue ( QueueHandle_t handler)
{
    BaseType_t xStatus;
    NetworkData pvBuffer;
    xStatus = xQueueReceive (handler, &pvBuffer, portMAX_DELAY);
   if(xStatus != pdPASS)
   {
       dbgOutputLoc(0x98);
       dbgStop(0x01);
   }
    return pvBuffer;
    
}

NetworkData readNetworkQueueISR ( QueueHandle_t handler, BaseType_t *pxHigherPriorityTaskWoken)
{
    BaseType_t xStatus;
    NetworkData pvBuffer;
    xStatus = xQueueReceiveFromISR (handler, &pvBuffer, &pxHigherPriorityTaskWoken);
   if(xStatus != pdPASS)
   {
       //dbgOutputLoc(READ_ARM_QUEUE_FAIL);
       //dbgStop(0x01);
   }
    return pvBuffer;
    
}

BaseType_t writeNetworkQueueISR ( QueueHandle_t handler, void *ItemToQueue, BaseType_t *pxHigherPriorityTaskWoken)
{
    xQueueSendToBackFromISR(handler, ItemToQueue, &pxHigherPriorityTaskWoken);  
}

QueueHandle_t createSensorQueue (const UBaseType_t uxQueueLength, const UBaseType_t uxItemSize)
{
    myQueue = xQueueGenericCreate(uxQueueLength , uxItemSize ,  queueQUEUE_TYPE_BASE );
    return myQueue;
}

QueueHandle_t createTimeQueue (const UBaseType_t uxQueueLength, const UBaseType_t uxItemSize)
{
    timeQueue = xQueueGenericCreate(uxQueueLength , uxItemSize ,  queueQUEUE_TYPE_BASE );
    return timeQueue;
}

QueueHandle_t createISRQueue (const UBaseType_t uxQueueLength, const UBaseType_t uxItemSize)
{
    ISRQueue = xQueueGenericCreate(uxQueueLength , uxItemSize ,  queueQUEUE_TYPE_BASE );
    return ISRQueue;
}

int32_t readTimeQueue (void)
{
    int32_t pvBuffer;
    xQueueReceive(timeQueue, &pvBuffer, portMAX_DELAY);
    return pvBuffer;
}

int32_t readTime2Queue (void)
{
    int32_t pvBuffer;
    xQueueReceive(IR_Queue, &pvBuffer, portMAX_DELAY);
    return pvBuffer;
}
Color_t readSensorQueue ( void ) 
{
   Color_t pvBuffer; 
   xQueueReceive (myQueue, &pvBuffer, portMAX_DELAY);
   return pvBuffer;
}

int32_t readISRQueue (void)
{
    int32_t pvBuffer;
    xQueueReceive(ISRQueue, &pvBuffer, portMAX_DELAY);
    return pvBuffer;
}

BaseType_t writeTimerISR(void *ItemToQueue, BaseType_t *pxHigherPriorityTaskWoken)
{
    xQueueSendToBackFromISR(timeQueue, ItemToQueue, pxHigherPriorityTaskWoken);
}
////
BaseType_t writeSensorQueueISR (void *ItemToQueue)
{
    xQueueSendToBackFromISR(myQueue, ItemToQueue, pdFALSE);
}
////
BaseType_t writeISR(void *ItemToQueue, BaseType_t *pxHigherPriorityTaskWoken)
{
    xQueueSendToBackFromISR(ISRQueue, ItemToQueue, pxHigherPriorityTaskWoken);
}

BaseType_t writeSensorQueue (const void * const ItemToQueue)
{
    xQueueSendToBack( myQueue, ItemToQueue, 0 );
}

BaseType_t writeQueue (QueueHandle_t handler, void *ItemToQueue)
{
    xQueueSendToBack(handler, ItemToQueue, 0);
}

/* *****************************************************************************
 End of File
 */