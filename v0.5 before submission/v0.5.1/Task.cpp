//@Yang Hongjie A0108457B
#include "Task.h"


#define EMPTY_TIME_INPUT -1;
#define EMPTY_EVENT "empty event";
 
Task::Task(){
    _startTime = EMPTY_TIME_INPUT;
    _endTime = EMPTY_TIME_INPUT;
    _eventdescription = EMPTY_EVENT;
    _startDay = EMPTY_TIME_INPUT;
    _startMonth = EMPTY_TIME_INPUT;
    _startYear = EMPTY_TIME_INPUT;
	_endDay = EMPTY_TIME_INPUT;
	_endMonth = EMPTY_TIME_INPUT;
	_endYear = EMPTY_TIME_INPUT;
	_unit = -1;
	_mark = 0;
	_overdue = 0;
}

Task::Task(string eventdescription,  int starttime, int startday, int startmonth, int startyear, int endtime, int endday, int endmonth, int endyear,int unit, int mark,int overdue){
    _startTime = starttime;
    _endTime = endtime;
    _eventdescription = eventdescription;
    _startDay = startday;
    _startMonth = startmonth;
    _startYear = startyear;
	_endDay = endday;
	_endMonth = endmonth;
	_endYear = endyear;
	_unit = unit;
	_mark = mark;
	_overdue = overdue;

}

Task::Task(string eventdescription,  int starttime, int startday, int startmonth, int startyear, int endtime, int endday, int endmonth, int endyear,int unit){
    _startTime = starttime;
    _endTime = endtime;
    _eventdescription = eventdescription;
    _startDay = startday;
    _startMonth = startmonth;
    _startYear = startyear;
	_endDay = endday;
	_endMonth = endmonth;
	_endYear = endyear;
	_unit = unit;
	_mark = 0;
	_overdue = 0;
}

string Task::getEventInformation(){
	return _eventdescription;
}
int Task::getEndTime(){
     return _endTime;
 }
    
	
int Task::getEndDay(){
    return _endDay;
}
    
int Task::getEndMonth(){
    return _endMonth;
}

   
int Task::getEndYear(){
    return _endYear;
}
	
int Task::getStartTime(){
    return _startTime;
}
    
    
int Task::getStartDay(){
    return _startDay;
}
    
    
int Task::getStartMonth(){
    return _startMonth;
}
   
int Task::getStartYear(){
    return _startYear;
}
	
int Task::getUnit(){
	return _unit;
}
    
int Task::getMark(){
	return _mark;
}

int Task::getOverdue(){
	return _overdue;
}

 void Task::setEventInformation(string eventdescription){
    _eventdescription = eventdescription;
}
    
   
 void Task::setEndTime(int endtime){
    _endTime = endtime;
}
    
 void Task::setEndDay(int endday){
    _endDay = endday;
}
    
    
 void Task::setEndMonth(int endmonth){
    _endMonth = endmonth;
}

    
 void Task::setEndYear(int endyear){
    _endYear = endyear;
}
   
 void Task::setStartTime(int starttime){
    _startTime = starttime;
}
    
    
 void Task::setStartDay(int startday){
    _startDay = startday;
}
    
    
 void Task::setStartMonth(int startmonth){
    _startMonth = startmonth;
}

    
 void Task::setStartYear(int startyear){
    _startYear = startyear;
}

	
 void Task::setMark(int mark){
	_mark = mark;
}
    
 void Task::setUnmark(int unmark){
	_mark = unmark;
}

 void Task::setOverdue(int overdue){
     _overdue = overdue;
 }