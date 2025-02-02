//@author A09119454A
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <assert.h>
#include "SmartAdder.h"

using namespace std;

#define INDICATOR_EMPTY_INPUT -1;
#define EMPTY_EVENT "empty event";
const int FIRST_CHARACTER_POSITION = 0;
const int MAXIMUM_YEAR = 2500;
const int MINIMUM_YEAR = 1500;
const int MAXIMUM_Day = 31;
const int MINIMUM_Day = 1;

const string INDICATOR_START_INPUT = "-st";
const string INDICATOR_END_INPUT = "-et";
const string INDICAOTR_AM = "am";
const string INDICAOTR_PM = "pm";
const int DEFAULT_TIME = 1200;
const int FEB = 2;
const int APR = 4;
const int JUN = 6;
const int SEP = 9;
const int NOV = 11;
const int DAY29 = 29;
const int DAY30 = 30;
const int DAY31 = 31;



const string SmartAdder::_STD_Month[36]={"january","jan","janu","february","feb","febr","march","mar","marc","april","apr","apri",
    "may","may","may","june","jun","june","july","jul","jul","august","aug","augu","september","sep","sept","october","oct","octo","november","nov","nove", "december","dec","dece"};


SmartAdder::SmartAdder(){
	_indicatorEmptyInput = INDICATOR_EMPTY_INPUT;
    setDefaultStartTime();
	setDefaultStartDay();
    setDefaultStartMonth();
	setDefaultStartYear();
	setDefaultEndTime();
	setDefaultEndDay();
    setDefaultEndMonth();
	setDefaultEndYear();
    setDefaultDescription();
	setDefaultisValidInput();
}

void SmartAdder::setDefaultStartTime(){
	_wholeEvent.startTime = INDICATOR_EMPTY_INPUT;
}

void SmartAdder::setDefaultisValidInput(){
    _wholeEvent.isValidInput = true;
}
void SmartAdder::setDefaultStartDay(){
	_wholeEvent.startDay = INDICATOR_EMPTY_INPUT;
}
void SmartAdder::setDefaultStartMonth(){
	_wholeEvent.startMonth = INDICATOR_EMPTY_INPUT;
}
void SmartAdder::setDefaultStartYear(){
	_wholeEvent.startYear = INDICATOR_EMPTY_INPUT;
}
void SmartAdder::setDefaultEndTime(){
	_wholeEvent.endTime = INDICATOR_EMPTY_INPUT;
}
void SmartAdder::setDefaultEndDay(){
	_wholeEvent.endDay = INDICATOR_EMPTY_INPUT;
}
void SmartAdder::setDefaultEndMonth(){
	_wholeEvent.endMonth = INDICATOR_EMPTY_INPUT;
}
void SmartAdder::setDefaultEndYear(){
	_wholeEvent.endYear = INDICATOR_EMPTY_INPUT;
}

void SmartAdder::setDefaultDescription(){
	 _wholeEvent.description = EMPTY_EVENT;
}


string SmartAdder::getDescription(){

    return _wholeEvent.description;

}



int SmartAdder::getStartTime(){

    return _wholeEvent.startTime;

}



int SmartAdder::getStartDay(){

    return _wholeEvent.startDay;

}



int SmartAdder::getStartMonth(){

    return _wholeEvent.startMonth;

}



int SmartAdder::getStartYear(){

    return _wholeEvent.startYear;

}



int SmartAdder::getEndTime(){

    return _wholeEvent.endTime;

}



int SmartAdder::getEndDay(){

    return _wholeEvent.endDay;

}



int SmartAdder::getEndMonth(){

    return _wholeEvent.endMonth;

}



bool SmartAdder::getIsValidInput(){

   return _wholeEvent.isValidInput;

}

int SmartAdder::getEndYear(){

    return _wholeEvent.endYear;

}

void SmartAdder::reset(){
	setDefaultStartTime();
	setDefaultStartDay();
    setDefaultStartMonth();
	setDefaultStartYear();
	setDefaultEndTime();
	setDefaultEndDay();
    setDefaultEndMonth();
	setDefaultEndYear();
    setDefaultDescription();
	setDefaultisValidInput();
}


//Purpose: to get the description of the event from user input
void SmartAdder::setDescription(string line){
	unsigned int starting = 0;
	starting = line.find_first_of("-");
	if(starting != FIRST_CHARACTER_POSITION){
	    _wholeEvent.description = line.substr(FIRST_CHARACTER_POSITION, starting - 1);
	}
	if(starting == string::npos){
	    _wholeEvent.description = line;
	}
}

