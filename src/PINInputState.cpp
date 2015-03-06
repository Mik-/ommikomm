/*
 * PINInputState.cpp
 *
 *  Created on: 05.03.2015
 *      Author: michael
 */

#include <libintl.h>
#include <string>
#include <sstream>

#include "OmmiKomm.h"
#include "IPINResult.h"
#include "PINInputState.h"

PINInputState::PINInputState(ICommands *Commands, IPINResult *PINResult, std::string caption) {
	this->Commands = Commands;
	this->PINResult = PINResult;
	this->caption = caption;
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
			PINResult->enteredPIN(enteredPIN.str());
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

    menuText << "\n\n" << _(caption.c_str()) << ": ";

    Commands->getInput()->value(menuText.str().c_str());
}

std::string PINInputState::getEnteredPIN() {
	return this->enteredPIN.str();
}

void PINInputState::tick(void) {
}
