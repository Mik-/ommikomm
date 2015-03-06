/*
 (C) 2015 by Michael Neuendorf <michael@neuendorf-online.de>

 This file is part of OmmiKomm.

 OmmiKomm is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 OmmiKomm is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with OmmiKomm.  If not, see <http://www.gnu.org/licenses/>.

 Diese Datei ist Teil von OmmiKomm.

 OmmiKomm ist Freie Software: Sie können es unter den Bedingungen
 der GNU General Public License, wie von der Free Software Foundation,
 Version 3 der Lizenz oder (nach Ihrer Wahl) jeder späteren
 veröffentlichten Version, weiterverbreiten und/oder modifizieren.

 OmmiKomm wird in der Hoffnung, dass es nützlich sein wird, aber
 OHNE JEDE GEWÄHELEISTUNG, bereitgestellt; sogar ohne die implizite
 Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
 Siehe die GNU General Public License für weitere Details.

 Sie sollten eine Kopie der GNU General Public License zusammen mit OmmiKomm
 erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
 */

#include "PINInputState.h"

#include <FL/Fl_Input_.H>
#include <FL/Fl_Multiline_Input.H>

PINInputState::PINInputState(ICommands *Commands, IPINResult *PINResult,
		std::string caption) {
	this->Commands = Commands;
	this->PINResult = PINResult;
	this->caption = caption;
}

PINInputState::~PINInputState() {
}

int PINInputState::handleKey(int key) {
	// Allow only the keys "0" to "9"
	if (key >= (int) '0' & key <= (int) '9') {
		enteredPIN << (char) key; // append the current key to the entered PIN var

		// Display a asterisk instead of the digit
		std::stringstream value;
		value << Commands->getInput()->value() << "*";
		Commands->getInput()->value(value.str().c_str());

		// If 4 digits were entered, call the "PIN entered" method, which was
		// handed to the constructor
		if (enteredPIN.str().length() >= 4) {
			PINResult->enteredPIN(enteredPIN.str());
		}
	}

	return 1;
}

void PINInputState::enterState(void) {
	enteredPIN.clear();

	std::ostringstream menuText;

	Commands->setTextLines(5);
	Commands->clear_all();

	menuText << "\n\n" << caption.c_str() << ": ";

	Commands->getInput()->value(menuText.str().c_str());
}

void PINInputState::tick(void) {
	// No actions, depending on time, in this state
}
