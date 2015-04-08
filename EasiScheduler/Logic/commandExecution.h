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
	
	CommandExecution();
	~CommandExecution();

	enum StardardCommand { 
		ADD, DELET, DISPLAY, UPDATE, SEARCH, EXIT, INVALID, LOCATION, UNDO, REDO, MARK,UNMARK,TRACK
	};



	void retrieveContent(string, size_t);
	string readCommand(string);
	StardardCommand const determineCommandType(string);
    void executeCommand(StardardCommand, string &);

	void performAdd(string &);
	void performDisplay(string &);
	void performUpdate(string &);
	void performDelete(string &);
	void performUndo(string &);
	void performRedo(string &);
	void performExit();

	void storeInTaskInfo();
	void addEventToList();
	void performSearch(string &);

	
    string invalidCommand(int);
    bool isNormalTask ();
    bool CommandExecution::isDeadlineTask ();

	
    void saveInFile();
	void saveTaskLists(); 
    bool CommandExecution::isUndoTrue();

	
    void performLocation(string &);
	void performMark(string &);
	void performUnmark(string &);
	void performTrack(string &);
	string getCommand(string, size_t &);
	
	//This function is for UI to display recent tasks
	string readRecentTask(int index);

	string getContent();
	string getAddResult();



	bool isExit(string);
	bool isInvalidFormat(size_t, string);
	bool isSingleWordCommand(string);
	bool isEmptyContent(string);



	

};


