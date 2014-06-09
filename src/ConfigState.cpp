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

#include "ConfigState.h"
#include "AutopoweroffState.h"

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

    Commands->setNewState(Commands->getNormalState());
    return (1);
}

void ConfigState::enterState(void) {
    std::string menuText;

    Commands->setTextLines(7);
    Commands->clear_all();

    menuText = "Einstellungen\n"
        "\n";

    std::ostringstream contrast_zahl;
    contrast_zahl << Config->getContrastIndex() + 1;
    menuText += "F3 - Kontrast " + contrast_zahl.str() + "\n";

    std::ostringstream font_zahl ;
    font_zahl << Config->getFontIndex() + 1;
    menuText += "F4 - Schriftart " + font_zahl.str() + "\n";

    std::ostringstream linecount_zahl ;
    linecount_zahl << Config->getLinecountIndex() + 1;
    menuText += "F5 - Zeilenzahl " + linecount_zahl.str() + "\n";

    menuText += "\nTaste drücken";

    Commands->getInput()->value(menuText.c_str());
}

void ConfigState::tick(void) {
    // nothing to do
}

