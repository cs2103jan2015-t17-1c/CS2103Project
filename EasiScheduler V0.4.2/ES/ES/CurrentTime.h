#ifndef CURRENTTIME_H
#define CURRENTTIME_H
#include <iostream>
#include <ctime>

using namespace std;

class CurrentTime{

private:
	int year;
	int month;
	int day;

public:
	CurrentTime(){
	time_t now_time=time(0);
	struct tm *timeinfo;
	timeinfo=localtime(&now_time);

	year = 1900 + timeinfo->tm_year;
	month = 1 + timeinfo->tm_mon;
	day = timeinfo->tm_mday;
	}

	int getYear(){
		return year;
	}

	int getMonth(){
		return month;
	}

	int getDay(){
		return day;
	}

};


#endif