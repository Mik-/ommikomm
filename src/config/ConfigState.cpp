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

#include <libintl.h>
#include <sstream>

#include "../AutopoweroffState.h"
#include "../OmmiKomm.h"
#include "ConfigState.h"
#include "OKConfigPersistent.h"

ConfigState::ConfigState(IOKCommands *Commands, IOKConfig *Config)
{
    this->Commands = Commands;
    this->Config = Config;
}

ConfigState::~ConfigState()
{
    //dtor
}

int ConfigState::handleKey(int key) {
    if (key == FL_F+3) {
        Config->toggleContrast();
        return(1);
    }
    if (key == FL_F+4) {
        Config->toggleFont();
        return(1);
    }
    if (key == FL_F+5) {
        Config->toggleLinecount();
        return(1);
    }

    OKConfigPersistent configWriter(Config);
    configWriter.write(CONFIGFILENAME);
    Commands->setNewState(Commands->getTypingState());
    return (1);
}

void ConfigState::enterState(void) {
    std::ostringstream menuText;

    Commands->setTextLines(8);
    Commands->clear_all();

    menuText << _("Setup") << "\n\n";

    menuText << "F3 - " << _("Contrast") << ": " << Config->getContrastIndex() + 1 << "\n";
    menuText << "F4 - " << _("Typeface") << ": " << Config->getFontIndex() + 1 << "\n";
    menuText << "F5 - " << _("Number of lines") << ": " << Config->getLinecountIndex() + 1 << "\n";

    menuText << "\n" << _("Press space bar to go back");

    Commands->getInput()->value(menuText.str().c_str());
}

void ConfigState::tick(void) {
    // nothing to do
}

