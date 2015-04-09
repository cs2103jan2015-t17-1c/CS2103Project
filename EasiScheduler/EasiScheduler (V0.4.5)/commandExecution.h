#pragma once
//
//  Header.h
//  Task
//
//  Created by Yang Hong Jie on 10/3/15.
//  Copyright (c) 2015 Yang Hong Jie. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include <assert.h>
#include <fstream>
#include <exception>
#include <ctype.h>
#include "Interpreter.h"
#include "Storage.h"

using namespace std;

class CommandExecution
{
private:
	Interpreter _inter;
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

	enum StandardCommand { 
		ADD, DELET, DISPLAY, UPDATE, SEARCH, EXIT, INVALID, LOCATION, UNDO, REDO, MARK,UNMARK,TRACK
	};



	void retrieveContent(string, size_t);
	string readCommand(string);
	StandardCommand const determineCommandType(string);
    void executeCommand(StandardCommand, string &);

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
    bool isNormalTask (int, int);
    bool isDeadlineTask (int, int);

	
    void saveInFile();
	void saveTaskLists(); 
    bool isUndoAlready();

	
    
	string getCommand(string, size_t &);
	
	//This function is for UI to display recent tasks
	string readRecentTask(int index);

	string getContent();
	string getAddResult(int, int, string);


	bool isExit(string);
	bool isInvalidFormat(size_t, string);
	bool isSingleWordCommand(string);
	bool isEmptyContent(string);


	//new functions added for unit testing

	int getStartYear();
	int getEndYear();
	string getDescription();
	bool isValidIndexForDeletion(int);
	bool isInvalidIndex(int);
	int getSize();
	void seperateInputForUpdate(string, int &, string &);
	bool updateToTasks(int);
};

