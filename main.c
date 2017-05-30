/* 
 * File:   main.c
 * Author: Ninoslav Budimir
 *
 * Created on 16 May 2017, 11:39
 */


//#if defined(__XC)
//    #include <xc.h>         /* XC8 General Include File */
//#elif defined(HI_TECH_C)
//    #include <htc.h>        /* HiTech General Include File */
//#endif
#include <xc.h> 
#include <htc.h> 
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include <pic16lf1459.h>
#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

#include "nRF24L01P.h"
#include "spi.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection Bits (ECH, External Clock, High Power Mode (4-20 MHz): device clock supplied to CLKIN pins)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF        // Internal/External Switchover Mode (Internal/External Switchover Mode is enabled)
#pragma config FCMEN = OFF       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config CPUDIV = NOCLKDIV// CPU System Clock Selection Bit (CPU system clock divided by 6)
#pragma config USBLSCLK = 48MHz // USB Low SPeed Clock Selection bit (System clock expects 48 MHz, FS/LS USB CLKENs divide-by is set to 8.)
#pragma config PLLMULT = 3x     // PLL Multipler Selection Bit (3x Output Frequency Selected)
#pragma config PLLEN = DISABLED  // PLL Enable Bit (3x or 4x PLL Enabled)
#pragma config STVREN = OFF      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

//If the movement occured interrupt (IOC) signals from the PIR motion detector wake up MCU from sleep mode. 
//MCU send information about that event through the RF module to the Arduino provider and going to sleep again.

void main(void)
{

    /* Configure the oscillator for the device */
    ConfigureOscillator();
    __delay_ms(1000);
    /* Turn off analog function for port A,B,C */
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    // i tak ti ja napi?em komentar
    TRISCbits.TRISC5 = 0;           //RED LED output
    LATCbits.LATC5 = 0;             //RED LED off
    
    IOCBFbits.IOCBF7 = 0;           // clear IOC flag
    INTCONbits.IOCIF = 0;           // clear interrupt flag
    IOCBPbits.IOCBP7 = 1;           // edge select, positive edge
    INTCONbits.IOCIE = 1;           // Enable interrupt on change
   
    INTCONbits.PEIE = 1;            // Enable Peripheral Interrupts
    INTCONbits.GIE  = 1;            // Enable Global interrupt
  
    __delay_ms(10);
    
        uint8_t data[2]={0,0};                  //data to send via RF module
        CE = 0;                                 // chip enable = 0
        SPI_init();                             // SPI initialization
        nRF_Setup();                            // Set RF module
        FlushTXRX();                            // Flush TX/RX register
        WriteRegister(NRF_STATUS,0x70);         // Reset status register
        __delay_ms(2);
        CE = 1;                                 // chip enable = 1      
        WritePayload(2, data);                  //send data
        __delay_us(202);                        // 130 us + Ttransmit = 72 us
         FlushTXRX();                            // Flush TX/RX register
        
    
        if (flag == 1) 
        {                                       //if interrupt occured
        LATCbits.LATC5 = 1;                     //toggle LED 
        __delay_ms(1000);
        LATCbits.LATC5= 0;
       __delay_ms(1000);
        flag = 0;
        }
       
        InitApp();                              //Sleep mode setup for minimum power consumption
        SLEEP();                                //go sleep
        //After sleep mode program goes from the beginning
        
 }
    
    
  
