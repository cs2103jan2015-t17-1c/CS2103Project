#pragma once
#include <iostream>
#include <string>
#include <sstream>
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
		int month;
		int day;
		int startTime;
		int endTime;
	} taskInfo;
public:
	CommandExecution(void);
	~CommandExecution(void);
	enum StardardCommand { 
		ADD, DELETE, DISPLAY, UPDATE, CLEAR, EXIT, INVALID
	};
	string readCommand(string );
	StardardCommand const determineCommandType(string);
	void executeCommand(StardardCommand, string&);
	void performAdd(string&);
	void performDisplay(string&);
	void performUpdate(string&);
	void performDelete(string&);
	void performExit();
	void storeInTaskInfo();
	void addEventToList();
	string addResult();;
};

