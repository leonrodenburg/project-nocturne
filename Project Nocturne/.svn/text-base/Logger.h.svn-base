#pragma once

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <string>			/* include string header */
#include <fstream>			/* include fstream header */
#include <sstream>			/* include sstream header */
#include <iostream>			/* include iostream header */
#include <iomanip>			/* include iomanip header */
#include <ctime>			/* include ctime header for time functionality */
#include <stdarg.h>			/* include stdarg.h header for va_list support */
#include <stdio.h>			/* include stdio.h header */
#include <fcntl.h>			/* include fcntl.h header */

namespace NocturneCore
{
#if defined _WIN32 || defined _WIN64
	/* defines */
	#define LOGCONSOLE(format, ...)			NocturneCore::Logger::Get(NocturneCore::Logger::DEBUG)->ToConsole()->Log(format, __VA_ARGS__);
	#define LOGFILE(format, ...)			NocturneCore::Logger::Get(NocturneCore::Logger::DEBUG)->ToFile()->Log(format, __VA_ARGS__);
	#define LOGALL(format, ...)             NocturneCore::Logger::Get(NocturneCore::Logger::DEBUG)->ToConsole()->ToFile()->Log(format, __VA_ARGS__);
	#define LOGERRORCONSOLE(format, ...)	NocturneCore::Logger::Get(NocturneCore::Logger::FATAL)->ToConsole()->Log(format, __VA_ARGS__);
	#define LOGERRORFILE(format, ...)		NocturneCore::Logger::Get(NocturneCore::Logger::FATAL)->ToFile()->Log(format, __VA_ARGS__);
	#define LOGERRORALL(format, ...)		NocturneCore::Logger::Get(NocturneCore::Logger::FATAL)->ToConsole()->ToFile()->Log(format, __VA_ARGS__);
#else
	/* defines */
	#define LOGCONSOLE(format, args...)			NocturneCore::Logger::Get(NocturneCore::Logger::DEBUG)->ToConsole()->Log(format, args);
	#define LOGFILE(format, args...)			NocturneCore::Logger::Get(NocturneCore::Logger::DEBUG)->ToFile()->Log(format, args);
	#define LOGALL(format, args...)             NocturneCore::Logger::Get(NocturneCore::Logger::DEBUG)->ToConsole()->ToFile()->Log(format, args);
	#define LOGERRORCONSOLE(format, args...)	NocturneCore::Logger::Get(NocturneCore::Logger::FATAL)->ToConsole()->Log(format, args);
	#define LOGERRORFILE(format, args...)		NocturneCore::Logger::Get(NocturneCore::Logger::FATAL)->ToFile()->Log(format, args);
	#define LOGERRORALL(format, args...)		NocturneCore::Logger::Get(NocturneCore::Logger::FATAL)->ToConsole()->ToFile()->Log(format, args);
#endif

	class Logger
	{
	public:
		enum LogLevel { FATAL, WARNING, NOTICE, DEBUG };

		static Logger* Get();
		static Logger* Get(LogLevel logLevel);

		Logger* ToConsole();
		Logger* ToFile();
		Logger* ToFile(std::string sFilename);

		void Log(char* pFormat, ...);
	private:
		LogLevel _logLevel;
		std::ofstream* _pOutputFile;
		bool _bToConsole;

		Logger();
		Logger(LogLevel logLevel);
		virtual ~Logger();

		void _Log(char* pFormat, va_list pArguments);
	};
}

#endif