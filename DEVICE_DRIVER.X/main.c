/* 
 * File:   main.c
 * Author: rui_m
 *
 * Created on 4 de Maio de 2021, 18:37
 */


#include "../Common/Config/config_bits.h" // NOTE!! Must precede project file includes

#include <xc.h>
#include <sys/attribs.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Common/UART/uart.h" 

#define SYSCLK  80000000L // System clock frequency, in Hz
#define PBCLOCK 40000000L // Peripheral Bus Clock frequency, in Hz


void f1(){
    PORTAbits.RA3 = !PORTAbits.RA3;
    PutChar('T');
    Timer2ResetInterruptFlag();
}

/*
 * 
 */
int main(int argc, char** argv) {

    // Set RA3 and D5 ports
    TRISAbits.TRISA3 = 0;  // A3 as output
    TRISDbits.TRISD5 = 0; // D5 a output
    ODCDbits.ODCD5 = 1; // D5 as open-drain

    // Init UART and redirect tdin/stdot/stderr to UART
    if(UartInit(PBCLOCK, 115200) != UART_SUCCESS) {
        PORTAbits.RA3 = 1; // If Led active error initializing UART
        while(1);
    }
    __XC_UART = 1; /* Redirect stdin/stdout/stderr to UART1*/
    
    
    Timer2Config(1300000);
    Timer2setCallbackFunction(f1);
    // Loop
    while (1);
     
    return (EXIT_SUCCESS);
}


