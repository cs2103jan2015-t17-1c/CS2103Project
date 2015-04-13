
//  EasiStorage.cpp
//  EasiStorage
//
//  Created by wangjiexuan on 31/3/15.
//  Copyright (c) 2015 wang. All rights reserved.
//

//@author A0119426E
#include <iostream>
#include <iomanip>
#include <assert.h>
#include <exception>
#include "EasiStorage.h"


using namespace std;


#define DEFAULT_FILENAME "EasiScheduler.txt";
#define EMPTY_MESSAGE "";

#define TASK_SHOWN_ON_GUI_REMINDER(info) "TODO: " << info << "\r\n";
#define MESSAGE_SCHEDULE_IS_EMPTY "Schedule is empty\r\n";
#define MESSAGE_DISPLAYING_TASKS "Displaying:\r\n";
#define MESSAGE_TRACKING_TASKS "Tracking:\r\n";
#define MESSAGE_NO_MATCH_FOUND "No Match Found in EasiScheduler!\r\n";
#define MESSAGE_NEW_FILE_LOCATION(newLocation) "Changed File Location to " + newLocation + "\r\n";
#define MESSAGE_OVERDUE_TASK(info) "[OD] Event: " + info + "\r\n";
#define MESSAGE_FUTURE_TASK(info) "     Event: " + info + "\r\n";
#define MESSAGE_SCHEDULE_TASK_TIME(unit, startYear, startMonth, startDay, startTime, endYear, endMonth, endDay, endTime) "Unit No." << setfill('0') << setw(4) << unit <<" "<< startYear << "/" << setw(2) << startMonth << "/" << setw(2) << startDay << "/" << setfill('0') << setw(4) << startTime << " - " << endYear << "/" << setw(2) << endMonth << "/" << setw(2 )<< endDay << "/" << setfill('0') << setw(4) << endTime; 
#define MESSAGE_DEADLINE_TASK_TIME(unit, endYear, endMonth, endDay, endTime) "Unit No." << setfill('0') << setw(4) << unit << " ****/**/**/**** - " << endYear << "/" << setw(2) << endMonth << "/" << setw(2) << endDay << "/" << setfill('0') << setw(4) << endTime;
#define MESSAGE_FLOATING_TASK_INFO(unit, info) "Unit No." << setfill('0') << setw(4) << unit << " ****/**/**/**** - ****/**/**/****" << "     Event: " << info << "\r\n"
#define MESSAGE_SEARCH_UNDONE_TASK(info) "     Event: [Undone]" << info << "\r\n";
#define MESSAGE_SEARCH_DONE_TASK(info) "     Event: [Done]" << info << "\r\n";
#define MESSAGE_SEARCH_OVERDUE_UNDONE_TASK(info) "[OD] Event: [Undone]" << info << "\r\n";
#define MESSAGE_SEARCH_OVERDUE_DONE_TASK(info) "[OD] Event: [Done]" << info << "\r\n";
#define MESSAGE_SEARCH_FLOATING_UNDONE_TASK(unit, info)  "Unit No." << setfill('0') << setw(4) << unit << " ****/**/**/**** - ****/**/**/****     Event: [Undone]" << info << "\r\n";
#define MESSAGE_SEARCH_FLOATING_DONE_TASK(unit, info) "Unit No." << setfill('0') << setw(4) << unit << " ****/**/**/**** - ****/**/**/****     Event: [Done]" << info << "\r\n";
#define INDICATOR_EMPTY_INPUT -1;

const char* DEFAULT_LOCATION_FILE = "location.txt";
const char* MESSAGE_EXCEPTION_EXCEED_TOTAL_UNIT = "Congrats, Exceed Maximum Number of Task! Please delete your 'EasiScheduler.txt'";
const int MAXIMUM_TOTAL_UNITS = 9999;

