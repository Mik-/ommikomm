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

#include "NormaleState.h"

NormaleState::NormaleState(IOKCommands *Commands, int lines, int waitForAutopoweroff)
{
    this->Commands = Commands;
    this->lines = lines;
    this->waitForAutopoweroff = waitForAutopoweroff;
}

NormaleState::~NormaleState()
{
    //dtor
}

void NormaleState::setLines(int lines) {
    this->lines = lines;
}

int NormaleState::handleKey(int key){
    ticks = 0;

    if (key == FL_F+1) {
        Commands->setNewState(Commands->getHelpState());
        return(1);
    }
    if (key == FL_F+10) {
        Commands->setNewState(Commands->getConfigState());
        return(1);
    }
    if (key == FL_Escape or key == FL_F+5) {
        Commands->clear_all();
        return (1);
    }
    if (key == FL_F+12) {
        Commands->setNewState(Commands->getAutopoweroffState());
        return (1);
    }

    return (0);
}

void NormaleState::enterState(void) {
    ticks = 0;
    Commands->setTextLines(lines);
}

void NormaleState::tick(void) {
    ticks++;
//    if (ticks >= waitForAutopoweroff) {
//        Commands->setNewState(Commands->getAutopoweroffState());
//    }
}

