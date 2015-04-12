#pragma once
//
//  Header.h
//  Task
//
//  Created by Yang Hong Jie on 10/3/15.
//  Copyright (c) 2015 Yang Hong Jie. All rights reserved.
//


//@Yang Hongjie A0108457B
#include "CommandChecker.h"
#include "SmartAdder.h"
#include "EasiStorage.h"
#include "Logger.h"

using namespace std;

class CommandExecution
{
private:
	CommandChecker _checker;
	EasiStorage _tasks;
	SmartAdder _adder;
	Logger _log;
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
	string getCommand(string, size_t &);
	string getAddResult(int, int, string);
	string getDescription();

	//This function is for UI to display recent tasks
	string readRecentTask(int index);
	
	StandardCommand const determineCommandType(string);
	void loggingInput(string);
	void verifyUserInput(string);
	void verifyTotalUnit();

	//@Wang Jiexuan A09119454A
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
	void saveInFile();
	void saveTaskLists(); 
	void seperateInputForUpdate(string, int &, string &);
    
    bool isScheduleTask (int, int);
    bool isDeadlineTask (int, int);   
    bool isUndoAlready();
	bool isExit(string);
	bool isInvalidFormat(string, size_t);
	bool isSingleWordCommand(string);
	bool isEmptyContent(string);
    bool isValidIndex(int);
	bool isUpdatedToTasks(int);

	int getStartYear();
	int getEndYear();
	
	
	
};
