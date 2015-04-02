//
//  Header.h
//  Task
//
//  Created by Xu Meng on 10/3/15.
//  Copyright (c) 2015 Xu Meng. All rights reserved.
//

#ifndef Task_h
#define Task_h
#include <string>

using namespace std;

class Task{
private:
    int startTime;
    int endTime;
    string _eventdescription;
    int startDay;
    int startMonth;
    int startYear;
	int endDay;
	int endMonth;
	int endYear;
	int _unit;
	int _mark;

public:
 
    Task(){
        startTime=-1;
        endTime=-1;
        _eventdescription="EMPTY";
        startDay=-1;
        startMonth=-1;
        startYear=-1;
		endDay=-1;
		endMonth=-1;
		endYear=-1;
		_unit=-1;
		_mark=0;
    }
    
	//when mark is given
    Task(string eventdescription,  int starttime, int startday, int startmonth, int startyear, int endtime, int endday, int endmonth, int endyear,int unit, int mark){
        startTime=starttime;
        endTime=endtime;
        _eventdescription=eventdescription;
        startDay=startday;
        startMonth=startmonth;
        startYear=startyear;
		endDay=endday;
		endMonth=endmonth;
		endYear=endyear;
		_unit=unit;
		_mark=mark;

    }
		//when mark is default and is not given
	    Task(string eventdescription,  int starttime, int startday, int startmonth, int startyear, int endtime, int endday, int endmonth, int endyear,int unit){
        startTime=starttime;
        endTime=endtime;
        _eventdescription=eventdescription;
        startDay=startday;
        startMonth=startmonth;
        startYear=startyear;
		endDay=endday;
		endMonth=endmonth;
		endYear=endyear;
		_unit=unit;
		_mark=0;

    }

    


    string getEventInformation(){
        return _eventdescription;
    }
    
    int getEndTime(){
        return endTime;
    }
    
	int getEndDay(){
        return endDay;
    }
    
    int getEndMonth(){
        return endMonth;
    }

    int getEndYear(){
        return endYear;
    }

    int getStartTime(){
        return startTime;
    }
    
    int getStartDay(){
        return startDay;
    }
    
    int getStartMonth(){
        return startMonth;
    }
    int getStartYear(){
        return startYear;
    }
	int getUnit(){
		return _unit;
	}
    int getMark(){
	    return _mark;
	}



    void setEventInformation(string eventdescription){
        _eventdescription = eventdescription;
    }
    
    void setEndTime(int endtime){
        endTime=endtime;
    }
     void setEndDay(int endday){
        endDay=endday;
    }
    
    void setEndMonth(int endmonth){
        endMonth=endmonth;
    }

    void setEndYear(int endyear){
        endYear=endyear;
    }
    void setStartTime(int starttime){
        startTime=starttime;
    }
    
    void setStartDay(int startday){
        startDay=startday;
    }
    
    void setStartMonth(int startmonth){
        startMonth=startmonth;
    }

    void setStartYear(int startyear){
        startYear=startyear;
    }

	void setMark(int mark){
	     _mark=mark;
	}
    void setUnmark(int unmark){
	     _mark=unmark;
	}

    
};





#endif
