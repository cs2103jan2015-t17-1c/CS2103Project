#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <assert.h>
#include <fstream>
#include <exception>
#include <ctype.h>
#include "interpreter.h"
#include "Storage.h"

using namespace std;

class CommandExecution
{
private:
	interpreter inter;
	Storage tasks;
	string _content;
	struct TaskInfo {
		string description;
		string month;
		int intMonth;
		int day;
		int startTime;
		int endTime;
	} ;
	TaskInfo taskInfo;
public:
	CommandExecution(void);
	~CommandExecution(void);
	enum StardardCommand { 
		ADD, DELETE, DISPLAY, UPDATE, EXIT, INVALID
	};
	string readCommand(string);
	StardardCommand const determineCommandType(string);
	void executeCommand(StardardCommand, string&);
	void performAdd(string&);
	void performDisplay(string&);
	void performUpdate(string&);
	void performDelete(string&);
	void performExit();
	void storeInTaskInfo();
	void addEventToList();
	void verify(size_t, string);
	string addResult();
	string invalidCommand(int);
};

