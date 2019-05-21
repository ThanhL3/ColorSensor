#include "debug.h"

//initialize the pins on the board for logic analyzer
void dbgInit(void)
{
    TRISBbits.TRISB12 = 0; // 42
    TRISGbits.TRISG8 = 0;
    TRISAbits.TRISA10 = 0;
    TRISFbits.TRISF0 = 0;
    TRISFbits.TRISF1 = 0;
    TRISDbits.TRISD6 = 0; // 47
    TRISDbits.TRISD8 = 0;
    TRISDbits.TRISD11 = 0; // 49
    TRISGbits.TRISG7 = 0; // 50
    TRISEbits.TRISE0 = 0; // 37
    TRISEbits.TRISE1 = 0;
    TRISEbits.TRISE2 = 0;
    TRISEbits.TRISE3 = 0;
    TRISEbits.TRISE4 = 0;
    TRISEbits.TRISE5 = 0;
    TRISEbits.TRISE6 = 0;
    TRISEbits.TRISE7 = 0; // 30
}

void dbgOutputVal(unsigned int outVal)
{   
//    TRISBbits.TRISB11 = 0; //40
//    TRISBbits.TRISB13 = 0;
    
//    PORTBbits.RB11 = outVal & 0b1;
//    PORTBbits.RB13 = (outVal>>1) & 0b1;
    PORTBbits.RB12 = outVal & 0b1;
    PORTGbits.RG8 = (outVal>>1) & 0b1;
    PORTAbits.RA10 = (outVal>>2) & 0b1;
    if (outVal>>3 & 0b1) {
        PORTGbits.RG7 = 0b1;
    } else {
        PORTGbits.RG7 = 0b0;
    }
//    PORTFbits.RF0 = (outVal>>3) & 0b1;
    PORTFbits.RF1 = (outVal>>4) & 0b1;
    if ((outVal>>5) && 0b1){
        PORTDbits.RD6 = 1;
    } else {
        PORTDbits.RD6 = 0;
    }
//    PORTDbits.RD6 = (outVal>>5) & 0b1;
    PORTDbits.RD8 = (outVal>>6) & 0b1;
    PORTDbits.RD11 = ~PORTDbits.RD11;
    
}

//turns on channel and ports depending on the value passed include
//used by logic analyzer
void dbgOutputLoc(unsigned int outVal)
{
   PLIB_PORTS_Write (PORTS_ID_0, PORT_CHANNEL_E, outVal);
   PLIB_PORTS_PinToggle (PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_7);    
}

//output the input to a USAT terminal I.E PuTTy
void dbgUARTVal(unsigned char *outVal)
{
    PLIB_USART_Enable(USART_ID_1);
    int i = 0;
    while (outVal[i] != '\0')
    {
        while (!PLIB_USART_TransmitterIsEmpty(USART_ID_1))
        {
            
        }
        PLIB_USART_TransmitterByteSend(USART_ID_1, outVal[i]);
        i++;
    }
}

//stops all of tasks and threads
void dbgStop(unsigned int outVal)
{
    vTaskSuspendAll(); // stop task
	//DRV_ADC_Close(); // stop adc
    SYS_INT_Disable();
	
	while (1)
	{
		dbgOutputLoc(outVal);
	}
}