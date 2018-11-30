// Copyright 2018
// Richard Luby, all rights reserved

#include "headers/logger.h"

using namespace std;

Logger::Logger(std::ostream* logOutput){
	this->outstream = logOutput;
}

int Logger::Info(string formatString){
	return this->Info(formatString, NULL);
}

template <typename... ArgTypes>
int Logger::Info(string formatString, ArgTypes... args){
	return this->LogLevel(LOG_LEVEL::INFO, formatString, args...);
}

int Logger::Warn(string formatString){
	return this->Warn(formatString, NULL);
}

template <typename... ArgTypes>
int Logger::Warn(string formatString, ArgTypes... args){
	return this->LogLevel(LOG_LEVEL::WARN, formatString, args...);
}

int Logger::Error(string formatString){
	return this->Error(formatString, NULL);
}

template <typename... ArgTypes>
int Logger::Error(string formatString, ArgTypes... args){
	return this->LogLevel(LOG_LEVEL::ERROR, formatString, args...);
}

int Logger::Fatal(string formatString){
	return this->Fatal(formatString, NULL);
}

template <typename... ArgTypes>
int Logger::Fatal(string formatString, ArgTypes... args){
	return this->LogLevel(LOG_LEVEL::FATAL, formatString, args...);
}

template <typename... ArgTypes>
int Logger::LogLevel(LOG_LEVEL level, const string &formatString, ArgTypes... args){
	// see
	// https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
	// answer : https://stackoverflow.com/a/26197300
	size_t required = std::snprintf(nullptr, 0, formatString.c_str(), args...) + 1;
	char* bytes = (char*) malloc(sizeof(char) * required);
	std::snprintf(bytes, required, formatString.c_str(), args...);
	*this->outstream << *bytes << std::endl;
	std::free(bytes);
	return required;
}
