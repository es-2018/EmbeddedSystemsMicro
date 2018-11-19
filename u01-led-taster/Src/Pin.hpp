#include "lib.h"
#include <LPC17xx.H>

#ifndef PIN_HPP
#define PIN_HPP

class Pin {
private:
	LPC_GPIO_TypeDef* port;	
	int pin;

protected:
	bool isOut;
	bool alterZustand;

public:
	Pin(bool isOut);
	
	virtual void an() = 0;
	virtual void aus() = 0;
	virtual bool lesen() = 0;
	
	bool isOutput();
	
	void toggle();
	bool steigendeFlanke();
	bool fallendeFlanke();
};
#endif