EasiStorage::EasiStorage(){

	
	_isUndoOnce = false;
	_indicatorOfEmptyInput = INDICATOR_EMPTY_INPUT;
    _fileName = DEFAULT_FILENAME;

    
	if (isLocationAvailable(DEFAULT_LOCATION_FILE) ){
        string location;
        _readFile.open(DEFAULT_LOCATION_FILE);
        _readFile >> location;
        SetCurrentDirectoryA(location.c_str());
        _readFile.close();
    }

	
	if(isFileAvailable(_fileName)) {
        _readFile.open(_fileName.c_str());
        string line;
        string dummy;
        int firstChar;
        int lastChar;
        string eventDescription;
        int starttime = INDICATOR_EMPTY_INPUT;
        int endtime = INDICATOR_EMPTY_INPUT;
		int endday = INDICATOR_EMPTY_INPUT;
		int endmonth = INDICATOR_EMPTY_INPUT;
		int endyear = INDICATOR_EMPTY_INPUT;
        int startday = INDICATOR_EMPTY_INPUT;
        int startmonth = INDICATOR_EMPTY_INPUT;
        int startyear = INDICATOR_EMPTY_INPUT;
        int unit = INDICATOR_EMPTY_INPUT;
        int mark = 0;
		int overdue = 0;

		while(getline(_readFile,line)){
			istringstream in(line);
			in >> startyear;
			in >> startmonth;
			in >> startday;
			in >> starttime;
			in >> endyear;
			in >> endmonth;
			in >> endday;
			in >> endtime;
			in >> unit;
			in >> mark;
			in >> overdue;
			in >> dummy;
				
			firstChar = line.find(dummy);
			lastChar = line.find_last_not_of(" ");
			eventDescription = line.substr(firstChar, lastChar - firstChar + 1);
            Task newTask(eventDescription, starttime, startday, startmonth, startyear, endtime, endday, endmonth, endyear, unit, mark,overdue);
            _taskLists.push_back(newTask);
        }   
		
		int tempLargestUnit = 0;				
		for (unsigned int i = 0; isWithinRange(i, _taskLists.size()); i++){
			if(  isWithinRange(tempLargestUnit, _taskLists[i].getUnit())){
				tempLargestUnit = _taskLists[i].getUnit();
			}		
		}	
		_totalUnits = tempLargestUnit; 
		_readFile.close();
	
	} else {
		_totalUnits = 0;
	}
};




//Purpose: To check the existence of the file to save the location
//If exist, then the location of the file is not the default directory, it will return true
//Otherwise, return false;
bool EasiStorage::isLocationAvailable(string fileStoringLocation){
	if (ifstream(fileStoringLocation)){
		return true;
	}
	else {
		return false;
	}
	
}
	
bool EasiStorage::isFileAvailable(string fileName){
	if(ifstream(fileName.c_str())){
		return true;
	} else {
		return false;
	}
}

Task EasiStorage::getTask(int index){
    return  _taskLists[index];
}

void EasiStorage::addTask(string eventDescription, int starttime, int startday, int startmonth, int startyear, int endtime, int endday, int endmonth, int endyear){
	_totalUnits++;
    Task newTask(eventDescription, starttime, startday, startmonth, startyear, endtime, endday, endmonth, endyear,_totalUnits);
    _taskLists.push_back(newTask);
}


void EasiStorage::deleteTask(int index){
	unsigned int i;
    for(i = 0; isWithinRange(i, getListSize()); i++){     
		if(isEqualsIndex(index, _taskLists[i].getUnit())){      
			_taskLists.erase(_taskLists.begin() + i);
		}
    }
}

int EasiStorage::getListSize(){
	return _taskLists.size();
}

bool EasiStorage::isWithinRange(unsigned int index, unsigned int maximumSize){
	if (index < maximumSize){
		return true;
	} else {
		return false;
	}
}

bool EasiStorage::isEqualsIndex(int currentIndex, int targetIndex){
	if (currentIndex == targetIndex){
		return true;
	} else {
		return false;
	}
}
//Purpose: To check the validation of the index and then perform update
bool EasiStorage::isUpdatedTask(int index, string eventDescription, int starttime, int startday, int startmonth,int startyear, int endtime, int endday, int endmonth, int endyear){
    unsigned int i = 0;
	while(isWithinRange(i, _taskLists.size()) && !isEqualsIndex(_taskLists[i].getUnit(), index)){
		i++;
	}
	
	if(isEqualsIndex( i,_taskLists.size())) {
		 return false;
	} else {
		 _taskLists[i].setStartTime(starttime);
		 _taskLists[i].setStartDay(startday);
		 _taskLists[i].setStartMonth(startmonth);
		 _taskLists[i].setStartYear(startyear);
		 _taskLists[i].setEventInformation(eventDescription);
		 _taskLists[i].setEndTime(endtime);
		 _taskLists[i].setEndDay(endday);
		 _taskLists[i].setEndMonth(endmonth);
		 _taskLists[i].setEndYear(endyear);
		 return true;
	}	
}

