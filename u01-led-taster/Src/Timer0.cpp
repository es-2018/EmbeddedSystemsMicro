#include "Timer0.hpp"
#include "PinGPIO.hpp"

Timer0* Timer0::ptr = NULL;

Timer0::Timer0(unsigned int T){
	// Erklärung der Register und gute grafische Übersicht: siehe Vorlesung S. 26.
	
	// CTCR: Auswahl zwischen Timer Mode und Counter Mode (Timer Mode: Inkrementiere den
	//  Timer Conter (TC), wenn der Prescale Counter mit dem Wert im Prescale-Register
	//  übereinstimmt. Der Prescale-Counter wird mit jeder steigenden Flanke des Prozessor-
	//  Takts PCLK inkrementiert. (Datenblatt, S. 494)
	LPC_TIM0->CTCR = 0; // Timer Mode
	
	// PR: Setze das Prescale-Register (Maximalwert des Prescale Counter). (Datenblatt, S. 495)
	//  Da der Prozessor einen Takt von 25 MHz hat, setze den Prescaler auf
	//  25000. Dann sollte der Prescale Counter 1000 Mal pro Sekunde
	//  (d.h. 1 Mal pro Millisekunde) "voll sein" und den Timer Counter
	//  inkrementieren. Zusätzlich müssen wir noch 1 abziehen, weil diese Zeit
	//  zum Triggern (des TC?) benötigt wird.
	//  Diese Wahl des PR ist nützlich, weil man den Compare-Wert in MR0 dann
	//  einfach in Millisekunden angeben kann.
	LPC_TIM0->PR = 25000 - 1; // PCLK = 25 MHz, trigger = 1 kHz
	
	// MR0: Setze das Compare-Register (auch: Match-Register, daher MR0) (Datenblatt, S. 496)
	//  Wie oben beschrieben wurde das Prescale-Register so gewählt, dass hier einfach
	//  die Zeit das Timer-Intervall in Millisekunden angegeben werden kann.
	//  Auch hier wird wieder 1 abgezogen -- Vermutung: Ebenfalls eine Trigger-Verzögerung?
	LPC_TIM0->MR0 = T - 1; // T in ms
	
	// MCR: Setze das MCR-Register, das angibt, was bei einem Match (Counter == Compare-Register)
	//  passieren soll. Wir möchten bei einem Match einen Interrupt erzeugen (LSB = 0. Bit = 1), den Counter
	//  zurückseten (1. Bit = 1), den Timer aber nicht stoppen (2. Bit = 0)
	LPC_TIM0->MCR |= (1<<0) // enable interrupt
									|(1<<1) // reset on match
									|(0<<2); // stop on match
									
	// TCR: Timer aktivieren (LSB des Timer Control Register auf 1 setzen)
	LPC_TIM0->TCR |= (1<<0); // enable timer
	
	// Timer Interupt aktivieren
	NVIC_EnableIRQ( TIMER0_IRQn ); // enable timer interrupt

	ptr = this;
}

void Timer0::isr() {
	PinGPIO led1 = PinGPIO(LED1_PORT, LED1_PIN, true);
	led1.toggle();
}
