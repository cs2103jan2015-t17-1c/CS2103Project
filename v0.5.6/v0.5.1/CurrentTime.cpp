#include "CurrentTime.h"


CurrentTime::CurrentTime(){
	struct tm *timeinfo;
	time_t now_time=time(0);
	timeinfo=localtime(&now_time);
	
	setYear(timeinfo);
	setMonth(timeinfo);
	setDate(timeinfo);

	}


void CurrentTime::setYear(struct tm *timeinfo){
	year = 1900 + timeinfo->tm_year;

}

void CurrentTime::setMonth(struct tm *timeinfo){
	month = 1 + timeinfo->tm_mon;
}

void CurrentTime::setDate(struct tm *timeinfo){
	day = timeinfo->tm_mday;
}

int CurrentTime::getYear(){
		return year;
	}

int CurrentTime::getMonth(){
		return month;
	}

int CurrentTime::getDay(){
		return day;
	}

