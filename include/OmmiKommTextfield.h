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

#ifndef OMMIKOMMTEXTFIELD_H_
#define OMMIKOMMTEXTFIELD_H_

#include <FL/Fl.H>
#include <FL/Enumerations.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Multiline_Input.H>

#include <IOKCommands.h>
#include <HelpState.h>
#include <NormaleState.h>
#include <AutopoweroffState.h>
#include <ConfigState.h>
#include <OKConfig.h>

class OmmiKommTextfield : public Fl_Multiline_Input, public IOKCommands, public IOKConfigChange {
    IOKState *currentState;
    HelpState *helpState;
    NormaleState *normalState;
    AutopoweroffState *autopoweroffState;
    ConfigState *configState;
    OKConfig *config;

    virtual void clear_all();
    virtual void poweroff();
    virtual Fl_Multiline_Input *getInput(void);
    virtual void setTextLines(int lines);
    virtual IOKState *getNormalState(void);
    virtual IOKState *getAutopoweroffState(void);
    virtual IOKState *getConfigState(void);
    virtual void configChange();
public:
    OmmiKommTextfield(int X,int Y,int W,int H,const char* L);

    virtual void setNewState(IOKState *newState);
    virtual IOKState *getHelpState(void);
    int handle(int e);
    void tick(void);
};

#endif /* OMMIKOMMTEXTFIELD_H_ */
