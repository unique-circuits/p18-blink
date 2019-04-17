/*
 * Created by :- Rohit Nimkar
 *      Blink an LED using timer generated delay
 *      Micro-Controller :- PIC18f4550 Rev 7
 *      XTAL :- 20MHz
 *      LED connected to PortD
 */


#include<pic18f4550.h>
#pragma config FOSC=HS
#pragma config PBADEN=OFF
#pragma config LVP=OFF
#pragma config WDT=OFF
void delay_ms(unsigned int);

void main(){
    TRISB = 0x00;
    INTCONbits.TMR0IE=1;
    T0CONbits.TMR0ON=0;
    while(1){
        PORTB = 0xff;
        delay_ms(1000);
        PORTB = 0x00;
        delay_ms(1000);
    }
}
void delay_ms(unsigned int ms){
    T0CON = 0x08;                   // Timer0, OFF, 16 bit without pre-scalar
    while(ms--){                   // Loop till required delay is generated
        TMR0H = 0xEC;               // Value loaded as per delay of 1mS
        TMR0L = 0x78;
        
        T0CONbits.TMR0ON = 1;       // Turn on Timer0
        while(!INTCONbits.TMR0IF);  // Checking for timer overflow flag
        INTCONbits.TMR0IF = 0;      // Turn Off timer
        T0CONbits.TMR0ON=0;         // Clear overflow flag
    }
    return;
}

