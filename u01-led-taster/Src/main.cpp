//*******************************************************************
//#include "lib.h"
//#include "config.h"
#include <LPC17xx.H>

#define LED1_PIN 28
//*******************************************************************

class Pin {
public:
	int PIN;
	LPC_GPIO_TypeDef* PORT;
	bool alterZustand;

	Pin(LPC_GPIO_TypeDef* PORT, int PIN, bool isOut) {
		// ... init ...
	}

	//void init(bool isOut) {}


	//void an/_aus()
	//bool lesen(...)

};


int main(void)
{
	Pin led1;
	
	// Setze GPIO1, Pin 28 Output (1 an Stelle 28 schreiben) (LED)
	LPC_GPIO1->FIODIR |= (1 << 28);
	// Setze GPIO2, Pin 10 Input (0 an Stelle 10 schreiben) (Taster)
	LPC_GPIO2->FIODIR &= ~(1 << 10);
	
	
	while( 1 )
	{
		// Falls GPIO2, Pin 10 == 1 (d.h. Taster gedrückt)
  		// (Frage: Warum geht hier nicht FIOPIN statt FIOSET?)
		if (LPC_GPIO2->FIOPIN & (1 << 10)) {
			// Schreibe 1 in GPIO1, Pin 28 (LED an)
			LPC_GPIO1->FIOSET = (1 << 28);
		} else {
			// Schreibe 0 in GPIO1, Pin 28 (LED aus)
			// LPC_GPIO1->FIOSET &= ~(1 << 28);
			LPC_GPIO1->FIOCLR = 1 << 28;
		}
	}
}

//EOF
