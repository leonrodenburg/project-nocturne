#include "Logger.h"		/* include Logger header */

/**
 * Get a Logger instance with the DEBUG LogLevel.
 *
 * @return	NocturneCore::Logger instance
 */
NocturneCore::Logger* NocturneCore::Logger::Get()
{
	/* call overloaded method */
	return Logger::Get(DEBUG);
}

/**
 * Get a Logger instance with a specifiedLogLevel.
 *
 * @param   logLevel	The LogLevel
 *
 * @return  Logger instance
 */
NocturneCore::Logger* NocturneCore::Logger::Get(LogLevel logLevel)
{
	/* create a Logger instance */
	return new Logger(logLevel);
}

/**
 * Specify that the output should be written to the console.
 *
 * @return  Logger instance ready to log to console
 */
NocturneCore::Logger* NocturneCore::Logger::ToConsole()
{
	/* set the boolean to true */
	_bToConsole = true;

	/* return Logger instance */
	return this;
}

/**
 * Specify that the current Logger object should also
 * write to the standard file (defaults to logfile.txt)
 *
 * @return  Logger instance ready to log to file
 */
NocturneCore::Logger* NocturneCore::Logger::ToFile()
{
	/* call overloaded method with default filename */
	return Logger::ToFile("logfile.txt");
}

/**
 * Specify that the current Logger object should also
 * write to the specified filename.
 *
 * @param   sFilename   The filename
 *
 * @return  Logger instance ready to log to file
 */
NocturneCore::Logger* NocturneCore::Logger::ToFile(std::string sFilename)
{
	/* if the filename is not empty */
	if(sFilename.length() > 0)
	{
		/* open the filestream */
		_pOutputFile = new std::ofstream(sFilename.c_str(), std::ios::app);
	}
	else
	{
		/* initialize output file to NULL */
		_pOutputFile = NULL;
	}

	/* return this */
	return this;
}

/**
 * Log a message. The variable number of arguments can be used
 * to log multiple values, specified in the C-style format.
 *
 * @param   pFormat	 C-style formatting string
 * @param   ...		 Variable number of arguments
 */
void NocturneCore::Logger::Log(char* pFormat, ...)
{
	/* create a va_list to hold the arguments */
	va_list pArguments;

	/* save the arguments */
	va_start(pArguments, pFormat);

	/* call overloaded Log() method */
	this->_Log(pFormat, pArguments);

	/* close the argument list */
	va_end(pArguments);
}

/**
 * Constructor, private so only the Logger itself can instantiate 
 * objects. Calls overloaded constructor with DEBUG level.
 */
NocturneCore::Logger::Logger()
{
	/* call overloaded constructor */
	Logger::Logger(DEBUG);
}

/**
 * Overloaded constructor, setting the LogLevel and output filename.
 *
 * @param   logLevel	The NocturneCore::LogLevel
 */
NocturneCore::Logger::Logger(LogLevel logLevel)
{
	/* set the NocturneCore::LogLevel */
	_logLevel = logLevel;

	/* set the output file to NULL */
	_pOutputFile = NULL;

	/* default to not writing to the console */
	_bToConsole = false;
}

/**
 * Destructor, private so only Logger objects can destroy
 * themselves.
 */
NocturneCore::Logger::~Logger()
{
	/* if a file was opened */
	if(NULL != _pOutputFile)
	{
		/* close the file */
		_pOutputFile->close();

		/* delete the pointer to the output file */
		delete _pOutputFile;
	}
}

/**
 * Log a message, setting the va_list arguments in the format
 * to create the output message.
 * 
 * @param   pFormat		C-style formatting string
 * @param   pArguments  va-list with arguments
 */
void NocturneCore::Logger::_Log(char* pFormat, va_list pArguments)
{
	/* declare string to find text value for LogLevel */
	std::string sLevelString = "";

	/* switch over the log level */
	switch(_logLevel)
	{
	case FATAL:	 /* if the level is FATAL */
		sLevelString = "ERROR"; 
		break;
	case WARNING:   /* if the level is WARNING */
		sLevelString = "WARNING";
		break;
	case NOTICE:	/* if the level is NOTICE */
		sLevelString = "NOTICE"; 
		break;
	case DEBUG:	 /* if the level is DEBUG */
		sLevelString = "DEBUG"; 
		break;
	default:		/* if the level is not specified */
		sLevelString = "UNKNOWN";
		break;
	}

	/* declare time_t object */
	std::time_t ttCurrentTime;
    
    /* declare tm object */
    std::tm* tmTimeInfo;

	/* declare a stringstream to build the output */
	std::stringstream ssTimeString;
    
    /* fill time_t object */
    time(&ttCurrentTime);
    
    /* get time info */
    tmTimeInfo = localtime(&ttCurrentTime);

	/* set the fill character */
	ssTimeString.fill('0');

	/* build the string */
	ssTimeString	<< std::setw(2) << tmTimeInfo->tm_mday << "-"           /* day */
					<< std::setw(2) << tmTimeInfo->tm_mon + 1 << "-"        /* month */
					<< std::setw(4) << tmTimeInfo->tm_year + 1900 << " "    /* year */
					<< std::setw(2) << tmTimeInfo->tm_hour << ":"           /* hour */
					<< std::setw(2) << tmTimeInfo->tm_min << ":"            /* minute */
					<< std::setw(2) << tmTimeInfo->tm_sec;                  /* second */

	/* declare array of chars to combine va_list with format */
	char pLogMessage[256];

	/* put the arguments in the format */
	vsprintf(pLogMessage, pFormat, pArguments);

	/* declare stringstream for output */
	std::stringstream ssOutputMessage;

	/* combine the time, log level and message */
	ssOutputMessage << ssTimeString.str() << " " << sLevelString << ": " << pLogMessage << std::endl;

	/* if the output file is opened */
	if(NULL != _pOutputFile)
	{
		/* write to the output file */
		*_pOutputFile << ssOutputMessage.str();

		/* flush the buffer */
		_pOutputFile->flush();
	}

	/* if the ouput should be written to console */
	if(_bToConsole)
	{
		/* write the output to the console */
		std::cout << ssOutputMessage.str();
	}

	/* delete instance of Logger */
	delete this;
}
