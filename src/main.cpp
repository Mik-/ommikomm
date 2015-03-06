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
#include <FL/Fl_Window.H>
#include <libintl.h>
#include <clocale>

#include "config.h"
#include "OmmiKomm.h"
#include "textfield/OmmiKommTextfield.h"

using namespace std;

// the input field as global variable
OmmiKommTextfield *input;

// this function is registered by the FLTK framework an will be called every second
void timercallback(void *data) {
	// call the tick method of the input which will call the tick method of the active state
    input->tick();
    Fl::repeat_timeout(1.0, timercallback);
}

int main(int argc, char ** argv) {
    // Initialize the i18n
	setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALEDIR);
    textdomain(PACKAGE);

    // create a window and place the text field on it
    Fl_Window *window;
    window = new Fl_Window(Fl::w(), Fl::h());
    input = new OmmiKommTextfield(BORDERWIDTH, BORDERWIDTH, Fl::w() - 2 * BORDERWIDTH,
            Fl::h() - 2 * BORDERWIDTH, "");

    window->end();
    window->show(argc, argv);

    // start the tick timer
    Fl::add_timeout(1.0, timercallback);

    // set the initial state (the help screen)
    input->setNewState(input->getHelpState());

    // run the app
    return (Fl::run());
}