//Purpose: To display the tasks according to their task types and ending time
string EasiStorage::getDisplayTasks(){
	int SumOfMark = 0;
	unsigned int i = 0;
	ostringstream out;

	if(getListSize() == 0) {
		return MESSAGE_SCHEDULE_IS_EMPTY;
	}
	assert(getListSize() > 0);

	for( i = 0; isWithinRange(i, getListSize()); i++){
		SumOfMark=SumOfMark + _taskLists[i].getMark();
	}

	if(SumOfMark == i){
		return MESSAGE_SCHEDULE_IS_EMPTY;
	}

    out << MESSAGE_DISPLAYING_TASKS;
	setDueStatusIfDayPast();

	for(unsigned i = 0; isWithinRange(i, getListSize()); i++){

		if(isMarkEqualsZero(i)) {
		   if(isScheduleTask(_taskLists[i].getStartYear(), _taskLists[i].getEndYear())){
			   displayScheduleTask(out, _taskLists[i]);
		   } else 
			   if(isDeadlineTask(_taskLists[i].getStartYear(), _taskLists[i].getEndYear())){			   
					displayDeadlineTask(out, _taskLists[i]);
			   } else {
					displayFloatingTask(out, _taskLists[i]);
			   }
		}
	}
	return out.str();

}


bool EasiStorage::isMarkEqualsOne(int indexOfTask){
	if(_taskLists[indexOfTask].getMark() == 1){
		return true;
	} else {
		assert(_taskLists[indexOfTask].getMark() == 0);
		return false;
	}
}

bool EasiStorage::isMarkEqualsZero(int indexOfTask){
	if (_taskLists[indexOfTask].getMark() == 0){
		return true;
	 }else {
		assert(_taskLists[indexOfTask].getMark() == 1);
		return false;
	}
}
bool EasiStorage::isScheduleTask(int startYear, int endYear){
	if(startYear != _indicatorOfEmptyInput && endYear != _indicatorOfEmptyInput){
		return true;
	} else {
		return false;
	}
}
	
bool EasiStorage::isDeadlineTask(int startYear, int endYear){
	if(startYear == _indicatorOfEmptyInput && endYear != _indicatorOfEmptyInput){
		return true;
	} else {
		return false;
	}
}

void EasiStorage::trackScheduleTask(ostringstream &outMessage, int unitIndex){
	outMessage << MESSAGE_SCHEDULE_TASK_TIME(_taskLists[unitIndex].getUnit(), _taskLists[unitIndex].getStartYear(), _taskLists[unitIndex].getStartMonth(), _taskLists[unitIndex].getStartDay(), _taskLists[unitIndex].getStartTime(), _taskLists[unitIndex].getEndYear(), _taskLists[unitIndex].getEndMonth(), _taskLists[unitIndex].getEndDay(), _taskLists[unitIndex].getEndTime());
	outMessage << MESSAGE_FUTURE_TASK(_taskLists[unitIndex].getEventInformation());
}
	
void EasiStorage::trackDeadlineTask(ostringstream &outMessage,int unitIndex){
	outMessage << MESSAGE_DEADLINE_TASK_TIME(_taskLists[unitIndex].getUnit(), _taskLists[unitIndex].getEndYear(), _taskLists[unitIndex].getEndMonth(), _taskLists[unitIndex].getEndDay(), _taskLists[unitIndex].getEndTime());
	outMessage << MESSAGE_FUTURE_TASK(_taskLists[unitIndex].getEventInformation());
}
	
void EasiStorage::trackFloatingTask(ostringstream &outMessage,int unitIndex){
	outMessage << MESSAGE_FLOATING_TASK_INFO(_taskLists[unitIndex].getUnit(), _taskLists[unitIndex].getEventInformation()); 
}


string EasiStorage::getTrackTasks(){
    ostringstream out;
    out << MESSAGE_TRACKING_TASKS;
    for (unsigned i = 0; isWithinRange(i, getListSize()); i++){
		if (isMarkEqualsOne(i)){
		   if(isScheduleTask(_taskLists[i].getStartYear(), _taskLists[i].getEndYear())){           
			   trackScheduleTask(out, i);
		   } else { 
			   if(isDeadlineTask(_taskLists[i].getStartYear(), _taskLists[i].getEndYear())){		   
				   trackDeadlineTask(out, i);
			   } else {
					trackFloatingTask(out, i);	
			   }
		   }
		}
	}
    return out.str();

}

