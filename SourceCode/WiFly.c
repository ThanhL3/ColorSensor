#include "app3.h"
#include "definition.h"
#include "sensor_queue.h"

APP3_DATA app3Data;



void APP3_Initialize ( void )
{
    uartTimer = xTimerCreate(
            "Timer to test UART transactions",
            pdMS_TO_TICKS(100),
            pdTRUE,
            0,
            uartTimerCallback);
    
    networkQueue = createQueue(networkQueue, 5, sizeof( NetworkData));
    
    txUARTQueue = createQueue(txUARTQueue, 5, sizeof( NetworkData));
    timerUARTQueue = createQueue(timerUARTQueue, 5, sizeof( int32_t));
    
    xTimerStart(uartTimer, 0);
}



void APP3_Tasks ( void )
{
    
    char *temp;
    uint8_t temp2[3];
    
    int32_t tester = 0;
    int32_t num = 0;
    int32_t num2 = 0;
    int32_t frame = 0;
    
    NetworkData networkdata;
    
    char colorBuffer[50];
    char redColor[10];
    char greenColor[10];
    char blueColor[10];
    char irData[10];
    
    static UART_STATE uart_state = UART_IDLE;   
    static int32_t get_state = 0;
    static int32_t put_state = 0;
    uint8_t temp_new[] = "";//GET.{\"name\": \"Dingwen\"}";
    
    dbgOutputLoc(0x50);
    for(;;) 
    {   
        dbgOutputLoc(0x51);
        networkdata = readNetworkQueue(networkQueue);
        dbgOutputLoc(0x52);
        
        if(networkdata.isColor == 1)
        {
            sprintf(redColor, "%d", networkdata.red);
            sprintf(greenColor, "%d", networkdata.green);
            sprintf(blueColor, "%d", networkdata.blue);
        }
        else if (networkdata.isIR == 1)
        {
            sprintf(irData, "%d", networkdata.IR_Value);
        }
        
        
        if(networkdata.isTimer == 1 && networkdata.isRx == 0) {
        switch(uart_state)
        {
            case UART_IDLE:
                dbgOutputLoc(0x53);
                uart_state = UART_PUT;
            break;
            case UART_PUT:
  
                if(put_state == 0) {
                    //strcpy(temp_new, "PUT.{\"name\": \"Dingwen\", \"value\": \"123\"}");
                    strcpy(temp_new, "PUT.{\"name\": \"RED\", \"Value\": \"" );
                    strcat(temp_new, redColor);
                    strcat(temp_new, "\"}");
                    put_state = 1;
                }
                else if(put_state == 1) {
                    //strcpy(temp_new, "PUT.{\"name\": \"Dingwen1\", \"value\": \"456\"}");
                    strcpy(temp_new, "PUT.{\"name\": \"GREEN\", \"Value\": \"" );
                    strcat(temp_new, greenColor);
                    strcat(temp_new, "\"}");
                    put_state = 2;                    
                }else if(put_state == 2) {
                    //strcpy(temp_new, "PUT.{\"name\": \"Dingwen2\", \"value\": \"789\"}");
                    strcpy(temp_new, "PUT.{\"name\": \"BLUE\", \"Value\": \"" );
                    strcat(temp_new, blueColor);
                    strcat(temp_new, "\"}");
                    put_state = 3;                    
                }
                else if(put_state == 3)
                {
                    strcpy(temp_new, "PUT.{\"name\": \"IR\", \"Value\": \"" );
                    strcat(temp_new, irData);
                    strcat(temp_new, "\"}");
                    put_state = 0;
                }
                uint8_t f1[1];

                strcpy(networkdata.data_stream, temp_new);
                networkdata.frame = frame;
                
                if(frame == 35)
                    frame = 37;
                else if(frame >= 255)
                    frame = 0;
                else
                    frame = frame + 1;
                writeQueue(txUARTQueue, &networkdata);  
                SYS_INT_SourceEnable(INT_SOURCE_USART_1_TRANSMIT); 
                
                uart_state = UART_PUT;
                
                //if(put_state == 4)
                   //uart_state = UART_TX;
            break;
            case UART_GET:
                if(get_state == 0) {
                    strcpy(temp_new, "GET.{\"name\": \"Dingwen\"}");
                    get_state = 1;
                }else if(get_state == 1) {
                    strcpy(temp_new, "GET.{\"name\": \"Dingwen1\"}");
                    get_state = 2;                    
                }else if(get_state == 2) {
                    strcpy(temp_new, "GET.{\"name\": \"Dingwen2\"}");
                    get_state = 3;                    
                }else if(get_state == 3) {
                    strcpy(temp_new, "GET.{\"name\": \"Dingwen3\"}");
                    get_state = 4;                    
                }else if(get_state == 4) {
                    strcpy(temp_new, "GET.{\"name\": \"Dingwen4\"}");
                    get_state = 0;                    
                }
                dbgOutputLoc(0x55);                 

                //uint8_t temp_new2[] = "GET /debug HTTP/1.1\r\nHost: 192.168.0.10:80\r\nContent-Type: application/json\r\nContent-Length: 19\r\n\r\n{\"name\": \"Dingwen\"}";
                //uint8_t temp_new2[] = "PUT.{\"name\": \"Dingwen\", \"value\": \"456\"}";
                strcpy(networkdata.data_stream, temp_new);
                
                networkdata.frame = frame;
                
                if(frame == 35)
                    frame = 37;
                else if(frame >= 255)
                    frame = 0;
                else
                    frame = frame + 1;
                networkdata.num_bytes = 50;//sizeof(temp);
                //temp2[0] = 0x05;
                dbgOutputLoc(0x54);   
                writeQueue(txUARTQueue, &networkdata);  
                SYS_INT_SourceEnable(INT_SOURCE_USART_1_TRANSMIT); 
                
                uart_state = UART_PUT;
                
                //if(get_state == 4)
                   //uart_state = UART_TX;
                
            break;                
            case UART_TX:
                
            break;
            case UART_RX:
                
            break;
            case UART_ER:
                
            break;
            default:
                uart_state = UART_IDLE;

        }
        }
        else if(networkdata.isRx == 1) {
            
        }
    }
     
}

static void uartTimerCallback( TimerHandle_t xTimer )
{
    NetworkData temp;
    temp.isTimer = 1;
    temp.isRx = 0;
    //int8_t temp = 1;
    dbgOutputLoc(0x44);
    //writeQueue(timerUARTQueue, &temp);
    //writeQueue(networkQueue, &temp);
} 

/*******************************************************************************
 End of File
 */
