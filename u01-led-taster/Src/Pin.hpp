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
	Pin(bool isOut) {
		this->isOut = isOut;
	}
	
	virtual void an() = 0;
	
	virtual void aus() = 0;
	
	void toggle() {
		if (isOutput()) {
			if (lesen()) {
				aus();
			} else {
				an();
			}
		}
	}
	
	virtual bool lesen() = 0;
	
	bool isOutput() {
		return isOut;
	}
	
	bool steigendeFlanke() {
		int zustand = lesen();
		bool ret = false;
		if (zustand && zustand != alterZustand) {
			ret = true;
		}
		alterZustand = zustand;
		return ret;
	}
	
	bool fallendeFlanke() {
		int zustand = lesen();
		bool ret = false;
		if (!zustand && zustand != alterZustand) {
			ret = true;
		}
		alterZustand = zustand;
		return ret;
	}
};
#endif
