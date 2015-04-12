#pragma once

#include <iostream>
#include <ctime>

using namespace std;

class CurrentTime{

private:
	int _year;
	int _month;
	int _day;

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


