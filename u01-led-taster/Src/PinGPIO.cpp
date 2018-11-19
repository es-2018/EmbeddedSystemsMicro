#include "PinGPIO.hpp"

PinGPIO::PinGPIO(LPC_GPIO_TypeDef* port, int pin, bool isOut)
: Pin(isOut) {
	this->port = port;
	this->pin = pin;
	
	if (this->isOut) {
		// Setze Pin als Output (1 an Stelle <pin> schreiben)
		this->port->FIODIR |= (1 << pin);
	} else {
		// Setze Pin als Input (0 an Stelle <pin> schreiben)
		this->port->FIODIR &= ~(1 << pin);
		alterZustand = lesen();
	}
}

void PinGPIO::an() {
	// Pin auf HIGH setzen (schreibe 1 an Stelle <pin> in FIOSET)
	port->FIOSET = (1 << pin);
}

void PinGPIO::aus() {
	// Pin auf LOW setzen (schreibe 1 an Stelle <pin> in FIOCLR)
	port->FIOCLR = (1 << pin);
}

bool PinGPIO::lesen() {
	// FIOPin-Register auslesen
	return port->FIOPIN & (1 << pin);
}
