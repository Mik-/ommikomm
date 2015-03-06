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

#include "HelpState.h"

#include <FL/Fl_Multiline_Input.H>
#include <sstream>
#include <string>

#include "../config.h"
#include "../OmmiKomm.h"

HelpState::HelpState(ICommands *Commands, int waitForAutoClose) {
	this->Commands = Commands;
	this->waitForAutoClose = waitForAutoClose;
	this->ticks = 0;
}

HelpState::~HelpState() {
	//dtor
}

int HelpState::handleKey(int key) {
	// Switch to typing state on any key
	Commands->setNewState(this->Commands->getTypingState());
	return (1);
}

void HelpState::enterState(void) {
	std::ostringstream helpText;

	ticks = 0;
	Commands->setTextLines(9);

	helpText << "OmmiKomm " << VERSION << "\n";
	helpText << "(c) " << COPYRIGHTYEAR << " Michael Neuendorf\n\n";
	helpText << "ESC - " << _("Clear input") << "\n";
	helpText << "F1  - " << _("This help screen") << "\n";
	helpText << "F10 - " << _("Setup") << "\n";
	helpText << "F12 - " << _("Restart OmmiKomm") << "\n";
	helpText << "\n" << _("Press space bar to go back");

	Commands->getInput()->value(helpText.str().c_str());
}

// Handle ticks, to close the help screen after the desired time
void HelpState::tick(void) {
	ticks++;

	if (ticks >= waitForAutoClose) {
		Commands->setNewState(this->Commands->getTypingState());
	}
}
