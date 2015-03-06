/*
 * IPINResult.h
 *
 *  Created on: 06.03.2015
 *      Author: michael
 */

#ifndef IPINRESULT_H_
#define IPINRESULT_H_

#include <string>

class IPINResult {
	public:
		virtual void enteredPIN(std::string PIN) = 0;
};

#endif /* IPINRESULT_H_ */
