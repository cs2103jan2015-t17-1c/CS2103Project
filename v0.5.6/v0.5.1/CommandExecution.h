#pragma once
//
//  Header.h
//  Task
//
//  Created by Yang Hong Jie on 10/3/15.
//  Copyright (c) 2015 Yang Hong Jie. All rights reserved.
//


#include "CommandChecker.h"
#include "SmartAdder.h"
#include "Storage.h"


using namespace std;

class CommandExecution
{
private:
	CommandChecker _checker;
	Storage _tasks;
	SmartAdder _adder;

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

	enum StandardCommand { 
		ADD, DEL, DISPLAY, UPDATE, SEARCH, EXIT, INVALID, LOCATION, UNDO, REDO, MARK, UNMARK,TRACK
	};



	string retrieveContent(string, size_t);
	string readCommand(string);
	StandardCommand const determineCommandType(string);
    void executeCommand(StandardCommand, string &, string);

	void performAdd(string &, string);
	void performDisplay(string &);
	void performUpdate(string &, string);
	void performDelete(string &, string);
	void performUndo(string &);
	void performRedo(string &);
	void performInvalidMessage(string &);
	void performExit();
	void performLocation(string &, string);
	void performMark(string &, string);
	void performUnmark(string &, string);
	void performTrack(string &);
	void performSearch(string &, string);


	void storeInTaskInfo();
	void addEventToList();
	

	
    string invalidCommand(int);
    bool isScheduleTask (int, int);
    bool isDeadlineTask (int, int);

	
    void saveInFile();
	void saveTaskLists(); 
    bool isUndoAlready();

	
    
	string getCommand(string, size_t &);
	
	//This function is for UI to display recent tasks
	string readRecentTask(int index);

	string getAddResult(int, int, string);


	bool isExit(string);
	bool isInvalidFormat(string, size_t);
	bool isSingleWordCommand(string);
	bool isEmptyContent(string);


	//new functions added for unit testing

	int getStartYear();
	int getEndYear();
	string getDescription();
	bool isValidIndex(int);
	int getSize();
	void seperateInputForUpdate(string, int &, string &);
	bool updateToTasks(int);
};
