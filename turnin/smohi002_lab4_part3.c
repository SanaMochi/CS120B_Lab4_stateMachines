/*	Author: smohi002
 *  Partner(s) Name: 
 *	Lab Section:25
 *	Assignment: Lab #4  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {start, Init, wait, waitFall, waitRise, y, waitFallY, lock, waitFallLock} state;

      unsigned char tmpA;

void Tick() {
	switch(state) {
		case start:
			state = Init;
			break;
		case Init:
			PORTB = 0x00;
			state = wait;
			break;
		case wait:
			if (tmpA == 0x04) {			   state = waitFall;}
			else if (tmpA == 0x80) {		   state = lock;}
			else {					   state = wait;}
			break;
		case waitFall:
			if (tmpA == 0x00) {	 state = waitRise;}
			else {			 state = waitFall;}
			break;
		case waitRise:
			if (tmpA == 0x02) {			 state = y;}
			else if (tmpA == 0x80) {		 state = lock;}
			else if (tmpA == 0x04 || tmpA == 0x01) { state = waitFallY;}
			else {					 state = waitRise;}
			break;
		case y:
			PORTB = 0x01;
			state = waitFallY;
			break;
		case waitFallY:
			if (tmpA == 0x00) {  state = wait;}
			else {		     state = waitFallY;}
			break;
		case lock:
			PORTB = 0x00;
			state = waitFallLock;
			break;
		case waitFallLock:
			if (tmpA == 0x00) { state = wait;}
			else {		    state = waitFallLock;}
                        break;
		default:
			PORTB = 0x00;
			state = start;
			break;
	};
	switch(state) {
		case start:			break;
		case Init:			break;
		case wait:			break;
		case waitFall:			break;
		case waitRise:			break;
		case y:				break;
//			PORTB = 0x01;		break;
		case waitFallY:			break;
		case lock:			break;
//			PORTB = 0x00;		break;
		case waitFallLock:		break;
		default:			break;
	};
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; //PORTA = input
	DDRB = 0xFF; PORTB = 0x00; //PORTB = output = 0

	state = start;
    while (1) {
	tmpA = PINA;
	Tick();	
    }
//    return 1;
}
