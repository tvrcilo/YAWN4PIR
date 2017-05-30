/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

#define SLEEP()     asm("sleep")
#define GREENLED    LATCbits.LATC4
#define REDLED      LATCbits.LATC5
#define CSN         LATCbits.LATC6
#define CE          LATAbits.LATA4
#define IRQ         LATAbits.LATA5
#define SDI         LATBbits.LATB4
#define SCK         LATBbits.LATB6



/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */
void InitApp(void);         /* I/O and Peripheral Initialization */
void interrupt isr(void);
/******************************************************************************/
/* Global Variables                                            */
/******************************************************************************/
