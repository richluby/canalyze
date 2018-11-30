// Copyright 2018
// Richard Luby, all rights reserved
#ifndef LOGGER_HEADERS
#define LOGGER_HEADERS

#include <string>
#include <fstream>

// provides the logging levels
enum class LOG_LEVEL{DEBUG, INFO, WARN, ERROR, FATAL};

class Logger {
// this class implements a leveled logger
	
	// the stream to which to output the log
	std::ostream* outstream;

	public:
		// initializes the logger
		Logger(std::ostream* logOutput);
		// prints a string at the DEBUG level
		int Debug(std::string formatString);
		// prints a string at the INFO level
		int Info(std::string formatString);
		// prints a string at the WARN level
		int Warn(std::string formatString);
		// prints a string at the ERROR level
		int Error(std::string formatString);
		// prints a string at the FATAL level
		int Fatal(std::string formatString);
		// prints a string at the DEBUG level with the specified args
		template <typename... ArgTypes>
		int Debug(std::string formatString, ArgTypes... args);
		// prints a string at the INFO level with the specified args
		template <typename... ArgTypes>
		int Info(std::string formatString, ArgTypes... args);
		// prints a string at the WARN level with the specified args
		template <typename... ArgTypes>
		int Warn(std::string formatString, ArgTypes... args);
		// prints a string at the ERROR level with the specified args
		template <typename... ArgTypes>
		int Error(std::string formatString, ArgTypes... args);
		// prints a string at the FATAL level with the specified args
		template <typename... ArgTypes>
		int Fatal(std::string formatString, ArgTypes... args);
		// logs a string at or above the specified level
		template <typename... ArgTypes>
		int LogLevel(LOG_LEVEL level, const std::string &formatString, ArgTypes... args);
};

#endif // LOGGER_HEADERS
