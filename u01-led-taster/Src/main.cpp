//*******************************************************************
#include "lib.h"
#include "config.h"
#include <LPC17xx.H>
#include "Pin.hpp"
#include "PinGPIO.hpp"
#include "Timer0.cpp"

#define LED1_PORT LPC_GPIO1
#define LED1_PIN 29
#define BTN1_PORT LPC_GPIO2
#define BTN1_PIN 10
//*******************************************************************

PinGPIO* led = NULL;

// Interrupt-Handler müssen als C-Funktionen deklariert werden
extern "C" {
	void EINT0_IRQHandler(void);
}

extern "C" {
	void TIMER0_IRQHandler(void) {
		LPC_TIM0->IR = LPC_TIM0->IR;
		Timer0::ptr->isr();
	}
}

// Interrupt Service Routine für EINT0
void EINT0_IRQHandler(void) {
	// Clear Interrupt Flag
	LPC_SC->EXTINT = (1 << 0);
	
	// Toggle LED
	if (led) {
		led->toggle();
	}
}

int main(void) {
	Timer0 t0 (30);
	
	
//	PinGPIO led1 = PinGPIO(LED1_PORT, LED1_PIN, true);
//	led = &led1;
//	
//	// Pin 2.10 als Interrupt-Quelle (EINT0) einrichten
//	// -> Setze 20. Bit von PINSEL4 auf 1
//	LPC_PINCON->PINSEL4 |= (1 << 20);

//	// Setze EINT0 flankengesteuert (statt level-gesteuert)
//	// -> Setze 1. Bit von EXTMODE auf 1
//	LPC_SC->EXTMODE |= (1 << 0);
//		
//	// EINT0 soll auf steigende Flanke reagieren
//	// -> Setze 1. Bit von EXTPOLAR auf 1
//	LPC_SC->EXTPOLAR |= (1 << 0);
//	
//	// EINT0 soll auf fallende Flanke reagieren
//	// -> Setze 1. Bit von EXTPOLAR auf 0
//	//LPC_SC->EXTPOLAR &= ~(1 << 0);

//	// External Interrupt 0 aktivieren
//	NVIC_EnableIRQ(EINT0_IRQn);	
//	
	while(1) {	}
}
//EOF
