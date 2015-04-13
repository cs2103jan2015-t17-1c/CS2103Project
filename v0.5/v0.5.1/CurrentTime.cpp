//@author A0093868J
#include "CurrentTime.h"

#define SYSTEM_DEFAULT_TIME 1900;
#define SYSTEM_DEFAULT_MONTH 1;
CurrentTime::CurrentTime(){
	struct tm *timeinfo;
	time_t now_time = time(0);
	timeinfo = localtime(&now_time);
	
	//set current year, month and date from the computer when CurrentTime is constructed
	setCurrentYear(timeinfo);
	setCurrentMonth(timeinfo);
	setCurrentDate(timeinfo);

}


void CurrentTime::setCurrentYear(struct tm *timeinfo){
	_currentYear =  timeinfo->tm_year + SYSTEM_DEFAULT_TIME;

}

void CurrentTime::setCurrentMonth(struct tm *timeinfo){
	_currentMonth = timeinfo->tm_mon + SYSTEM_DEFAULT_MONTH;
}

void CurrentTime::setCurrentDate(struct tm *timeinfo){
	_currentDay = timeinfo->tm_mday;
}


//get CURRENT year, month and date from the computer
int CurrentTime::getCurrentYear(){
	return _currentYear;
}

int CurrentTime::getCurrentMonth(){
	return _currentMonth;
}

int CurrentTime::getCurrentDay(){
	return _currentDay;
}

