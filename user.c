/******************************************************************************/
/* Files to Include                                                           */
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
/* User Functions                                                             */
/******************************************************************************/

void InitApp(void)
{

   //disable analog functions
   ANSELA = 0x00;
   ANSELB = 0x00;
   ANSELC = 0x00;

   TRISCbits.TRISC0 = 0; //ICSPDAT output
   TRISCbits.TRISC1 = 0; //ICSPCLK output
   TRISCbits.TRISC2 = 0; //AN0 output
   TRISCbits.TRISC3 = 0; //AN1 output
   TRISCbits.TRISC4 = 0; //Green led output
   TRISCbits.TRISC5 = 0; //Red led output
   TRISCbits.TRISC6 = 0; //CSN output
   TRISCbits.TRISC7 = 0; //SDO output

   TRISAbits.TRISA4 = 0; //CE output
   TRISAbits.TRISA5 = 0; //IRQ output

   TRISBbits.TRISB4 = 1; //SDI input
   TRISBbits.TRISB5 = 1; //IOC input
   TRISBbits.TRISB6 = 0; //clock output
   TRISBbits.TRISB7 = 1; //IOC input

   LATCbits.LATC0 = 0;
   LATCbits.LATC1 = 0;
   LATCbits.LATC2 = 0;
   LATCbits.LATC3 = 0;
   LATCbits.LATC4 = 0;
   LATCbits.LATC5 = 0;
   LATCbits.LATC6 = 0;
   LATCbits.LATC7 = 0;

   LATAbits.LATA4 = 0;
   LATAbits.LATA5 = 0;

   LATBbits.LATB6 = 0;

}

