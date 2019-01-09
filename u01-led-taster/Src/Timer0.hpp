#include "lib.h"
#include <LPC17xx.H>

#define LED1_PORT LPC_GPIO1
#define LED1_PIN 29
#define BTN1_PORT LPC_GPIO2
#define BTN1_PIN 10

#ifndef TIMER0_HPP
#define TIMER0_HPP

class Timer0 {
public:
	static Timer0* ptr;

	Timer0(unsigned int T);
	void isr();	
};

#endif
