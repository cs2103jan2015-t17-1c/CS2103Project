#include <string>
#include <iostream>
#include <sstream>
#include "SmartAdder.h"
#include <stdlib.h>
#include <algorithm>
#include <string>

using namespace std;


const string SmartAdder::STD_MONTH[36]={"january","jan","janu","february","feb","febr","march","mar","marc","april","apr","apri",
    "may","may","may","june","jun","june","july","jul","jul","august","aug","augu","september","sep","sept","october","oct","octo","november","nov","nove", "december","dec","dece"};

SmartAdder::SmartAdder(){
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
	wholeEvent.startTime=-1;
}

void SmartAdder::setDefaultisValidInput(){
    wholeEvent.isValidInput=true;
}
void SmartAdder::setDefaultStartDay(){
	wholeEvent.startDay=-1;
}
void SmartAdder::setDefaultStartMonth(){
	wholeEvent.startMonth=-1;
}
void SmartAdder::setDefaultStartYear(){
	wholeEvent.startYear=-1;
}
void SmartAdder::setDefaultEndTime(){
	wholeEvent.endTime=-1;
}
void SmartAdder::setDefaultEndDay(){
	wholeEvent.endDay=-1;
}
void SmartAdder::setDefaultEndMonth(){
	wholeEvent.endMonth=-1;
}
void SmartAdder::setDefaultEndYear(){
	wholeEvent.endYear=-1;
}
void SmartAdder::setDefaultDescription(){
	 wholeEvent.description="empty event";
}


string SmartAdder::getDescription(){

    return wholeEvent.description;

}



int SmartAdder::getStartTime(){

    return wholeEvent.startTime;

}



int SmartAdder::getStartDay(){

    return wholeEvent.startDay;

}



int SmartAdder::getStartMonth(){

    return wholeEvent.startMonth;

}



int SmartAdder::getStartYear(){

    return wholeEvent.startYear;

}



int SmartAdder::getEndTime(){

    return wholeEvent.endTime;

}



int SmartAdder::getEndDay(){

    return wholeEvent.endDay;

}



int SmartAdder::getEndMonth(){

    return wholeEvent.endMonth;

}



bool SmartAdder::getIsValidInput(){

   return wholeEvent.isValidInput;

}

