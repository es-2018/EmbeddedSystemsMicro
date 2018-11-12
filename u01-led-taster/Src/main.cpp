//*******************************************************************
#include "lib.h"
#include "config.h"
#include <LPC17xx.H>

#define LED1_PORT LPC_GPIO1
#define LED1_PIN 29
#define BTN1_PORT LPC_GPIO2
#define BTN1_PIN 10
//*******************************************************************

class Pin {
private:
	LPC_GPIO_TypeDef* port;	
	int pin;
	bool isOut;
	bool alterZustand;

public:
	Pin(LPC_GPIO_TypeDef* port, int pin, bool isOut) {
		this->port = port;
		this->pin = pin;
		this->isOut = isOut;
		
		if (this->isOut) {
			// Setze Pin als Output (1 an Stelle <pin> schreiben)
			this->port->FIODIR |= (1 << pin);
		} else {
			// Setze Pin als Input (0 an Stelle <pin> schreiben)
			this->port->FIODIR &= ~(1 << pin);
		}
	}

	void an() {
		// Pin auf HIGH setzen (schreibe 1 an Stelle <pin> in FIOSET)
		port->FIOSET = (1 << pin);
	}
	
	void aus() {
		// Pin auf LOW setzen (schreibe 1 an Stelle <pin> in FIOCLR)
		port->FIOCLR = (1 << pin);
	}
	
	void toggle() {
		if (isOutput()) {
			if (lesen()) {
				aus();
			}else {
				an();
			}
		}
	}
	
	bool lesen() {
		// FIOPin-Register auslesen
		return port->FIOPIN & (1 << pin);
	}
	
	bool isOutput() {
		return isOut;
	}
};

int main(void) {
	Pin led1 = Pin(LED1_PORT, LED1_PIN, true);
	Pin btn1 = Pin(BTN1_PORT, BTN1_PIN, false);
	
	int previousButtonState = -1;
	
	while(1) {
		int buttonState = btn1.lesen();
		if (buttonState && buttonState != previousButtonState) {
			led1.toggle();
		}
		previousButtonState = buttonState;
	}
}
//EOF
