//
//  Header.h
//  Task
//
//  Created by Xu Meng on 10/3/15.
//  Copyright (c) 2015 Xu Meng. All rights reserved.
//

#pragma once

#include <string>

using namespace std;
//@author A0108457B
class Task{
private:

    int _startTime;
    int _endTime;
    string _eventdescription;
    int _startDay;
    int _startMonth;
    int _startYear;
	int _endDay;
	int _endMonth;
	int _endYear;
	int _unit;
	int _mark;
	int _overdue;

public:
 
    Task();
    
	//when mark is given
    Task(string eventdescription,  int starttime, int startday, int startmonth, int startyear, int endtime, int endday, int endmonth, int endyear,int unit, int mark, int overdue);
	
	//when mark is default and is not given	   
	Task(string eventdescription,  int starttime, int startday, int startmonth, int startyear, int endtime, int endday, int endmonth, int endyear,int unit);

    string getEventInformation();
    int getEndTime();    
	int getEndDay();  
    int getEndMonth();
    int getEndYear();
    int getStartTime();    
    int getStartDay();    
    int getStartMonth();
    int getStartYear();
	int getUnit();
    int getMark();
	int getOverdue();


    void setEventInformation(string eventdescription);
    void setEndTime(int endtime);
    void setEndDay(int endday);
    void setEndMonth(int endmonth);
    void setEndYear(int endyear);
    void setStartTime(int starttime);
    void setStartDay(int startday);
    void setStartMonth(int startmonth);
    void setStartYear(int startyear);
	void setMark(int mark);
    void setUnmark(int unmark);
	void setOverdue(int overdue);

    
};



