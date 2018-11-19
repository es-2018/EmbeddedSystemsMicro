#include "lib.h"
#include <LPC17xx.H>
#include "Pin.hpp"

#ifndef PINGPIO_HPP
#define PINGPIO_HPP


class PinGPIO : public Pin {
private:
	LPC_GPIO_TypeDef* port;	
	int pin;

public:
	PinGPIO(LPC_GPIO_TypeDef* port, int pin, bool isOut);

	virtual void an();
	virtual void aus();
	virtual bool lesen();
};
#endif
