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



//class PinGPIO : public Pin {
//public:
	
//};


int main(void) {
	PinGPIO led1 = PinGPIO(LED1_PORT, LED1_PIN, true);
	PinGPIO btn1 = PinGPIO(BTN1_PORT, BTN1_PIN, false);
	
	while(1) {
		if (btn1.fallendeFlanke()) {
			led1.toggle();
		}
	}
}
//EOF