//Purpose: to get the most recent tasks
string EasiStorage::getReadTask(int index){
    ostringstream out;
	if (isWithinRange(index - 1, getListSize())){
		 if(_taskLists[index - 1].getMark() == 0){
			out << TASK_SHOWN_ON_GUI_REMINDER(_taskLists[index - 1].getEventInformation());
		 }
	} else {
		out << EMPTY_MESSAGE;
	}
	return out.str();
}

string EasiStorage::getSearchTask(string content){
    
	vector<Task>::iterator iter;
    string line = EMPTY_MESSAGE;
    ostringstream out;   
	int searchPosition = 1;
    		
	setDueStatusIfDayPast();

	for(iter = _taskLists.begin(); iter != _taskLists.end(); iter++){
        line = (*iter).getEventInformation();
        if(line.find(content) != string::npos) {
			if(isScheduleTask((*iter).getStartYear(), (*iter).getEndYear())){			
				displaySearchedScheduleTask(out, (*iter));
		    } else {
				if(isDeadlineTask((*iter).getStartYear(), (*iter).getEndYear())){
					displaySearchedDeadlineTask(out, (*iter));
				} else {
					displaySearchedFloatingTask(out, (*iter));
				}
			}
			searchPosition++;
		}
    }    
	
	if(isFoundInList(searchPosition)) {
        out << MESSAGE_NO_MATCH_FOUND;
	}
	return out.str();
}

bool EasiStorage::isFoundInList(int searchPosition){
	if(searchPosition == 1){
		return true;
	} else {
		assert(searchPosition != 1);
		return false;
	}
}

bool EasiStorage::isOverDue(Task &task){
	if(task.getOverdue() == 1){
		return true;
	} else {
		assert(task.getOverdue() == 0);
		return false;
	}
}

void EasiStorage::displayDeadlineTask(ostringstream &outMessage, Task &task){
	outMessage << MESSAGE_DEADLINE_TASK_TIME(task.getUnit(), task.getEndYear(), task.getEndMonth(), task.getEndDay(), task.getEndTime());		  				
	if(isOverDue(task)){					
		outMessage << MESSAGE_OVERDUE_TASK(task.getEventInformation());				
	} else {					
		outMessage << MESSAGE_FUTURE_TASK(task.getEventInformation());			
	}
}

void EasiStorage::displayFloatingTask(ostringstream &outMessage, Task &task){
	outMessage << MESSAGE_FLOATING_TASK_INFO(task.getUnit(), task.getEventInformation());
}

void EasiStorage::displayScheduleTask(ostringstream &outMessage, Task &task){
	outMessage << MESSAGE_SCHEDULE_TASK_TIME(task.getUnit(), task.getStartYear(), task.getStartMonth(), task.getStartDay(), task.getStartTime(), task.getEndYear(), task.getEndMonth(), task.getEndDay(), task.getEndTime());
	if(isOverDue(task)){					
		outMessage << MESSAGE_OVERDUE_TASK(task.getEventInformation());		  				
	} else {								
		outMessage << MESSAGE_FUTURE_TASK(task.getEventInformation());				
	}
}

void EasiStorage::displaySearchedDeadlineTask(ostringstream &outMessage, Task &task){
	outMessage << MESSAGE_DEADLINE_TASK_TIME(task.getUnit(), task.getEndYear(), task.getEndMonth(), task.getEndDay(), task.getEndTime());		  				
	
	if (isOverDue(task) && task.getMark() == 0){
		outMessage << MESSAGE_SEARCH_OVERDUE_UNDONE_TASK(task.getEventInformation());
	}
	
	if (!isOverDue(task) && task.getMark() == 0){
		outMessage << MESSAGE_SEARCH_UNDONE_TASK(task.getEventInformation());
	}

	if (isOverDue(task) && task.getMark() == 1){
		outMessage << MESSAGE_SEARCH_OVERDUE_DONE_TASK(task.getEventInformation());
	}
	

	if (!isOverDue(task) && task.getMark() == 1){
		outMessage << MESSAGE_SEARCH_DONE_TASK(task.getEventInformation());
	}
}


void EasiStorage::displaySearchedFloatingTask(ostringstream &outMessage,Task &task){
	 if(task.getMark() == 0){
		 outMessage << MESSAGE_SEARCH_FLOATING_UNDONE_TASK(task.getUnit(), task.getEventInformation());
	 } else {
		assert(task.getMark() == 1);
		outMessage<< MESSAGE_SEARCH_FLOATING_DONE_TASK(task.getUnit(), task.getEventInformation());
	 }
}

