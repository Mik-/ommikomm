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

#include <FL/Fl.H>
#include <FL/Enumerations.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Multiline_Input.H>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <libintl.h>

#include "config.h"
#include "src/AutopoweroffState.h"
#include "src/IOKState.h"
#include "src/IOKCommands.h"
#include "src/NormaleState.h"
#include "src/OmmiKomm.h"
#include "src/help/HelpState.h"
#include "src/config/ConfigState.h"
#include "src/config/OKConfig.h"
#include "src/textfield/OmmiKommTextfield.h"

using namespace std;

OmmiKommTextfield *input;

void timercallback(void *data) {
    input->tick();
    Fl::repeat_timeout(1.0, timercallback);
}

int main(int argc, char ** argv) {
    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALEDIR);
    textdomain(PACKAGE);

cout << LOCALEDIR << "\n";

    Fl_Window *window;
    window = new Fl_Window(Fl::w(), Fl::h());
    input = new OmmiKommTextfield(RAND, RAND, Fl::w() - 2 * RAND,
            Fl::h() - 2 * RAND, "");

    window->end();
    window->show(argc, argv);

    Fl::add_timeout(1.0, timercallback);

    input->setNewState(input->getHelpState());

    return (Fl::run());
}
