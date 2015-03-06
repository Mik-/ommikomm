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

#include <string>
#include <libintl.h>
#include "OmmiKomm.h"
#include "TypingState.h"
#include "PINInputState.h"

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

	if (key == FL_F + 1) {
		Commands->setNewState(Commands->getHelpState());
		return (1);
	}
	if (key == FL_F + 10) {
		if (Settings->getPIN().empty()) {
			Commands->setNewState(Commands->getConfigState());
		} else {
			std::string caption = "Enter PIN";
			pinInputState =  new PINInputState(Commands, this, caption);
			Commands->setNewState(pinInputState);
		}

		return (1);
	}
	if (key == FL_Escape or key == FL_F + 5) {
		Commands->clear_all();
		return (1);
	}
	if (key == FL_F + 12) {
		Commands->setNewState(Commands->getRestartState());
		return (1);
	}

	return (0);
}

void TypingState::enterState(void) {
	ticks = 0;
	Commands->setTextLines(lines);
}

void TypingState::tick(void) {
	ticks++;
    if (ticks >= idleUntilHelpScreen) {
        Commands->setNewState(Commands->getHelpState());
    }
}

void TypingState::enteredPIN(std::string PIN) {
	delete pinInputState;

	if (PIN == Settings->getPIN()) {
		Commands->setNewState(Commands->getConfigState());
	} else {
	    Commands->setNewState(Commands->getTypingState());

	    std::ostringstream menuText;

	    Commands->clear_all();

	    menuText << _("Wrong PIN!");
	    Commands->getInput()->value(menuText.str().c_str());
	}
}
