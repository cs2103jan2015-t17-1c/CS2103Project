#pragma once
//@author A0093868J
#include <iostream>
#include <ctime>

using namespace std;
// This function is used to get current time information
class CurrentTime{

private:
	int _currentYear;
	int _currentMonth;
	int _currentDay;

public:
	CurrentTime();
	//setter methods
	void setCurrentYear(struct tm *timeinfo);
	void setCurrentMonth(struct tm *timeinfo);
	void setCurrentDate(struct tm *timeinfo);

	//getter methods
	int getCurrentYear();
	int getCurrentMonth();
	int getCurrentDay();

};


