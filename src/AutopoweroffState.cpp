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

#include <AutopoweroffState.h>

using namespace std;

AutopoweroffState::AutopoweroffState(IOKCommands *Commands, int waitForShutdown)
{
    this->Commands = Commands;
    this->waitForShutdown = waitForShutdown;
    this->ticks = 0;
}

AutopoweroffState::~AutopoweroffState()
{
    //dtor
}

int AutopoweroffState::handleKey(int key) {
    Commands->setNewState(Commands->getNormalState());
    return (1);
}

void AutopoweroffState::enterState(void) {
    ticks = 0;
    Commands->setTextLines(7);
    Commands->getInput()->value("OmmiKomm wird jetzt ausgeschaltet.\n\nBitte nicht vergessen, den Fernseher wieder auf \"TV\" zu stellen.");
}

void AutopoweroffState::tick(void) {
    string newtext;
    ostringstream zahl;

    ticks++;

    zahl << (waitForShutdown - ticks);
    newtext = Commands->getInput()->value();
    newtext += zahl.str() +  ". ";
    Commands->getInput()->value(newtext.c_str());

    if (ticks >= waitForShutdown) {
        Commands->poweroff();
    }
}

