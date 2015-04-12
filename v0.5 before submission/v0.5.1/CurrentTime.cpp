//@author A0093868J
#include "CurrentTime.h"


CurrentTime::CurrentTime(){
	struct tm *timeinfo;
	time_t now_time = time(0);
	timeinfo = localtime(&now_time);
	
	setYear(timeinfo);
	setMonth(timeinfo);
	setDate(timeinfo);

}


void CurrentTime::setYear(struct tm *timeinfo){
	_year = 1900 + timeinfo->tm_year;

}

void CurrentTime::setMonth(struct tm *timeinfo){
	_month = 1 + timeinfo->tm_mon;
}

void CurrentTime::setDate(struct tm *timeinfo){
	_day = timeinfo->tm_mday;
}

int CurrentTime::getYear(){
	return _year;
}

int CurrentTime::getMonth(){
	return _month;
}

int CurrentTime::getDay(){
	return _day;
}

