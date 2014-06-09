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

#include <IOKState.h>
#include <IOKCommands.h>
#include <HelpState.h>
#include <NormaleState.h>
#include <AutopoweroffState.h>
#include <ConfigState.h>
#include <OKConfig.h>
#include <OKConfigPersistent.h>


#ifdef DEBUG
    #define AUTOPOWEROFF 10
    #define WAITPOWEROFF 5
    #define WAITCLOSEHELP 5
#else
    #define AUTOPOWEROFF 900
    #define WAITPOWEROFF 10
    #define WAITCLOSEHELP 30
#endif

#define RAND 5

using namespace std;

class MyTextfield : public Fl_Multiline_Input, public IOKCommands, public IOKConfigChange {
    IOKState *currentState;
    HelpState *helpState;
    NormaleState *normalState;
    AutopoweroffState *autopoweroffState;
    ConfigState *configState;
    OKConfig *config;

    virtual void clear_all() {
        static_value("");
    }

    virtual void poweroff() {
        string command = "sudo poweroff";
        #ifndef DEBUG
        int sysres = system(command.c_str());
        #endif

        exit(0);
    }

    virtual Fl_Multiline_Input *getInput(void) {
        return (this);
    }

    virtual void setTextLines(int lines) {
        textsize(h() / (lines * 1.2));

        clear_all();
    }

    virtual IOKState *getNormalState(void) {
        return (normalState);
    }

    virtual IOKState *getAutopoweroffState(void) {
        return (autopoweroffState);
    }

    virtual IOKState *getConfigState(void) {
        return (configState);
    }

    virtual void configChange() {
        textfont(config->getFont());
        color(config->getBackColor());
        textcolor(config->getTextColor());
        normalState->setLines(config->getLinecount());

        currentState->enterState();

        OKConfigPersistent *configwriter = new OKConfigPersistent(config);
        configwriter->Write("test.xml");
    }

public:
    MyTextfield(int X,int Y,int W,int H,const char* L=0) : Fl_Multiline_Input(X, Y, W, H, L) {
        type(FL_MULTILINE_INPUT_WRAP);

        config = new OKConfig(this);

        OKConfigPersistent *configreader = new OKConfigPersistent(config);
        configreader->Read("test.xml");

        helpState = new HelpState(this, WAITCLOSEHELP);
        normalState = new NormaleState(this, config->getLinecount(), AUTOPOWEROFF);
        autopoweroffState = new AutopoweroffState(this, WAITPOWEROFF);
        configState = new ConfigState(this, config);
    }

    virtual void setNewState(IOKState *newState) {
        currentState = newState;
        currentState->enterState();
    }

    virtual IOKState *getHelpState(void) {
        return (helpState);
    }

    int handle(int e) {
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

    void tick(void) {
        currentState->tick();
    }
};

MyTextfield *input;

void timercallback(void *data)
 {
    input->tick();
    Fl::repeat_timeout(1.0, timercallback);
 }

int main (int argc, char ** argv)
{
  Fl_Window *window;

  window = new Fl_Window (Fl::w(), Fl::h());
  input = new MyTextfield (RAND, RAND, Fl::w()-2*RAND, Fl::h()-2*RAND, "");

  window->end ();
  window->show (argc, argv);

  Fl::add_timeout(1.0, timercallback);

  input->setNewState(input->getHelpState());

  return(Fl::run());
}