int SmartAdder::getEndYear(){

    return wholeEvent.endYear;

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



void SmartAdder::setDescription(string line){
	unsigned int starting;
	starting=line.find_first_of("-");
	if(starting != 0){
	    wholeEvent.description=line.substr(0,starting-1);
	}
	if(starting == string::npos){
	    wholeEvent.description=line;
	}
}

void SmartAdder::convert(string line){  	

	setDescription(line);
	setStart(line);
	setEnd(line);
	appendMissingInfo();
	
}

void SmartAdder::setStartYear(int year){
	wholeEvent.startYear=year;
}

void SmartAdder::setStartMonth(int month){
	wholeEvent.startMonth=month;
}
void SmartAdder::setStartTime(int time){
	wholeEvent.startTime=time;
}
void SmartAdder::setStartDay(int day){
	wholeEvent.startDay=day;
}	   


void SmartAdder::setIsValidInput(bool isValid){
	wholeEvent.isValidInput=isValid;

}

void SmartAdder::setStart(string line){
	
	istringstream in(line);
	string tempTime="";
	int tempInt;
	bool isValidMonth=true;

	if (line.find("-st")!= string::npos && line.find("-et") == string::npos){
		setIsValidInput(false);
	}


    if(line.find("-st")!=string::npos){
	    
		while(tempTime.find("-st") == string::npos){
		    in>>tempTime;
		}
		
	   in>>tempTime;
	  
	   while(tempTime!="-et" && getIsValidInput()){
		   
			 if(isFoundAM(tempTime)){
				 tempTime=tempTime.substr(0,4);	
				 setStartTime(atoi(tempTime.c_str()));
			 }else 
				 if(isFoundPM(tempTime)){
					 tempTime=tempTime.substr(0,4);
					 setStartTime(atoi(tempTime.c_str())+1200);
				 }else 
					 if(isdigit(tempTime[0])){	
						 tempInt=atoi(tempTime.c_str());
						 if(isYear(tempInt)){
							 setStartYear(tempInt);
						 }else 
							 if(isMonth(tempInt)){
		   					 setStartDay(tempInt);	    
							 }else{			  
								 setIsValidInput(false);		  
							 }	   
					 }else{		  
						   std::transform(tempTime.begin(), tempTime.end(), tempTime.begin(), ::tolower);
						 for(int i=0;isExceedMaximumMonth(i,isValidMonth);i++){			
							 if(isInputEqualsStandardMonth(tempTime,i)){			
								 setStartMonth(i/3+1);			
								 isValidMonth=false;			
							 }	       
						 }		  
						 if(isValidMonth){		   
							 setIsValidInput(false);	   
						 }
					 }	  	   
			   in>>tempTime;
	   }


	}

	

}



void SmartAdder::setEndYear(int year){
	wholeEvent.endYear=year;
}

void SmartAdder::setEndMonth(int month){
	wholeEvent.endMonth=month;
}
void SmartAdder::setEndTime(int time){
	wholeEvent.endTime=time;
}
void SmartAdder::setEndDay(int day){
	wholeEvent.endDay=day;
}

void SmartAdder::setEnd(string line){
	
	istringstream in(line);
	string tempTime="";
	int tempInt;
	bool isValidMonth=true;
	       
if(line.find("-et")!=string::npos){
	     while(tempTime.find("-et") == string::npos){
		    in>>tempTime;
		}
		if(in.eof()){
			setIsValidInput(false);
		}
		 while(in>>tempTime){	   
			 if(isFoundAM(tempTime))  
			 {
				 tempTime=tempTime.substr(0,4);	
				 setEndTime(atoi(tempTime.c_str()));
			 }else 
				 if(isFoundPM(tempTime)){
					 tempTime=tempTime.substr(0,4);
					 setEndTime(atoi(tempTime.c_str())+1200);
				 }else 
					 if(isdigit(tempTime[0])){	
						 tempInt=atoi(tempTime.c_str());
						 if(isYear(tempInt)){
							 setEndYear(tempInt);
						 }else 
							 if(isMonth(tempInt)){
		   					 setEndDay(tempInt);	    
							 }else{			  
								 setIsValidInput(false);		  
							 }	   
					 }else{		  
						 std::transform(tempTime.begin(), tempTime.end(), tempTime.begin(), ::tolower);
						 for(int i=0;isExceedMaximumMonth(i,isValidMonth);i++){			
							 if(isInputEqualsStandardMonth(tempTime,i)){			
								 setEndMonth(i/3+1);			
								 isValidMonth=false;			
							 }	       
						 
						 
						 }		  
						 if(isValidMonth){		   
							 setIsValidInput(false);	   
						 }
					 }	  
		 }
	  
}
}

bool SmartAdder::isFoundAM(string tempTime){
	if(tempTime.find("am")!=string::npos)  {
		return true;
	}else {
		return false;
	}

}

bool SmartAdder::isFoundPM(string tempTime){
	if(tempTime.find("pm")!=string::npos){
		return true;
	}else {
		return false;
	}
}

bool SmartAdder::isYear(int tempInt){
	if(2100>tempInt && tempInt >1900){
		return true;
	}else{
		return false;
		}
}

bool SmartAdder::isMonth(int tempInt){
	if(0<tempInt && tempInt<32){
		return true;
	}else{
		return false;
	}

}
bool SmartAdder::isExceedMaximumMonth(int month,bool isValidMonth){
	if(month<36 &&isValidMonth){
		return true;
	}else{
		return false;
	}
}
bool SmartAdder::isInputEqualsStandardMonth(string tempTime, int i){
	if (tempTime == STD_MONTH[i]){
		return true;
	}else{
		return false;
}

}
void SmartAdder::appendMissingInfo(){
	
	appendMissingStartInfo();
	checkFeasibleDate(getStartDay(),getStartMonth(),getStartYear());
	appendMissingEndInfo();
	checkFeasibleDate(getEndDay(),getEndMonth(),getEndYear());

}

bool SmartAdder::isEverythingMissing(int time,int day,int month,int year){
	if (time == -1 && day == -1 && month == -1 && year ==-1 ){
		return true;
	}
	else{
		return false;
	}
}

bool SmartAdder::isTheUnitMissing(int valueOfTimeUnit){
	if (valueOfTimeUnit==-1){
		return true;
	}
	else return false;

}

void SmartAdder::checkFeasibleDate(int day, int month, int year){
	 if (isFebThirtieth(day,month)){
		setIsValidInput(false);
	 }
	 if (isFebThirtyFirst(day,month)){
		 setIsValidInput(false);
	 }
	 if (isAprThirtyFirst(day,month)){
		  setIsValidInput(false);
	 }
	 if (isJunThirtyFirst(day,month)){
		 setIsValidInput(false);
	 }
	 if (isSepThirtyFirst(day,month)){
		  setIsValidInput(false);
	 }
	 if (isNovThirtyFirst(day,month)){
		  setIsValidInput(false);
	 }
	 if (isFebTwentyNinth(day,month,year)){
		 setIsValidInput(false);
	 }

}

bool SmartAdder::isFebThirtieth(int day,int month){
		if(month==2&&day==30){
			return true;
		}else{
			return false;
		}
	}

bool SmartAdder::isFebThirtyFirst(int day,int month){
		if(month==2&&day==31){
			return true;
		}else{
			return false;
		}
	}

bool SmartAdder::isAprThirtyFirst(int day,int month){
		if(month==4&&day==31){
			return true;
		}else{
			return false;
		}
	}

bool SmartAdder::isJunThirtyFirst(int day,int month){
		if(month=6&&day==31){
			return true;
		}else{
			return false;
		}
	}
	
bool SmartAdder::isSepThirtyFirst(int day,int month){
		if(month==9 && day==31){
			return true;
		}else{
			return false;
		}
	}

bool SmartAdder::isNovThirtyFirst(int day,int month){
		if(month==11&&day==31){
			return true;
		}else{
			return false;
		}
	}

bool SmartAdder::isFebTwentyNinth(int day,int month,int year){
		if (month == 2 && day== 29 && ((year % 100 == 0 && year % 400 != 0) || (year% 100 != 0 && year % 4 != 0))){
			return true;
		}else{
			return false;
		}
	}


void SmartAdder::appendMissingStartInfo(){

	 CurrentTime timeInfo;
	 if (isEverythingMissing(getStartTime(),getStartDay(),getStartMonth(),getStartYear()) ){	
	 } else {
		 if (isTheUnitMissing(getStartTime())){
			setStartTime(1200);
		}
		 if (isTheUnitMissing(getStartDay())){
			setStartDay(timeInfo.getDay());
		}
		 if (isTheUnitMissing(getStartMonth())){
			setStartMonth(timeInfo.getMonth());
		}
		 if (isTheUnitMissing(getStartYear())){
			setStartYear(timeInfo.getYear());
		}
	 }

	
}


void SmartAdder::appendMissingEndInfo(){
	
	CurrentTime timeInfo;
	
	if (isEverythingMissing(getEndTime(),getEndDay(),getEndMonth(),getEndYear())){	
	}else {
		if (isTheUnitMissing(getEndTime())){
			setEndTime(1200);
		}		
		if (isTheUnitMissing(getEndDay())){
			setEndDay(timeInfo.getDay());
		}
		if (isTheUnitMissing(getEndMonth())){
			setEndMonth(timeInfo.getMonth());
		}
		if (isTheUnitMissing(getEndYear())){
			setEndYear(timeInfo.getYear());
		}
	}
	 
}