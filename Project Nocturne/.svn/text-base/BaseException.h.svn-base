#pragma once

#ifndef _BASEEXCEPTION_H_
#define _BASEEXCEPTION_H_

#include "Resources.h"			/* include Resources header */
#include <exception>			/* include exception header */

namespace NocturneCore
{
	class BaseException : public std::exception
	{
	public:
		/**
		 * Constructor, setting the reason for the exception
		 *
		 * @param	what	The reason of the exception
		 */
		BaseException(char* what) : std::exception(what)
		{
			/* assign the reason */
			this->_what = what;

			/* if debugging is enabled */
#ifdef _DEBUG_
			/* log to all outputs */
			this->Log();
#endif
		}

		/**
		 * Destructor.
		 */
		virtual ~BaseException()
		{

		}

		/**
		 * Return the reason of the exception.
		 *
		 * @return	The reason of the exception
		 */
		virtual const char* what() const throw()
		{
			/* return the reason */
			return this->_what;
		}

#ifdef _DEBUG_
		/**
		 * Log the exception to all outputs.
		 */
		virtual void Log()
		{
			/* log the reason of the exception */
			LOGERRORALL(this->_what);
		}
#endif

	private:
		char* _what;
	};
}

#endif