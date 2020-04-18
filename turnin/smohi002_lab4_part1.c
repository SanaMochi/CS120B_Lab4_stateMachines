/*	Author: smohi002
 *  Partner(s) Name: 
 *	Lab Section:25
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {start, Init, waitRise1, switch1, waitFall1, waitRise2, switch2, waitFall2} state;

      unsigned char tmpA;

void Tick() {
	switch(state) {
		case start:
			state = Init;
			PORTB = 0x01;
			break;
		case Init:
			state = waitRise1;
			PORTB = 0x01;
			break;
		case waitRise1:
			if (!tmpA)
				state = waitRise1;
			else
				state = switch1;
			break;
		case switch1:
			PORTB = 0x02;
			state = waitFall1;
			break;
		case waitFall1:
			if (tmpA)
				state = waitFall1;
			else
				state = waitRise2;
			break;
		case waitRise2:
			if (!tmpA)
                                state = waitRise2;
                        else
                                state = switch2;
                        break;
		case switch2:
			PORTB = 0x01;
			state = waitFall2;
			break;
		case waitFall2:
			if (tmpA)
                                state = waitFall2;
                        else
                                state = waitRise1;
                        break;
		default:
			PORTB = 0x01;
			state = start;
			break;
	};
	switch(state) {
		case Init:	break;
		case waitRise1:	break;
		case switch1:	break;
		case waitFall1:	break;
		case waitRise2:	break;
		case switch2:	break;
		case waitFall2:	break;
		default:	break;
	};
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; //PORTA = input
	DDRB = 0xFF; PORTB = 0x00; //PORTB = output

	state = start;
    while (1) {
	tmpA = PINA;
	Tick();	

    }
//    return 1;
}
