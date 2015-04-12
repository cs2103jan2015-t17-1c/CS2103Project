#pragma once
//@Wang Jiexuan A09119454A
#include <iostream>
#include <fstream>
#include <string>
#include "CurrentTime.h"

using namespace std;

class Logger {
private:
	ofstream _log;
	CurrentTime _loggerTime;
public:
	Logger();
	~Logger();
	void logUserInput(string);
	void logOpenFile();
	void logWriteTime();
	void logInput(string);
	void logClose();
};