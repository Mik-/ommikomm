/*
 (C) 2014 by Michael Neuendorf <michael@neuendorf-online.de>

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

#include "TypingState.h"

#include <FL/Enumerations.H>
#include <FL/Fl_Multiline_Input.H>
#include <sstream>

#include "OmmiKomm.h"

TypingState::TypingState(ICommands *Commands, int lines,
		int idleUntilHelpScreen, ISettings *Settings) {
	this->Commands = Commands;
	this->lines = lines;
	this->idleUntilHelpScreen = idleUntilHelpScreen;
	this->Settings = Settings;
}

TypingState::~TypingState() {
	//dtor
}

void TypingState::setLines(int lines) {
	this->lines = lines;
}

int TypingState::handleKey(int key) {
	ticks = 0;

	// on key F1, enter the help state
	if (key == FL_F + 1) {
		Commands->setNewState(Commands->getHelpState());
		return (1);
	}
	// on key F10, enter the settings state, if now PIN is set
	// if a PIN is set, create a new PIN input state and register "this" as
	// callback interface, to receive the result of the input
	if (key == FL_F + 10) {
		if (Settings->getPIN().empty()) {
			Commands->setNewState(Commands->getConfigState());
		} else {
			std::string caption = _("Enter PIN");
			pinInputState = new PINInputState(Commands, this, caption);
			Commands->setNewState(pinInputState);
		}

		return (1);
	}
	// on key ESCAPE or F5, clear the current text
	if (key == FL_Escape or key == FL_F + 5) {
		Commands->clear_all();
		return (1);
	}
	// on key F12, enter the restart state
	if (key == FL_F + 12) {
		Commands->setNewState(Commands->getRestartState());
		return (1);
	}

	return (0);
}

// if this state entered, set the line count, which also clears the input
void TypingState::enterState(void) {
	ticks = 0;
	Commands->setTextLines(lines);
}

// handle the ticks, to enter the help state after the given time
void TypingState::tick(void) {
	ticks++;
	if (ticks >= idleUntilHelpScreen) {
		Commands->setNewState(Commands->getHelpState());
	}
}

// handle the PIN result, which is gathered by the PIN input state
void TypingState::enteredPIN(std::string PIN) {
	// delete the class, which was created in the handle key method
	delete pinInputState;

	// compared the entered PIN with the PIN in the settings
	if (PIN == Settings->getPIN()) {
		// PIN is equal, change to settings state
		Commands->setNewState(Commands->getConfigState());
	} else {
		// PIN is wrong, change to typing state and show an error message
		Commands->setNewState(Commands->getTypingState());

		std::ostringstream menuText;

		Commands->clear_all();

		menuText << _("Wrong PIN!");
		Commands->getInput()->value(menuText.str().c_str());
	}
}
