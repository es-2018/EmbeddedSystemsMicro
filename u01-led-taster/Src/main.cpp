//*******************************************************************
#include "lib.h"
#include "config.h"
#include <LPC17xx.H>

#define LED1_PORT LPC_GPIO1
#define LED1_PIN 28
#define BTN1_PORT LPC_GPIO2
#define BTN1_PIN 10
//*******************************************************************

class Pin {
public:
	LPC_GPIO_TypeDef* PORT;	
	int PIN;
  bool ISOUT;
	bool alterZustand;

	Pin(LPC_GPIO_TypeDef* port, int pin, bool isOut) {
		PORT = port;
		PIN = pin;
		ISOUT = isOut;
		
		if (isOut) {
			// Setze Pin als Output (1 an Stelle <pin> schreiben)
			port->FIODIR |= (1 << pin);
		} else {
			// Setze Pin als Input (0 an Stelle <pin> schreiben)
			port->FIODIR &= ~(1 << pin);
		}
	}

	void an() {
		// Pin auf HIGH setzen (schreibe 1 an Stelle <pin> in FIOSET)
		PORT->FIOSET = (1 << PIN);
	}
	
	void aus() {
		// Pin auf LOW setzen (schreibe 1 an Stelle <pin> in FIOCLR)
		PORT->FIOCLR = (1 << PIN);
	}
	
	bool lesen() {
		// Frage: Warum nicht: return PORT->FIOPIN & (1 << PIN); ?
		return PORT->FIOSET & (1 << PIN);
	}
};


int main(void) {
	Pin led1 = Pin(LED1_PORT, LED1_PIN, true);
	Pin btn1 = Pin(BTN1_PORT, BTN1_PIN, false);
	
	while(1) {
		if (btn1.lesen()) {
			led1.an();
		} else {
			led1.aus();
		}
	}
}
//EOF
