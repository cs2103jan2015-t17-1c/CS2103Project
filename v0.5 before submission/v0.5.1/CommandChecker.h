#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <assert.h>
#include <fstream>
#include <exception>
#include <ctype.h>

using namespace std;




class CommandChecker{

public:
	CommandChecker(void);
	~CommandChecker(void);

	string getCommand(string, size_t &);
	string interpretCommand(string);
	string getContent(string, size_t);
	
	bool isExitCommand(string);
	bool isAddCommand(string);
	bool isDeleteCommand(string);
	bool isDisplayCommand(string);
	bool isUpdateCommand(string);
	bool isMarkCommand(string);
	bool isUnmarkCommand(string);
	bool isUndoCommand(string);
	bool isRedoCommand(string);
	bool isSearchCommand(string);
	bool isTrackCommand(string);
	bool isLocationCommand(string);
	bool isSingleWordCommand(string);
	bool isInvalidCommandFormat(string, size_t);
	bool isEmptyContent(string);

	void seperateContent(string, int &, string &);
	void verifyLengthOfUserInput(string);
};

