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

enum States {start, Init, wait, waitFall, waitRise, y, waitFallY, lock, waitFallLock, waitFallFalse, waitRiseFalse, waitFallFalse2} state;

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
			else if ((tmpA == 0x02) || tmpA == 0x01) { state = waitFallFalse;}
			else {					   state = wait;}
			break;
		case waitFall:
			if (tmpA == 0x00) {	 state = waitRise;}
			else {			 state = waitFall;}
			break;
		case waitRise:
			if (tmpA == 0x02) {			 state = y;}
			else if (tmpA == 0x04 || tmpA == 0x01) { state = waitFallY;}
			else {					 state = waitRise;}
			break;
		case y:
			state = waitFallY;
			break;
		case waitFallY:
			if (tmpA == 0x00) { state = wait;}
			else {	     state = waitFallY;}
			break;
		case lock:
			state = waitFallLock;
			break;
		case waitFallLock:
			if (tmpA == 0x00) { state = wait;}
			else {		    state = waitFallLock;}
                        break;
		case waitFallFalse:
			if (tmpA == 0x00) { state = waitRiseFalse;}
			else {		    state = waitFallFalse;}
			break;
		case waitRiseFalse:
			if (tmpA == 0x04 || tmpA == 0x02 || tmpA == 0x01) { state = waitFallFalse2;}
			else {						    state = waitRiseFalse;}
			break;
		case waitFallFalse2:
			if (tmpA == 0x00) { state = wait;}
			else {		    state = waitFallFalse2;}
			break;
		default:
			PORTB = 0x00;
			state = start;
			break;
	};
	switch(state) {
		case start:		break;
		case Init:
//			PORTB = 0x00;
					break;
		case wait:		break;
		case waitFall:		break;
		case waitRise:		break;
		case y:	
			PORTB = 0x01;
					break;
		case waitFallY:		break;
		case lock:
			PORTB = 0x00;
					break;
		case waitFallLock:	break;
		case waitFallFalse:	break;
		case waitRiseFalse:	break;
		case waitFallFalse2:	break;
		default:
//			PORTB = 0x00;
					break;
	};
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; //PORTA = input
	DDRB = 0xFF; PORTB = 0x00; //PORTB = output = 0
	DDRC = 0xFF; PORTC = 0x00; //PORTC = output = 0

	state = start;
    while (1) {
	tmpA = PINA;
	Tick();	
	PORTC = state;
    }
//    return 1;
}
