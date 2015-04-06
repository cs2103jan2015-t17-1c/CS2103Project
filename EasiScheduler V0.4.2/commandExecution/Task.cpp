#include "Task.h"

Task::Task(){
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

Task::Task(string eventdescription,  int starttime, int startday, int startmonth, int startyear, int endtime, int endday, int endmonth, int endyear,int unit, int mark){
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

Task::Task(string eventdescription,  int starttime, int startday, int startmonth, int startyear, int endtime, int endday, int endmonth, int endyear,int unit){
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

string Task::getEventInformation(){
	return _eventdescription;
}
int Task::getEndTime(){
        return endTime;
    }
    
	
int Task::getEndDay(){
        return endDay;
    }
    
int Task::getEndMonth(){
        return endMonth;
    }

   
int Task::getEndYear(){
        return endYear;
    }
	
int Task::getStartTime(){
        return startTime;
    }
    
    
int Task::getStartDay(){
        return startDay;
    }
    
    
int Task::getStartMonth(){
        return startMonth;
    }
   
int Task::getStartYear(){
        return startYear;
    }
	
int Task::getUnit(){
		return _unit;
	}
    
int Task::getMark(){
	    return _mark;
	}

 void Task::setEventInformation(string eventdescription){
        _eventdescription = eventdescription;
    }
    
   
 void Task::setEndTime(int endtime){
        endTime=endtime;
    }
    
 void Task::setEndDay(int endday){
        endDay=endday;
    }
    
    
 void Task::setEndMonth(int endmonth){
        endMonth=endmonth;
    }

    
 void Task::setEndYear(int endyear){
        endYear=endyear;
    }
   
 void Task::setStartTime(int starttime){
        startTime=starttime;
    }
    
    
 void Task::setStartDay(int startday){
        startDay=startday;
    }
    
    
 void Task::setStartMonth(int startmonth){
        startMonth=startmonth;
    }

    
 void Task::setStartYear(int startyear){
        startYear=startyear;
    }

	
 void Task::setMark(int mark){
	     _mark=mark;
	}
    
 void Task::setUnmark(int unmark){
	     _mark=unmark;
	}