//Purpose: To split the string into different component and save it into the corresponding variables
void SmartAdder::convert(string line){  	
	setDescription(line);
	setStart(line);
	setEnd(line);
	appendMissingInfo();	
}

void SmartAdder::setStartYear(int year){
	_wholeEvent.startYear = year;
}

void SmartAdder::setStartMonth(int month){
	_wholeEvent.startMonth = month;
}

void SmartAdder::setStartTime(int time){
	if ( (time>= 1200 && time < 1300) || (time >= 2400 && time < 2500)){
		_wholeEvent.startTime = time - 1200;
	} else {
		_wholeEvent.startTime = time;
	}
}
void SmartAdder::setStartDay(int day){
	_wholeEvent.startDay = day;
}	   


void SmartAdder::setIsValidInput(bool isValid){
	_wholeEvent.isValidInput = isValid;

}

//Purpose: To detect and save any of the ending time component
//standard format: -et 2015 June 2 1100am
void SmartAdder::setEnd(string line){
	string tempTime = "";
	int tempInt = 0;
	bool isValidMonth = true;
	bool isNotTime = true;
	istringstream in(line); 

	
	if(line.find(INDICATOR_END_INPUT) != string::npos) {
		while(tempTime.find(INDICATOR_END_INPUT) == string::npos){
		in >> tempTime;

		}
		if(in.eof()){
			setIsValidInput(false);
		}

		while(in >> tempTime && getIsValidInput()){	   
			setIsValidInput(false);
			if (_wholeEvent.endTime == _indicatorEmptyInput && isFoundAM(tempTime)){
				if (tempTime.find(INDICAOTR_AM) < 5){
					tempTime = tempTime.substr(0, 4);	
					tempInt = atoi(tempTime.c_str());
					if (tempInt >= 100 && tempInt < 1300){ 
					   if(tempInt % 100 < 60){
							setEndTime(tempInt);
							setIsValidInput(true);
						}
					} else {
						isNotTime = false;
					}
					 	
				}
			}

			if (_wholeEvent.endTime == _indicatorEmptyInput && isFoundPM(tempTime)){
				if (tempTime.find(INDICAOTR_PM) < 5){	
					tempTime = tempTime.substr(0, 4);	
					tempInt = atoi(tempTime.c_str());
					if (tempInt >= 100 && tempInt < 1300){ 
					   if(tempInt % 100 < 60){
							setEndTime(tempInt + 1200);
							setIsValidInput(true);
						}
					} else {
						isNotTime = false;
					}
				}
			}

			if(isdigit(tempTime[0]) && isNotTime){	
				tempInt = atoi(tempTime.c_str());

				if (_wholeEvent.endDay == _indicatorEmptyInput && isDay(tempInt)){
					setEndDay(tempInt);
					setIsValidInput(true);
				}

				if (_wholeEvent.endYear == _indicatorEmptyInput && isYear(tempInt)){
					setEndYear(tempInt);
					setIsValidInput(true);
				}
			} else { 
				transform(tempTime.begin(), tempTime.end(), tempTime.begin(), ::tolower);
				for(int i = 0; isExceedMaximumMonth(i, isValidMonth); i++) {			
					if(isInputEqualsStandardMonth(tempTime, i) && _wholeEvent.endMonth == _indicatorEmptyInput){			
						setEndMonth(i / 3 + 1);	
						setIsValidInput(true);
					}
				}
			}
		}  
	}
}

void SmartAdder::setEndYear(int year){
	_wholeEvent.endYear = year;
}

void SmartAdder::setEndMonth(int month){
	_wholeEvent.endMonth = month;
}

void SmartAdder::setEndTime(int time){
	if ( (time >= 1200 && time < 1300) || (time >= 2400 && time < 2500)){
		_wholeEvent.endTime = time - 1200;
	} else {
		_wholeEvent.endTime = time;
	}
}
void SmartAdder::setEndDay(int day){
	_wholeEvent.endDay = day;
}