void EasiStorage::displaySearchedScheduleTask(ostringstream &outMessage,Task &task){
	outMessage << MESSAGE_SCHEDULE_TASK_TIME(task.getUnit(), task.getStartYear(), task.getStartMonth(), task.getStartDay(), task.getStartTime(), task.getEndYear(), task.getEndMonth(), task.getEndDay(), task.getEndTime());
	if (isOverDue(task) && task.getMark() == 0){
		outMessage << MESSAGE_SEARCH_OVERDUE_UNDONE_TASK(task.getEventInformation());
	}
	
	if (!isOverDue(task) && task.getMark() == 0){
		outMessage << MESSAGE_SEARCH_UNDONE_TASK(task.getEventInformation());
	}

	if (isOverDue(task) && task.getMark() == 1){
		outMessage << MESSAGE_SEARCH_OVERDUE_DONE_TASK(task.getEventInformation());
	}
	

	if (!isOverDue(task) && task.getMark() == 1){
		outMessage << MESSAGE_SEARCH_DONE_TASK(task.getEventInformation());
	}
}

//Purpose: to update the changed information into file
//It will be called when the task list information is changed
void EasiStorage::writeIntoFile(){
    
	vector<Task>::iterator iter;
    string line = EMPTY_MESSAGE;
    
	if (ifstream(_fileName.c_str())){
        remove(_fileName.c_str());
    }
	_writeFile.open(_fileName.c_str());
    
	for(iter = _taskLists.begin(); iter != _taskLists.end(); iter++){
        writeOneTaskToFile(iter);
    }
	_writeFile.close();
}

void EasiStorage::writeOneTaskToFile(vector<Task>::iterator &iter){
	 _writeFile << (*iter).getStartYear() << " " << (*iter).getStartMonth() << " " << (*iter).getStartDay() << " " <<(*iter).getStartTime() <<" "<< (*iter).getEndYear() <<" " << (*iter).getEndMonth()<<" "<< (*iter).getEndDay()<<" " << (*iter).getEndTime() << " " <<(*iter).getUnit()<<" "<<(*iter).getMark()<<" "<< (*iter).getOverdue() <<(*iter).getEventInformation() << "\r\n";
}


string EasiStorage::getChangeFileLocation(string newLocation){
    
	string line = EMPTY_MESSAGE;
    remove(DEFAULT_LOCATION_FILE);
    _writeFile.open(DEFAULT_LOCATION_FILE);
    _writeFile << newLocation;
    _writeFile.close();
    
	
    remove(_fileName.c_str());
    SetCurrentDirectoryA(newLocation.c_str());
    _writeFile.open(_fileName.c_str());
	
	vector<Task>::iterator iter;
    for(iter = _taskLists.begin(); iter != _taskLists.end(); iter++){
        writeOneTaskToFile(iter);
    }
    
	_writeFile.close();
    
	return MESSAGE_NEW_FILE_LOCATION(newLocation);
}

void EasiStorage::copyTaskLists(){
    _previousTaskLists.clear(); 
    for (unsigned int i = 0; isWithinRange(i, getListSize()); i++) {
        _previousTaskLists.push_back(_taskLists[i]);
	}
}

void EasiStorage::undoCommand(){
    vector<Task> temp_taskLists;
    temp_taskLists.clear();
    
    vector<Task> tempPrevious_taskLists;
    tempPrevious_taskLists.clear();
    
    for (unsigned int i = 0; isWithinRange(i, getListSize()); i++) {
        temp_taskLists.push_back(_taskLists[i]);
	}
    for (unsigned int i = 0; isWithinRange(i, _previousTaskLists.size()); i++) {
        tempPrevious_taskLists.push_back(_previousTaskLists[i]);
	}
    _taskLists.clear();
    _previousTaskLists.clear();
       
    for (unsigned int i = 0;isWithinRange(i, temp_taskLists.size()); i++) {
        _previousTaskLists.push_back(temp_taskLists[i]);
	}

    for (unsigned int i = 0; isWithinRange(i, tempPrevious_taskLists.size()); i++) {
        _taskLists.push_back(tempPrevious_taskLists[i]);
	}
}

void EasiStorage::operateExit() {
    exit(0);
}

void EasiStorage::operateMark(int index){
	unsigned int i = 0;
    for(i = 0;isWithinRange(i, _taskLists.size()); i++) {
        if(isEqualsIndex(index, _taskLists[i].getUnit())) {
			_taskLists[i].setMark(1);
		}
	}
}

