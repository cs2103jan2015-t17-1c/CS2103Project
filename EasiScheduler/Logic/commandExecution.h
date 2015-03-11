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

	string readCommand(string userInput);

	StardardCommand const determineCommandType(string command);

	void executeCommand(StardardCommand commandType,string&);

	void performAdd(string&);

	void performDisplay(string&);

	void performUpdate(string&);

	void performDelete(string&);

	void performExit();

	void storeInTaskInfo();

	void addEventToList();

	string addResult();

	bool isNormalEvent();

};



