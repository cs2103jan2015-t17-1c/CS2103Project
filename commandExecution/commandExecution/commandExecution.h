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
	struct TaskInfo {
		string description;
		string month;
		int day;
		int startTime;
		int endTime;
	} taskInfo;
public:
	CommandExecution(void);
	~CommandExecution(void);
	enum StardardCommand { 
		ADD, DELETE, DISPLAY, UPDATE,CLEAR, EXIT, INVALID
	};
	string readCommand();
	StardardCommand const determineCommandType(string command);
	void executeCommand(StardardCommand commandType);
	void performAdd();
	void performDisplay();
	void performUpdate();
	void performDelete();
	void performExit();
	void storeInTaskInfo();
	void addEventToList();
	void printAddResult();
	string getContentToBeAdded();
	bool isNormalEvent();
};

