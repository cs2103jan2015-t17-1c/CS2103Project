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
	CurrentTime();
	//setter methods
	void setYear(struct tm *timeinfo);
	void setMonth(struct tm *timeinfo);
	void setDate(struct tm *timeinfo);

	//getter methods
	int getYear();
	int getMonth();
	int getDay();

};


#endif