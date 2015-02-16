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

#include <FL/Fl.H>
#include <FL/Enumerations.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Multiline_Input.H>

#include <cstdlib>
#include <iostream>
#include <sstream>

#include "../AutopoweroffState.h"
#include "../IOKCommands.h"
#include "../OmmiKomm.h"
#include "../help/HelpState.h"
#include "OmmiKommTextfield.h"

#include "../settings/Settings.h"
#include "../settings/SettingsPersistence.h"
#include "../settings/SettingsState.h"
#include "../TypingState.h"


OmmiKommTextfield::OmmiKommTextfield(int X, int Y, int W, int H, const char* L) :
  Fl_Multiline_Input(X, Y, W, H, L)
{
  type (FL_MULTILINE_INPUT_WRAP);

  // Create the config object and the reader for the config
  config = new Settings(this);
  SettingsPersistence configReader(config);

  // Build the config filename and read the config file
  std::stringstream configFilename;
  configFilename << configReader.getHomeDir() << "/" << CONFIGFILENAME;
  configReader.read(configFilename.str());

  // Create the state objects
  helpState = new HelpState(this, WAITCLOSEHELP);
  typingState = new TypingState(this, config->getLinecount(), AUTOPOWEROFF);
  autopoweroffState = new AutopoweroffState(this, WAITPOWEROFF);
  configState = new SettingsState(this, config);

  currentState = helpState;
}

void OmmiKommTextfield::setNewState(IOKState *newState) {
    currentState = newState;
    currentState->enterState();
}

IOKState *OmmiKommTextfield::getHelpState(void) {
    return (helpState);
}

int OmmiKommTextfield::handle(int e) {
  switch(e) {
    case FL_KEYDOWN : {
        int key = Fl::event_key();

        int ret = currentState->handleKey(key);

        if (ret > 0) {
            return (ret);
        }
    }
  }

  return (Fl_Multiline_Input::handle(e));
}

void OmmiKommTextfield::tick(void) {
    currentState->tick();
}

void OmmiKommTextfield::clear_all() {
    static_value("");
}

void OmmiKommTextfield::poweroff() {
    std::string command = "sudo poweroff";
    #ifndef DEBUG
    int sysres = system(command.c_str());
    #endif

    exit(0);
}

Fl_Multiline_Input *OmmiKommTextfield::getInput(void) {
    return (this);
}

void OmmiKommTextfield::setTextLines(int lines) {
    textsize(h() / (lines * 1.2));

    clear_all();
}

IOKState *OmmiKommTextfield::getTypingState(void) {
    return (typingState);
}

IOKState *OmmiKommTextfield::getAutopoweroffState(void) {
    return (autopoweroffState);
}

IOKState *OmmiKommTextfield::getConfigState(void) {
    return (configState);
}

void OmmiKommTextfield::configChange() {
    textfont(config->getFont());
    color(config->getBackColor());
    textcolor(config->getTextColor());
    typingState->setLines(config->getLinecount());

    currentState->enterState();
}