//Purpose: To get the starting time component
//Standard Format: -st 2015 June 2 1100am
void SmartAdder::setStart(string line){
	
	istringstream in(line);
	string tempTime = "";
	int tempInt = 0;
	bool isValidMonth = true;
	bool isNotTime = true;

	if (line.find(INDICATOR_START_INPUT) != string::npos && line.find(INDICATOR_END_INPUT) == string::npos){
		setIsValidInput(false);
	}


    if(line.find(INDICATOR_START_INPUT) != string::npos){ 
		while(tempTime.find(INDICATOR_START_INPUT) == string::npos){
		    in >> tempTime;
		}
		
		in >> tempTime;
	  
	    while(tempTime != INDICATOR_END_INPUT && getIsValidInput()){
		      setIsValidInput(false);

			  if (_wholeEvent.startTime == _indicatorEmptyInput && isFoundAM(tempTime)){
				  if (tempTime.find(INDICAOTR_AM) < 5){					 
					 tempTime = tempTime.substr(0, 4);	
					 tempInt = atoi(tempTime.c_str());
					 if (tempInt >= 100 && tempInt < 1300){ 
						 if(tempInt % 100 < 60){
							setStartTime(tempInt);
							setIsValidInput(true);
						 }
					 } else {
						 isNotTime = false;
					 }
				  }
			  }

			  if (_wholeEvent.startTime == _indicatorEmptyInput && isFoundPM(tempTime)){
				  if (tempTime.find(INDICAOTR_PM) < 5){
				     tempTime=tempTime.substr(0, 4);	
					 tempInt = atoi(tempTime.c_str());
					 if (tempInt >= 100 && tempInt < 1300){ 
						 if(tempInt % 100 < 60){
							setStartTime(tempInt + 1200);
							setIsValidInput(true);
						 }
					 } else {
						 isNotTime = false;
					 }
				  }
			  } 

			  if(isdigit(tempTime[0]) && isNotTime){	
                  tempInt = atoi(tempTime.c_str());
				  if (_wholeEvent.startDay == _indicatorEmptyInput && isDay(tempInt)){
					 setStartDay(tempInt);
					 setIsValidInput(true);
				  }
				  if (_wholeEvent.startYear == _indicatorEmptyInput && isYear(tempInt)){
					 setStartYear(tempInt);
					 setIsValidInput(true);
				  }
			  } else { 
					transform(tempTime.begin(), tempTime.end(), tempTime.begin(), ::tolower);
				    for(int i = 0; isExceedMaximumMonth(i, isValidMonth); i++){			
						if(isInputEqualsStandardMonth(tempTime, i) && _wholeEvent.startMonth == _indicatorEmptyInput){			
								 setStartMonth(i / 3 + 1);	
								 setIsValidInput(true);
						}
					}
			  }
			  in >> tempTime;
	   }
	}
}

bool SmartAdder::isFoundAM(string tempTime){
	if(tempTime.find(INDICAOTR_AM) != string::npos)  {
		return true;
	} else {
		return false;
	}

}

bool SmartAdder::isFoundPM(string tempTime){
	if(tempTime.find(INDICAOTR_PM) != string::npos){
		return true;
	} else {
		return false;
	}
}


bool SmartAdder::isYear(int tempInt){
	if( tempInt > MINIMUM_YEAR && tempInt < MAXIMUM_YEAR) {
		return true;
	}else {
		return false;
	}
}

bool SmartAdder::isDay(int tempInt) {
	if(MINIMUM_Day <= tempInt && tempInt <= MAXIMUM_Day){
		return true;
	} else {
		return false;
	}

}
bool SmartAdder::isExceedMaximumMonth(int month, bool isValidMonth) {
	if(month < 36 && isValidMonth){
		return true;
	} else {
		return false;
	}
}

bool SmartAdder::isInputEqualsStandardMonth(string tempTime, int i){
	if (tempTime == _STD_Month[i]) {
		return true;
	} else {
		return false;
	}
}

//@author A0093868J
//Purpose: To fill the time component with current time if no user input is found
//If no time is found, it is set to be 0000am
void SmartAdder::appendMissingInfo() {
	appendMissingStartInfo();
	checkFeasibleDate(getStartDay(), getStartMonth(), getStartYear());
	appendMissingEndInfo();
	checkFeasibleDate(getEndDay(), getEndMonth(), getEndYear());
}

//Purpose: To detect which time component the user did not give
bool SmartAdder::isAnythingMissing(int time, int day, int month, int year){
	if (time == _indicatorEmptyInput && day == _indicatorEmptyInput && month == _indicatorEmptyInput && year == _indicatorEmptyInput ) {
		return true;
	} else {
		return false;
	}
}

bool SmartAdder::isTheUnitMissing(int valueOfTimeUnit){
	if (valueOfTimeUnit == _indicatorEmptyInput) {
		return true;
	} else {
		assert(valueOfTimeUnit != _indicatorEmptyInput);
		return false;
	}
}

