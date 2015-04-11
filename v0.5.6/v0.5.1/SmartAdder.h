#ifndef SMARTADDER_H
#define SMARTADDER_H 
#include <string> 
#include <iostream> 
#include <cstdlib> 
#include "CurrentTime.h"

using namespace std;

class SmartAdder{

private:

static const string STD_MONTH[36];

struct _eventinput{

		string description;

		int startTime;
		int startDay;
		int startMonth;
		int startYear;
		int endTime;
		int endDay;
		int endMonth;
		int endYear;
		bool isValidInput;

};

_eventinput wholeEvent;
public:
	SmartAdder();
	
	
	void setDefaultStartTime();
	void setDefaultStartDay();
	void setDefaultStartMonth();
	void setDefaultStartYear();
	void setDefaultEndTime();
	void setDefaultEndDay();
	void setDefaultEndMonth();
	void setDefaultEndYear();
	void setDefaultDescription();
	void setDefaultisValidInput();
	
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
	void setIsValidInput(bool isValid);
	void appendMissingInfo();

	void appendMissingStartInfo();
	void appendMissingEndInfo();
	
	//Test Invalid Input for Wrong Date e.g. 30/2, 31/4 and so on 
	void checkFeasibleDate(int day, int month, int year);
	bool isFebThirtieth(int day,int month);
	bool isFebThirtyFirst(int day,int month);
	bool isAprThirtyFirst(int day,int month);
	bool isJunThirtyFirst(int day,int month);
	bool isSepThirtyFirst(int day,int month);
	bool isNovThirtyFirst(int day,int month);
	bool isFebTwentyNinth(int day,int month,int year);
	
	
	string getDescription();
	int getStartTime();
	int getEndTime();
	int getStartDay();
	int getStartMonth();
	int getStartYear();
	int getEndDay();
	int getEndMonth();
	bool getIsValidInput();
	int getEndYear();
	void reset();

	bool isFoundAM(string tempTime);
	bool isFoundPM(string tempTime);
	bool isYear(int tempInt);
	bool isMonth(int tempInt);
	bool isExceedMaximumMonth(int tempInt, bool isValidMonth);
	bool isInputEqualsStandardMonth(string tempTime,int i);


	bool isEverythingMissing(int time,int day,int month,int year);
	bool isTheUnitMissing(int timeUnit);

};

#endif