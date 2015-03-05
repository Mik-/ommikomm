/*
 * PINInputState.cpp
 *
 *  Created on: 05.03.2015
 *      Author: michael
 */

#include <libintl.h>
#include <sstream>

#include "OmmiKomm.h"
#include "PINInputState.h"

PINInputState::PINInputState(ICommands* Commands, ISettings* Config, IState *PINOkState,
		IState *PINWrongState) {
	this->Commands = Commands;
	this->Config = Config;
	this->PINOkState = PINOkState;
	this->PINWrongState = PINWrongState;
}

PINInputState::~PINInputState() {
}

int PINInputState::handleKey(int key) {
	if (key >= (int)'0' & key <= (int)'9') {
		enteredPIN << (char)key;

		std::stringstream value;
		value << Commands->getInput()->value() << "*";
		Commands->getInput()->value(value.str().c_str());

		if (enteredPIN.str().length() >= 4) {
			if (enteredPIN.str() == Config->getPIN()) {
				Commands->setNewState(this->PINOkState);
			} else {
				Commands->setNewState(this->PINWrongState);
			}
		}

		return 1;
	}

	return 0;
}

void PINInputState::enterState(void) {
	enteredPIN.clear();

    std::ostringstream menuText;

    Commands->setTextLines(5);
    Commands->clear_all();

    menuText << "\n\n" << _("Enter PIN") << ": ";

    Commands->getInput()->value(menuText.str().c_str());
}

std::string PINInputState::getEnteredPIN() {
	return this->enteredPIN.str();
}

void PINInputState::tick(void) {
}
