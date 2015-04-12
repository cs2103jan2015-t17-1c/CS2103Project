#include "Logger.h"


const string DEFAULT_LOGGING_FILE = "userInputLogger.txt";

Logger::Logger(void){
}

Logger::~Logger(void){
}

void Logger::logUserInput(string userInput) {
	logOpenFile();
	logWriteTime();
	logInput(userInput);
	logClose();
}

void Logger::logClose() {
	_log.close();
}

void Logger::logOpenFile() {
	_log.open(DEFAULT_LOGGING_FILE, ofstream::out | ofstream::app);
}

void Logger::logWriteTime() {
	_log << _loggerTime.getYear() << _loggerTime.getMonth() << _loggerTime.getDay() << endl;
}

void Logger::logInput(string userInput) {
	_log << userInput << endl;
	_log << endl;
}