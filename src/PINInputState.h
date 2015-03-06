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
#include "IPINResult.h"

class PINInputState : public IState
{
    public:
		PINInputState(ICommands *Commands, IPINResult *PINResult, std::string caption);
        virtual ~PINInputState();

        std::string getEnteredPIN();
    protected:
        virtual int handleKey(int key);
        virtual void enterState(void);
        virtual void tick(void);
    private:
        ICommands *Commands;
        IPINResult *PINResult;
        std::stringstream enteredPIN;
        std::string caption;
};

#endif /* PININPUTSTATE_H_ */
