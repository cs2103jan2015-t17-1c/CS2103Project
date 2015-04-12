
//  storage.cpp
//  storage
//
//  Created by wangjiexuan on 31/3/15.
//  Copyright (c) 2015 wang. All rights reserved.
//
#include <iostream>
#include <iomanip>
#include "Storage.h"


using namespace std;


#define DEFAULT_FILENAME "EasiScheduler.txt";
#define EMPTY_MESSAGE "";
#define TASK_SHOWN_ON_GUI_REMINDER(index,information)  index + ". " + information + "\r\n";
#define MESSAGE_SCHEDULE_IS_EMPTY "Schedule is empty\r\n";
#define MESSAGE_DISPLAYING_TASKS "Displaying:\r\n";
#define MESSAGE_TRACKING_TASKS "Tracking:\r\n";
#define MESSAGE_NO_MATCH_FOUND "No Match Found in EasiScheduler!\r\n";
#define MESSAGE_NEW_FILE_LOCATION(newLocation) "Changed File Location to " + newLocation + "\r\n";




Storage::Storage(){
	bool isUndoOnce = false;

    _fileName = DEFAULT_FILENAME;

    
	if (isLocationAvailable("location.txt") ){
        string location;
        _readFile.open("location.txt");
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
        string eventdescription;
        int starttime = -1;
        int endtime = -1;
		int endday = -1;
		int endmonth = -1;
		int endyear = -1;
        int startday = -1;
        int startmonth = -1;
        int startyear = -1;
        int unit = -1;
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
			eventdescription = line.substr(firstChar, lastChar - firstChar + 1);
            Task newTask(eventdescription, starttime, startday, startmonth, startyear, endtime, endday, endmonth, endyear, unit, mark,overdue);
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





bool Storage::isLocationAvailable(string fileStoringLocation){
	if (ifstream(fileStoringLocation)){
		return true;
	}
	else {
		return false;
	}
	
}
	
bool Storage::isFileAvailable(string fileName){
	if(ifstream(fileName.c_str())){
		return true;
	} else {
		return false;
	}
}

Task Storage::getTask(int index){
    return  _taskLists[index];
}

void Storage::addTask(string eventdescription, int starttime, int startday, int startmonth, int startyear, int endtime, int endday, int endmonth, int endyear){
    _totalUnits++;
    Task newTask(eventdescription, starttime, startday, startmonth, startyear, endtime, endday, endmonth, endyear,_totalUnits);
    _taskLists.push_back(newTask);
}


void Storage::deleteTask(int index){
	unsigned int i;
    for(i = 0; isWithinRange(i, getListSize()); i++){     
		if(isEqualsIndex(index, _taskLists[i].getUnit())){      
			_taskLists.erase(_taskLists.begin() + i);
		}
    }
}

int Storage::getListSize(){
	return _taskLists.size();
}

bool Storage::isWithinRange(unsigned int index, unsigned int maximumSize){
	if (index<maximumSize){
		return true;
	} else {
		return false;
	}
}

bool Storage::isEqualsIndex(int currentIndex, int targetIndex){
	if (currentIndex == targetIndex){
		return true;
	} else {
		return false;
	}
}

bool Storage::isUpdatedTask(int index, string eventdescription, int starttime, int startday, int startmonth,int startyear, int endtime, int endday, int endmonth, int endyear){
    unsigned int i = 0;
	while(isWithinRange( i, _taskLists.size()) && !isEqualsIndex(_taskLists[i].getUnit(),index)){
	i++;
	}
	
	if(isEqualsIndex( i,_taskLists.size())){
	  return false;
	} else {
     _taskLists[i].setStartTime(starttime);
     _taskLists[i].setStartDay(startday);
     _taskLists[i].setStartMonth(startmonth);
     _taskLists[i].setStartYear(startyear);
	 _taskLists[i].setEventInformation(eventdescription);
	 _taskLists[i].setEndTime(endtime);
	 _taskLists[i].setEndDay(endday);
	 _taskLists[i].setEndMonth(endmonth);
	 _taskLists[i].setEndYear(endyear);
	 return true;
	}	
}

// REFACOTR
string Storage::displayTasks(){
	int SumOfMark = 0;
	unsigned  int i = 0;
	ostringstream out;

	if(getListSize() == 0){
		return MESSAGE_SCHEDULE_IS_EMPTY;
	}

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
bool Storage::isMarkEqualsOne(int indexOfTask){
	if(_taskLists[indexOfTask].getMark() == 1){
		return true;
	} else {
		return false;
	}
}

bool Storage::isMarkEqualsZero(int indexOfTask){
	if (_taskLists[indexOfTask].getMark() == 0){
		return true;
	 }else {
		return false;
	}
}
bool Storage::isScheduleTask(int startYear, int endYear){
	if(startYear != -1 && endYear != -1){
		return true;
	} else {
		return false;
	}
}
	
bool Storage::isDeadlineTask(int startYear, int endYear){
	if(startYear == -1 && endYear != -1){
		return true;
	} else {
		return false;
	}
}

void Storage::trackScheduleTask(ostringstream &outMessage, int unitIndex){
	 outMessage << "Unit No." << setfill('0') << setw(4) << _taskLists[unitIndex].getUnit() << " " << _taskLists[unitIndex].getStartYear() << "/" << setw(2) << _taskLists[unitIndex].getStartMonth() << "/" <<setw(2) << _taskLists[unitIndex].getStartDay() << "/" <<  setfill('0') << setw(4) << _taskLists[unitIndex].getStartTime() << " - " << _taskLists[unitIndex].getEndYear() << "/" <<setw(2)<< _taskLists[unitIndex].getEndMonth() << "/" <<setw(2) << _taskLists[unitIndex].getEndDay() << "/" <<  setfill('0') << setw(4) << _taskLists[unitIndex].getEndTime() <<"    " <<" Event: " << _taskLists[unitIndex].getEventInformation() << "\r\n";
}
	
void Storage::trackDeadlineTask(ostringstream &outMessage,int unitIndex){
	outMessage << "Unit No." <<  setfill('0') << setw(4) << _taskLists[unitIndex].getUnit() << " ****/**/**/**** - " << _taskLists[unitIndex].getEndYear() << "/" <<setw(2)<< _taskLists[unitIndex].getEndMonth()<< "/" << setw(2)<< _taskLists[unitIndex].getEndDay() << "/" << setfill('0') << setw(4) << _taskLists[unitIndex].getEndTime() << "    " << " Event: " <<_taskLists[unitIndex].getEventInformation() << "\r\n";
}
	
void Storage::trackFloatingTask(ostringstream &outMessage,int unitIndex){
	outMessage << "Unit No." <<  setfill('0') << setw(4) << _taskLists[unitIndex].getUnit() << " ****/**/**/**** - ****/**/**/****    " << " Event: " << _taskLists[unitIndex].getEventInformation() << "\r\n";
}

// REFACOTR
string Storage::trackTasks(){
    ostringstream out;
    out << MESSAGE_TRACKING_TASKS;
    for (unsigned i = 0; isWithinRange(i, getListSize()); i++){
		if (isMarkEqualsOne(i)){
		   if(isScheduleTask(_taskLists[i].getStartYear(), _taskLists[i].getEndYear())){           
			   trackScheduleTask(out, i);
		   }else 
			   if(isDeadlineTask(_taskLists[i].getStartYear(), _taskLists[i].getEndYear())){		   
				   trackDeadlineTask(out, i);
			   } else {
			   trackFloatingTask(out, i);	
		   }
		}
    }
   return out.str();

}

string Storage::readTask(int index){
    ostringstream out;
	if (isWithinRange(index -1, _totalUnits) && _taskLists[index-1].getMark() == 0){
		out << TASK_SHOWN_ON_GUI_REMINDER(index,_taskLists[index - 1].getEventInformation());
	}else 
		out << EMPTY_MESSAGE;
	return out.str();
}

// REFACOTR
string Storage::searchTask(string content){
    
	vector<Task>::iterator iter;
    string line = EMPTY_MESSAGE;
    ostringstream out;   
	int searchPosition = 1;
    		

	for(iter = _taskLists.begin(); iter != _taskLists.end(); iter++){
        line = (*iter).getEventInformation();
        if(line.find(content) != string::npos) {
			if(isScheduleTask((*iter).getStartYear(),(*iter).getEndYear())){			
				displaySearchedScheduleTask(out,(*iter));
		    } else 
				if(isDeadlineTask((*iter).getStartYear(), (*iter).getEndYear())){
				displaySearchedDeadlineTask(out, (*iter));
				} else {
				displaySearchedFloatingTask(out, (*iter));
				}
		   searchPosition++;
        }
    }    
	
	if(isFoundInList(searchPosition)){
        out << MESSAGE_NO_MATCH_FOUND;
	}
	return out.str();
}

bool Storage::isFoundInList(int searchPosition){
	if(searchPosition == 1){
		return true;
	} else {
		return false;
	}
}

bool Storage::isOverDue(Task &task){
	if(task.getOverdue() == 1){
		return true;
	} else {
		return false;
	}
}

void Storage::displayDeadlineTask(ostringstream &outMessage, Task &task){
	outMessage << "Unit No." <<  setfill('0') << setw(4) << task.getUnit() << " ****/**/**/**** - " << task.getEndYear() << "/" << setw(2) << task.getEndMonth() << "/" << setw(2) << task.getEndDay() << "/" << setfill('0') << setw(4) << task.getEndTime();		  				
	if(isOverDue(task)){					
		outMessage << "[OD]" << " Event: " << task.getEventInformation() << "\r\n";				
	} else {					
		outMessage << "    " << " Event: " << task.getEventInformation() << "\r\n";				
	}
}

void Storage::displayFloatingTask(ostringstream &outMessage, Task &task){
	outMessage << "Unit No." <<  setfill('0') << setw(4) << task.getUnit() << " ****/**/**/**** - ****/**/**/****" << "    " << " Event: " << task.getEventInformation() << "\r\n";
}

void Storage::displayScheduleTask(ostringstream &outMessage, Task &task){
	outMessage << "Unit No." << setfill('0') << setw(4)<<task.getUnit() << " " << task.getStartYear() << "/" << setw(2) << task.getStartMonth() << "/" << setw(2) << task.getStartDay() << "/" << setfill('0') << setw(4) << task.getStartTime() << " - " << task.getEndYear() << "/" << setw(2) << task.getEndMonth() << "/" << setw(2) << task.getEndDay() << "/" <<  setfill('0') << setw(4) << task.getEndTime() ;
	if(isOverDue(task)){					
		outMessage << "[OD]" << " Event: " << task.getEventInformation() << "\r\n";		  				
	} else {								
		outMessage << "    " << " Event: " << task.getEventInformation() << "\r\n";				
	}
}

void Storage::displaySearchedDeadlineTask(ostringstream &outMessage, Task &task){
	outMessage << "Unit No." << setfill('0') << setw(4) << task.getUnit() << " ****/**/**/**** - " << task.getEndYear() << "/" << setw(2) << task.getEndMonth() << "/" << setw(2) << task.getEndDay() << "/" << setfill('0') << setw(4) << task.getEndTime();		  				
	if(isOverDue(task)){					
		outMessage << "[OD]"<<" Event: " << task.getEventInformation();				
	} else {					
		outMessage << "    "<< " Event: " << task.getEventInformation();			
	}

	if(task.getMark() == 0){
		outMessage << "[Undone]" << "\r\n";
	} else {
		outMessage << "[Done]" << "\r\n";
	}
}


void Storage::displaySearchedFloatingTask(ostringstream &outMessage,Task &task){
	 outMessage<< "Unit No." <<  setfill('0') << setw(4)<<task.getUnit()<<" ****/**/**/**** - ****/**/**/****" <<"    "<<" Event: " <<  task.getEventInformation() << "\r\n";
}

void Storage::displaySearchedScheduleTask(ostringstream &outMessage,Task &task){
	outMessage<< "Unit No." << setfill('0')<<setw(4)<<task.getUnit()<<" "<< task.getStartYear() << "/" <<setw(2)<<task.getStartMonth() << "/" <<setw(2)<<task.getStartDay() << "/" <<  setfill('0') << setw(4) << task.getStartTime() <<" - " << task.getEndYear() << "/" <<setw(2)<<task.getEndMonth()<< "/" <<setw(2)<< task.getEndDay() << "/" <<  setfill('0') << setw(4) << task.getEndTime() ;
	if(isOverDue(task)){					
		outMessage << "[OD]"<<" Event: " << task.getEventInformation();		  				
	} else {								
		outMessage << "    "<<" Event: " <<task.getEventInformation();				
	}

	if(task.getMark() == 0){
		outMessage << "[Undone]\r\n";
	} else {
		outMessage << "[Done]\r\n";
	}
}

void Storage::writeIntoFile(){
    
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

void Storage::writeOneTaskToFile(vector<Task>::iterator &iter){
	 _writeFile << (*iter).getStartYear() <<" " << (*iter).getStartMonth()<<" "<< (*iter).getStartDay() << " " <<(*iter).getStartTime() <<" "<< (*iter).getEndYear() <<" " << (*iter).getEndMonth()<<" "<< (*iter).getEndDay()<<" " << (*iter).getEndTime() << " " <<(*iter).getUnit()<<" "<<(*iter).getMark()<<" "<< (*iter).getOverdue() <<(*iter).getEventInformation() << "\r\n";
}


string Storage::changeFileLocation(string newLocation){
    
	string line = EMPTY_MESSAGE;
    remove("location.txt");
    _writeFile.open("location.txt");
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

void Storage::copyTaskLists(){
    _previousTaskLists.clear(); 
    for (unsigned int i = 0; isWithinRange(i, getListSize()); i++) {
        _previousTaskLists.push_back(_taskLists[i]);
	}
}

void Storage::undoCommand(){
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

void Storage::operateExit() {
    exit(0);
}

void Storage::operateMark(int index){
	unsigned int i = 0;
    for(i = 0;isWithinRange(i, _taskLists.size()); i++) {
        if(isEqualsIndex(index, _taskLists[i].getUnit())) {
			_taskLists[i].setMark(1);
		}
	}
}

void Storage::operateUnmark(int index){
	unsigned int i = 0;
	 for( i = 0;isWithinRange(i, _taskLists.size()); i++) {
        if(isEqualsIndex(index, _taskLists[i].getUnit())) {
            _taskLists[i].setUnmark(0);
        }
    }
	
}

bool Storage::getIsUndoStatus() {
	return _isUndoOnce;
}

void Storage::setUndoStatus(bool status) {
	_isUndoOnce = status;
}

bool Storage::isSortNeeded(int firstEndTime, int secondEndTime) {
	if(firstEndTime == -1 || (( firstEndTime >secondEndTime) && secondEndTime != -1)){
		return true;
	} else {
		return false;
	}
}

void Storage::sortTasks() {
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

void Storage::setDueStatusIfDayPast() {
	CurrentTime timeInfo;
	for(unsigned int i = 0; isWithinRange(i, getListSize()); i++){
	    if(isDatePast(_taskLists[i].getEndDay(), _taskLists[i].getEndMonth(), _taskLists[i].getEndYear(),timeInfo.getDay(),timeInfo.getMonth(),timeInfo.getYear())){
			_taskLists[i].setOverdue(1);
		} else {
			_taskLists[i].setOverdue(0);
		}
	}
}

bool Storage::isDatePast(int day, int month, int year, int dayCurrent, int monthCurrent, int yearCurrent){
	 if(yearCurrent > year || (yearCurrent == year && monthCurrent > month) || (yearCurrent == year && monthCurrent == month && dayCurrent > day)) {
		 return true; 
	 } else {
		 return false;
	 }
}


//function added for unit testing
int Storage::getSize() {
	return _taskLists.size();
}

bool Storage::isValidIndex(int index){
	for(unsigned int i = 0; i < _taskLists.size(); i++){
		if(index == _taskLists[i].getUnit()) {
			return true;
		}
	}
	return false;
}