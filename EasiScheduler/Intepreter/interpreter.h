#ifndef INTERPRETER_H 
#define INTERPRETER_H 
#include <string> 
#include <iostream> 
#include <cstdlib> 
using namespace std;

class interpreter{
private:
static const string COMMAND_ADD[3];
static const string COMMAND_DELETE[3];
static const string COMMAND_CLEAR[3];
static const string COMMAND_DISPLAY[3];
static const string COMMAND_UPDATE[3];
static const string COMMAND_SEARCH[3];
static const string COMMAND_LOCATION[3];
static const string COMMAND_UNDO[3];
static const string COMMAND_EXIT[3];
static const string COMMAND_MARK[3];
static const string COMMAND_REDO[3];
static const string COMMAND_UNMARK[3];
static const string COMMAND_TRACK[3];
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
};
eventinput wholeEvent;
public:
	interpreter();
	string interpretCommand(string);
    bool checkEachPossibility(const string[], string);
	void convert(string);
	string getDescription();
	int getStartTime();
	int getEndTime();
	int getStartDay();
	int getStartMonth();
	int getStartYear();
	int getEndDay();
	int getEndMonth();
	int getEndYear();
};
#endif