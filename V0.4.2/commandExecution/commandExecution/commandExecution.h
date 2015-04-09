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
	interpreter _inter;
	Storage _tasks;
	string _content;
	struct TaskInfo {
		string description;
		int startTime;
		int startDay;
		int startMonth;
		int startYear;
		int endTime;
		int endDay;
		int endMonth;
		int endYear;
	} ;
	TaskInfo _taskInfo;
public:
	CommandExecution(void);
	~CommandExecution(void);
	enum StardardCommand { 
		ADD, DELET, DISPLAY, UPDATE, SEARCH, EXIT, INVALID, LOCATION, UNDO, REDO, MARK,UNMARK,TRACK
	};
	string readCommand(string);
	StardardCommand const determineCommandType(string);
	void executeCommand(StardardCommand, string&);
	void performAdd(string&);
	void performDisplay(string&);
	void performUpdate(string&);
	void performDelete(string&);
	void performUndo(string&);
	void performRedo(string&);
	void performExit();
	void storeInTaskInfo();
	void addEventToList();
	bool isInvalid(size_t, string);
	void performSearch(string&);
	string addResult();
	string invalidCommand(int);
	void saveInFile();
	void saveTaskLists();
	void performLocation(string&);
	void performMark(string&);
	void performUnmark(string&);
	void performTrack(string&);
};

