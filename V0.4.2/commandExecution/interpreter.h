#ifndef INTERPRETER_H 
#define INTERPRETER_H 
#include <string> 
#include <iostream> 
#include <cstdlib> 
#include "CurrentTime.h"
using namespace std;

class interpreter{

private:

static const string STD_MONTH[12];

static const string STD_ADD;

static const string STD_DELETE;

static const string STD_CLEAR;

static const string STD_DISPLAY;

static const string STD_UPDATE;

static const string STD_SEARCH;

static const string STD_LOCATION;

static const string STD_UNDO;

static const string STD_REDO;

static const string STD_EXIT;

static const string STD_MARK;

static const string STD_UNMARK;

static const string STD_TRACK;

struct eventinput{

		string description;

		int startTime;
		int startDay;
		int startMonth;
		int startYear;
		int endTime;
		int endDay;
		int endMonth;
		int endYear;
		bool validInput;

};
eventinput wholeEvent;
public:
	interpreter();
	string interpretCommand(string);
	
	void setDefaultStartTime();
	void setDefaultStartDay();
	void setDefaultStartMonth();
	void setDefaultStartYear();
	void setDefaultEndTime();
	void setDefaultEndDay();
	void setDefaultEndMonth();
	void setDefaultEndYear();
	void setDefaultDescription();
	void setDefaultValidInput();
	
	bool checkEachPossibility(const string[], string);
	void convert(string);
	void setDescription(string line);
	void setStart(string line);
	void setStartYear(int startYear);
	void setStartMonth(int startMonth);
	void setStartDay(int startDay);
	void setStartTime(int startTime);
	void setEnd(string line);
	void setEndYear(int endYear);
	void setEndMonth(int endMonth);
	void setEndDay(int endDay);
	void setEndTime(int endTime);
	void appendMissingInfo();
	void appendMissingStartInfo();
	void appendMissingEndInfo();

	
	string getDescription();
	int getStartTime();
	int getEndTime();
	int getStartDay();
	int getStartMonth();
	int getStartYear();
	int getEndDay();
	int getEndMonth();
	bool getvalidInput();
	int getEndYear();
	void reset();
};
#endif