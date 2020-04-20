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

enum States {start, Init, wait, waitFall, waitRise, unlock, lock, waitFallLock} state;

	unsigned char tmpA;
	unsigned char tmpB;
	unsigned char prevA = 0x00;
	unsigned char cnt = 0x00;
	unsigned char passcode[4];
	unsigned char flag = 0x00;
	unsigned char flag2 = 0x00;

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
			if (tmpA == 0x04 || tmpA == 0x02 || tmpA == 0x01) {
//				passcode[0] = tmpA;
//				cnt = 0x01;
				state = waitFall;
			}
			else if (tmpA == 0x80) {
				state = lock;
			}
			else {
				state = wait;
			}
			break;
		case waitFall:
			if (tmpA == 0x00 && cnt < 0x04) {			 state = waitRise;}
			else if (tmpA == 0x00 && cnt >= 0x04)  {		 state = unlock;}
			else {							 state = waitFall;}
			break;
		case waitRise:
			if (tmpA == 0x04 || tmpA == 0x02 || tmpA == 0x01) {
				state = waitFall;
				if (tmpA != prevA)	flag = 0x01;
			}
			else { state = waitRise; }
			break;
		case unlock:
			state = wait;
			break;
		case lock:
			state = waitFallLock;
			break;
		case waitFallLock:
			if (tmpA == 0x00) { state = wait;}
			else {		    state = waitFallLock;}
                        break;
		default:
			state = start;
			PORTB = 0x00;
			break;
	};

        switch(state) {
                case start:             	        break;
                case Init:              	        break;
                case wait:  
			if ((tmpA == 0x01 || tmpA == 0x02 || tmpA == 0x04)) {
				flag2 = 0x01;
			}				break;
                case waitFall: 
			if (flag == 0x01 && cnt < 0x04 && (tmpA == 0x01 || tmpA == 0x02 || tmpA == 0x04)) {
                                passcode[cnt] = tmpA;
                                cnt++;
				flag = 0;
                        }	    	        	break;
                case waitRise:				break;
		case unlock:
			if (flag2 == 0x01 && 
			    passcode[1] == 0x01 &&
			    passcode[2] == 0x02 &&
			    passcode[3] == 0x01 ) {
				if (tmpB == 0x00) 
					PORTB = 0x01;
                       		else 
					PORTB = 0x00;
			}				break;
		case lock:	PORTB = 0x00;		break;
		case waitFallLock:			break;
		default:				break;
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
	tmpB = PORTB;
	Tick();	
//	PORTC = state;
	prevA = tmpA;
    }
//    return 1;
}