void EasiStorage::operateUnmark(int index){
	unsigned int i = 0;
	 for( i = 0;isWithinRange(i, _taskLists.size()); i++) {
        if(isEqualsIndex(index, _taskLists[i].getUnit())) {
            _taskLists[i].setUnmark(0);
        }
    }
	
}

bool EasiStorage::isUndoStatus() {
	return _isUndoOnce;
}

void EasiStorage::setUndoStatus(bool status) {
	_isUndoOnce = status;
}

bool EasiStorage::isSortNeeded(int firstEndTime, int secondEndTime) {
	if(firstEndTime == _indicatorOfEmptyInput || (( firstEndTime >secondEndTime) && secondEndTime != _indicatorOfEmptyInput)){
		return true;
	} else {
		return false;
	}
}

//@author A09119454A
//Purpose: to sort all the tasks according to ending time
void EasiStorage::sortTasks() {
    Task tempTask;
	if (getListSize() >= 1 ) {
		for (unsigned int j = 0; isWithinRange(j, getListSize() - 1); j++) {
			for (unsigned int i = 0; isWithinRange(i,getListSize() - 1 - j); i++) {
				if(isSortNeeded(_taskLists[i].getEndTime(), _taskLists[i + 1].getEndTime())) {
					tempTask = _taskLists[i];
					_taskLists[i] = _taskLists[i + 1];
					_taskLists[i + 1] = tempTask;
				}
			}
		}
		for (unsigned int j = 0; isWithinRange(j,getListSize() - 1); j++) {
			for (unsigned int i = 0; isWithinRange(i, getListSize() - 1 - j); i++) {
				if(isSortNeeded(_taskLists[i].getEndDay(), _taskLists[i + 1].getEndDay())) {
					tempTask = _taskLists[i];
					_taskLists[i] = _taskLists[i + 1];
					_taskLists[i + 1] = tempTask;
				}
			}
		}
		for (unsigned int j = 0; isWithinRange(j, getListSize() - 1); j++) {
			for (unsigned int i = 0; isWithinRange(i, getListSize() - 1 - j); i++) {
				if(isSortNeeded(_taskLists[i].getEndMonth(), _taskLists[i + 1].getEndMonth())) {
					tempTask = _taskLists[i];
					_taskLists[i] = _taskLists[i + 1];
					_taskLists[i + 1] = tempTask;
				}
			}
		}

		for (unsigned int j = 0; isWithinRange(j, getListSize() - 1); j++) {
			for (unsigned int i = 0 ; isWithinRange(i, getListSize() - 1 - j); i++) {
				if(isSortNeeded(_taskLists[i].getEndYear(), _taskLists[i + 1].getEndYear())) {
					tempTask = _taskLists[i];
					_taskLists[i] = _taskLists[i + 1];
					_taskLists[i + 1] = tempTask;
				}
			}
		}
	}
}

//Purpose: to set the task as overdue if the ending time is past already
void EasiStorage::setDueStatusIfDayPast() {
	CurrentTime timeInfo;
	for(unsigned int i = 0; isWithinRange(i, getListSize()); i++){
	    if(isDatePast(_taskLists[i].getEndDay(), _taskLists[i].getEndMonth(), _taskLists[i].getEndYear(),timeInfo.getDay(),timeInfo.getMonth(),timeInfo.getYear())){
			_taskLists[i].setOverdue(1);
		} else {
			_taskLists[i].setOverdue(0);
		}
	}
}

bool EasiStorage::isDatePast(int day, int month, int year, int dayCurrent, int monthCurrent, int yearCurrent){
	 if(yearCurrent > year || (yearCurrent == year && monthCurrent > month) || (yearCurrent == year && monthCurrent == month && dayCurrent > day)) {
		 return true; 
	 } else {
		 return false;
	 }
}

void EasiStorage::verifyTotalUnit() {
	if(_totalUnits > MAXIMUM_TOTAL_UNITS) {
		throw new exception(MESSAGE_EXCEPTION_EXCEED_TOTAL_UNIT);
	}
}

int EasiStorage::getTotalUnit() {
	return _totalUnits;
}

bool EasiStorage::isValidIndex(int index){
	for(unsigned int i = 0; i < _taskLists.size(); i++){
		if(index == _taskLists[i].getUnit()) {
			return true;
		}
	}
	return false;
}