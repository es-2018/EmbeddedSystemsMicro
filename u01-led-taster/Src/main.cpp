//*******************************************************************
#include "lib.h"
#include "config.h"
#include <LPC17xx.H>
#include "Pin.hpp"
#include "PinGPIO.hpp"

#define LED1_PORT LPC_GPIO1
#define LED1_PIN 29
#define BTN1_PORT LPC_GPIO2
#define BTN1_PIN 10
//*******************************************************************

extern "C" {
	void EINT0_IRQHandler(void) {
		// Clear Interrupt Flag
		LPC_SC->EXTINT = (1 << 0);
		PinGPIO led1 = PinGPIO(LED1_PORT, LED1_PIN, true);
		led1.toggle();
	}
}
int main(void) {
	PinGPIO led1 = PinGPIO(LED1_PORT, LED1_PIN, true);
		
	// Pin 2.10 als Interrupt-Quelle einrichten
	LPC_PINCON->PINSEL4 |= (0x01 << 20);

	// TODO: Interrupt triggert bei fallender Flanke und danach,
	// bis zur nächsten steigenden Flanke!
	
	// Interrupt 2.10 auf fallende Flanke setzen
	LPC_GPIOINT->IO2IntEnF |= (1 << 10);
	// Interrupt 2.10 auf steigende Flanke setzen
	//LPC_GPIOINT->IO2IntEnR |= (1 << 10);

	// External Interrupt 0 aktivieren
	NVIC_EnableIRQ(EINT0_IRQn);	
	
	while(1){}
	
	//	PinGPIO led1 = PinGPIO(LED1_PORT, LED1_PIN, true);
	//	PinGPIO btn1 = PinGPIO(BTN1_PORT, BTN1_PIN, false);
	//	
	//	while(1) {
	//		if (btn1.steigendeFlanke()) {
	//			led1.toggle();
	//		}
	//	}	
}
//EOF
