#include "Pin.hpp"

Pin::Pin(bool isOut) {
	this->isOut = isOut;
}

void Pin::toggle() {
	if (isOutput()) {
		if (lesen()) {
			aus();
		} else {
			an();
		}
	}
}

bool Pin::isOutput() {
	return isOut;
}

bool Pin::steigendeFlanke() {
	int zustand = lesen();
	bool ret = false;
	if (zustand && zustand != alterZustand) {
		ret = true;
	}
	alterZustand = zustand;
	return ret;
}

bool Pin::fallendeFlanke() {
	int zustand = lesen();
	bool ret = false;
	if (!zustand && zustand != alterZustand) {
		ret = true;
	}
	alterZustand = zustand;
	return ret;
}
