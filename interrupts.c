/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include "user.h"

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* Baseline devices don't have interrupts. Note that some PIC16's 
 * are baseline devices.  Unfortunately the baseline detection macro is 
 * _PIC12 */

void interrupt isr(void)
{
    /* This code stub shows general interrupt handling.  Note that these
    conditional statements are not handled within 3 seperate if blocks.
    Do not use a seperate if block for each interrupt flag to avoid run
    time errors. */

    
    /* TODO Add interrupt routine code here. */

    /* Determine which flag generated the interrupt */
    if(INTCONbits.IOCIF)
    {
                 
        if (IOCBFbits.IOCBF7)           //RB7 interrupt on change
        {
            flag = 1;                   //for LED
            
            IOCBFbits.IOCBF7 = 0;       // reset interrupt flag
              
        }       
        if(IOCBFbits.IOCBF5)            //RB5 interrupt on change
        {
            flag = 1;
            IOCBFbits.IOCBF5 = 0;     //reset interrupt flag
        }
        
    }
}

