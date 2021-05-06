/*
 * File:   uart.h
 * Author: Paulo Pedreiras
 *
 * Created on Jan 28, 2019
 * MPLAB X IDE v5.10 + XC32 v2.15
 *
 * Target: Digilent chipKIT MAx32 board
 *
 * Overview:
 *          Set of functions to handle the UART

 * Notes: Partially based on the bootloader code from Microchip
 *
 * Revisions:
 *      2017-10-25: initial release
 *      2019-01-28: update to MPLAB X IDE v5.\0 + XC32 v2.15
 */

#ifndef __UART_H__
#define __UART_H__

#include <stdint.h>

// Define return codes
#define UART_SUCCESS 0
#define UART_FAIL -1;
#define UART_BR_NOT_SUP -2
#define UART_PBCLOCK_NOT_SUP -3

// Define prototypes (public interface)

/********************************************************************
* Function: 	UartInit()
* Precondition:
* Input: 		PB Clock and baudrate
* Returns:      UART_SUCCESS if Ok.
*               UARTX_XXX error codes in case of failure (see uart.h)
* Side Effects:	Takes control of U1A TX and RX pins
* Overview:     Initializes UART.
*
* Note:		 	Only supports 40MHz PBCLOCK, UART1A and
*               {9600/115200},8,n,1 configuration
*
********************************************************************/
int UartInit(uint64_t pbclock, uint32_t br);

/********************************************************************
* Function: 	UartClose()
* Precondition:
* Input: 		None
* Output:		None.
* Side Effects:	None.
* Overview:     Closes UART connection.
* Note:		 	No function currently
********************************************************************/
int UartClose(void);

/********************************************************************
* Function: 	GetChar()
* Precondition: UART initialized
* Input: 		None
* Output:		UART_SUCESS: If there is some data
 *              UART_FAIL: if there is no data.
* Side Effects:	None.
* Overview:     Gets the data from UART RX FIFO.
* Note:		 	None.
********************************************************************/
int GetChar(uint8_t *byte);


/********************************************************************
* Function: 	PutChar()
* Precondition:
* Input: 		None
* Output:		None
* Side Effects:	None.
* Overview:     Puts the data into UART tx reg for transmission.
* Note:		 	None.
********************************************************************/
void PutChar(uint8_t txChar);


#endif