//Purpose: To check whether the day of month is legal or not
//For example, the largest day of Febuary in 2015 should not be larger than 28
void SmartAdder::checkFeasibleDate(int day, int month, int year){
	 if(isFebThirtieth(day, month)) {
		setIsValidInput(false);
	 }
	 if(isFebThirtyFirst(day, month)) {
		setIsValidInput(false);
	 }
	 if(isAprThirtyFirst(day, month)) {
		 setIsValidInput(false);
	 }
	 if(isJunThirtyFirst(day, month)) {
		 setIsValidInput(false);
	 }
	 if(isSepThirtyFirst(day, month)){
		 setIsValidInput(false);
	 }
	 if(isNovThirtyFirst(day, month)){
		 setIsValidInput(false);
	 }
	 if(isInvalidFebTwentyNinth(day, month, year)) {
		 setIsValidInput(false);
	 }
}

bool SmartAdder::isFebThirtieth(int day, int month){
	if(month == FEB && day == DAY30) {
		return true;
	} else {
		return false;
	}
}

bool SmartAdder::isFebThirtyFirst(int day, int month){
	if(month == FEB && day == DAY31) {
		return true;
	} else {
		return false;
	}
}

bool SmartAdder::isAprThirtyFirst(int day, int month){
	if(month == APR && day == DAY31) {
		return true;
	} else {
		return false;
	}
}

bool SmartAdder::isJunThirtyFirst(int day, int month){
	if(month = JUN && day == DAY31){
		return true;
	} else {
		return false;
	}
}
	
bool SmartAdder::isSepThirtyFirst(int day, int month){
	if(month == SEP && day == DAY31){
		return true;
	} else {
		return false;
	}
}

bool SmartAdder::isNovThirtyFirst(int day,int month){
	if(month == NOV && day == DAY31){
		return true;
	} else {
		return false;
	}
}

bool SmartAdder::isInvalidFebTwentyNinth(int day, int month, int year){
	if (month == FEB && day == DAY29){
		if ( isNormalLeapYear(year) || isSpecialLeapYear(year)){
			return false;
		} else {
			return true;
		}
	} else {
		return false;
	}
}

//Append current time to the missing start time and end time information
void SmartAdder::appendMissingStartInfo(){

	 CurrentTime timeInfo;
	 if(isAnythingMissing(getStartTime(), getStartDay(), getStartMonth(), getStartYear())){	
	 } else {
		if (isTheUnitMissing(getStartTime())){
			setStartTime(DEFAULT_TIME);
		}
		if (isTheUnitMissing(getStartDay())){
			setStartDay(timeInfo.getCurrentDay());
		}
		if (isTheUnitMissing(getStartMonth())){
			setStartMonth(timeInfo.getCurrentMonth());
		}
		if (isTheUnitMissing(getStartYear())){
			setStartYear(timeInfo.getCurrentYear());
		}
	}
}


void SmartAdder::appendMissingEndInfo(){
	
	CurrentTime timeInfo;
	
	if (isAnythingMissing(getEndTime(), getEndDay(), getEndMonth(), getEndYear())){	
	} else {
		if (isTheUnitMissing(getEndTime())){
			setEndTime(DEFAULT_TIME);
		}		
		if (isTheUnitMissing(getEndDay())){
			setEndDay(timeInfo.getCurrentDay());
		}
		if (isTheUnitMissing(getEndMonth())){
			setEndMonth(timeInfo.getCurrentMonth());
		}
		if (isTheUnitMissing(getEndYear())){
			setEndYear(timeInfo.getCurrentYear());
		}
	}	 
}

bool SmartAdder::isEndTimeLaterThanStartTime(){
	if ( _wholeEvent.endYear > _wholeEvent.startYear ){
		return true;
	}

	if ( _wholeEvent.endYear == _wholeEvent.startYear && _wholeEvent.endMonth > _wholeEvent.startMonth ){
		return true;
	}

	if ( _wholeEvent.endYear == _wholeEvent.startYear && _wholeEvent.endMonth == _wholeEvent.startMonth && _wholeEvent.endDay > _wholeEvent.startDay ){
		return true;
	}

	if ( _wholeEvent.endYear == _wholeEvent.startYear && _wholeEvent.endMonth == _wholeEvent.startMonth && _wholeEvent.endDay == _wholeEvent.startDay && _wholeEvent.endTime >= _wholeEvent.startTime ){
		return true;
	}

	return false;
}


bool SmartAdder::isNormalLeapYear(int year){
	return (year % 100 != 0 && year % 4 == 0);
}

//special leap year refers to the year that is a multiple of 100
bool SmartAdder::isSpecialLeapYear(int year){
	return (year % 100 == 0 && year % 400 ==0);
}