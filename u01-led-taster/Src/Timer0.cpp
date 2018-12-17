#include "lib.h"
#include <LPC17xx.H>

#define LED1_PORT LPC_GPIO1
#define LED1_PIN 29
#define BTN1_PORT LPC_GPIO2
#define BTN1_PIN 10


#ifndef TIEMR0_HPP
#define TIMER0_HPP

class Timer0 {
private:
	
protected:
	
public:
	static Timer0* ptr;

	Timer0(unsigned int T){
		// LPC_SC->PCLKSEL0 |= (2 << 1);
		// LPC_SC->PCLKSEL0 |= (3 << 1);
		LPC_TIM0->CTCR = 0; // timer mode
		LPC_TIM0->PR = 25000 - 1; // PCLK = 25 MHz, trigger = 1 kHz
		LPC_TIM0->MR0 = T - 1; // T in ms
		LPC_TIM0->MCR |= (1<<0) // enable interrupt
										|(1<<1) // reset on match
										|(0<<2); // stop on match
		LPC_TIM0->TCR |= (1<<0); // enable timer
		NVIC_EnableIRQ( TIMER0_IRQn ); // enable timer interrupt

		ptr = this;
	}
	
	void isr() {
		PinGPIO led1 = PinGPIO(LED1_PORT, LED1_PIN, true);
		led1.toggle();
	}
	
	
	
	
};

Timer0* Timer0::ptr = NULL;

#endif
