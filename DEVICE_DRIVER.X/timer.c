/* 
 * File:   timer.c
 * Author: rui_m
 *
 * Created on 28 de Abril de 2021, 3:42
 */

#include <xc.h>
#include <sys/attribs.h>
#include <stdio.h>
#include "timer.h"

#define PBCLOCK 40000000L

void (*fp)(void);

int8_t Timer2Config(uint32_t period_us){
    uint16_t prescaler[8] = {1,2,4,8,16,32,64,256};
    uint8_t i;
	int8_t retval = -1;
    float fout;
    fout = 1000000/(period_us);
    
    for (i = 0; i < 8; i++) {
		if((((PBCLOCK/prescaler[i])/fout)-1) <= 65535) {
			retval = i;
            break;
		}else{
            retval = 7;
        }
	}
    Timer2Stop();
    Timer2ResetInterruptFlag();
    IPC2bits.T2IP=5; //set interrupt priority (1..7) *** Make sure it matches iplx in isr declaration ***
    Timer2InterruptConfig(1);
    // Timer period configuration
    T2CONbits.TCKPS = retval; //Divide by 256 pre-scaler
    T2CONbits.T32 = 0; // 16 bit timer operation
    PR2 = ((PBCLOCK/prescaler[retval])/fout)-1;
    TMR2=0;
    
    Timer2Start();
}

void Timer2InterruptConfig(uint8_t interrupt_enable){
    IEC0bits.T2IE = 1; // Enable T2 interrupts
    INTCONSET = _INTCON_MVEC_MASK;
    __builtin_enable_interrupts();
}

uint8_t Timer2ReadInterruptFlag(){
    return IFS0bits.T2IF;
}

void Timer2ResetInterruptFlag(){
        IFS0bits.T2IF=0; // Reset interrupt flag
}

void Timer2Start(){
    T2CONbits.TON=1; // Start the timer
}

void Timer2Stop(){
    T2CONbits.ON = 0; // Stop timer
}

void Timer2setCallbackFunction(void(*function)(void)){
    fp = function;
}

void __ISR(_TIMER_2_VECTOR, IPL5SRS) T2Interrupt(void){
    if (fp == NULL){
        fprintf(stderr,"Error: fp not set. Points to null");
        exit(-1);
    }
    else{
       (*fp)(); 
    }
}
