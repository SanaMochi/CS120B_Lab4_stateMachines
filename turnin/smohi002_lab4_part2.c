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

enum States {Start, Init, WaitRise1, Switch1, WaitFall1, WaitRise2, Switch2, WaitFall2} state;

      unsigned char tmpA = 0x00;
//      unsigned char tmpB = 0x00;

void Tick() {
	switch(state) {
		case Start:
			state = Init;
			break;
		case Init:
			state = WaitRise1;
			PORTB = 0x01;
			break;
		case WaitRise1:
			if (!tmpA)
				state = WaitRise1;
			else
				state = Switch1;
			break;
		case Switch1:
			PORTB = 0x02;
			state = WaitFall1;
			break;
		case WaitFall1:
			if (tmpA)
				state = WaitFall1;
			else
				state = WaitRise2;
			break;
		case WaitRise2:
			if (!tmpA)
                                state = WaitRise2;
                        else
                                state = Switch2;
                        break;
		case Switch2:
			PORTB = 0x01;
			state = WaitFall2;
			break;
		case WaitFall2:
			if (tmpA)
                                state = WaitFall2;
                        else
                                state = WaitRise1;
                        break;
		default:
			PORTB = 0x01;
			state = Start;
			break;
	}
	switch(state) {
		case Init:
		case WaitRise1:
		case Switch1:
		case WaitFall1:
		case WaitRise2:
		case Switch2:
		case WaitFall2:
			break;
		default:
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; //PORTA = input
	DDRB = 0xFF; PORTB = 0x00; //PORTB = output
    /* Insert your solution below */

//	unsigned char tmpA = 0x00;
//	unsigned char tpmB = 0x00;
	state = Start;
	PORTB = 0x00;
    while (1) {
	tmpA = PINA;
	Tick();	

    }
    return 1;
}
