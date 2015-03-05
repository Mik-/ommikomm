/*
 * PINInputState.h
 *
 *  Created on: 05.03.2015
 *      Author: michael
 */

#ifndef PININPUTSTATE_H_
#define PININPUTSTATE_H_

#include <string>
#include <sstream>

#include "ICommands.h"
#include "IState.h"
#include "settings/ISettings.h"

class PINInputState : public IState
{
    public:
		PINInputState(ICommands *Commands, ISettings *Config, IState *PINOkState,
				IState *PINWrongState);
        virtual ~PINInputState();

        std::string getEnteredPIN();
    protected:
        virtual int handleKey(int key);
        virtual void enterState(void);
        virtual void tick(void);
    private:
        ICommands *Commands;
        ISettings *Config;
        IState *PINOkState;
        IState *PINWrongState;
        std::stringstream enteredPIN;
};

#endif /* PININPUTSTATE_H_ */
