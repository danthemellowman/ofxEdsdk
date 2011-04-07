#pragma once

#include <typeinfo>
#include <string>

#include "EDSDKWrapper.h"

/*
	even more useful would be to go through the different error codes and make a class for each,
	or at least for subsets. this would take a little longer.
*/

namespace EDSDK {
	class Exception : public std::exception {
	public:
		Exception(const EdsError& err) throw();
		virtual ~Exception() throw();
		virtual const char* what() const throw();
	private:
		EdsError err;
		std::string errString;
	};
}