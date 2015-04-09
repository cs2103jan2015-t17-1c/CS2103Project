#include <string>
#include <iostream>
#include <sstream>
#include "Interpreter.h"
#include <stdlib.h>
using namespace std;


const string Interpreter::STD_MONTH[12]={"January","February","March","April",
    "May","June","July","August","September","October","November", "December"};
const string Interpreter::STD_ADD="add";
const string Interpreter::STD_DELETE="delete";
const string Interpreter::STD_CLEAR="clear";
const string Interpreter::STD_DISPLAY="display";
const string Interpreter::STD_UPDATE="update";
const string Interpreter::STD_SEARCH="search";
const string Interpreter::STD_LOCATION="location";
const string Interpreter::STD_UNDO="undo";
const string Interpreter::STD_REDO="redo";
const string Interpreter::STD_EXIT="exit";
const string Interpreter::STD_MARK="mark";
const string Interpreter::STD_UNMARK="unmark";
const string Interpreter::STD_TRACK="track";

Interpreter::Interpreter(){
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

void Interpreter::setDefaultStartTime(){
	wholeEvent.startTime=-1;
}

void Interpreter::setDefaultisValidInput(){
    wholeEvent.isValidInput=true;
}
void Interpreter::setDefaultStartDay(){
	wholeEvent.startDay=-1;
}
void Interpreter::setDefaultStartMonth(){
	wholeEvent.startMonth=-1;
}
void Interpreter::setDefaultStartYear(){
	wholeEvent.startYear=-1;
}
void Interpreter::setDefaultEndTime(){
	wholeEvent.endTime=-1;
}
void Interpreter::setDefaultEndDay(){
	wholeEvent.endDay=-1;
}
void Interpreter::setDefaultEndMonth(){
	wholeEvent.endMonth=-1;
}
void Interpreter::setDefaultEndYear(){
	wholeEvent.endYear=-1;
}
void Interpreter::setDefaultDescription(){
	 wholeEvent.description="empty event";
}




string Interpreter::interpretCommand(string cmd){

    int i=0;
	while(cmd[i]){
		tolower(cmd[i]);
		i++;
	}
	return cmd;

}

string Interpreter::getDescription(){

    return wholeEvent.description;

}



int Interpreter::getStartTime(){

    return wholeEvent.startTime;

}



int Interpreter::getStartDay(){

    return wholeEvent.startDay;

}



int Interpreter::getStartMonth(){

    return wholeEvent.startMonth;

}



int Interpreter::getStartYear(){

    return wholeEvent.startYear;

}



int Interpreter::getEndTime(){

    return wholeEvent.endTime;

}



int Interpreter::getEndDay(){

    return wholeEvent.endDay;

}



int Interpreter::getEndMonth(){

    return wholeEvent.endMonth;

}



bool Interpreter::getIsValidInput(){

   return wholeEvent.isValidInput;

}

int Interpreter::getEndYear(){

    return wholeEvent.endYear;

}

void Interpreter::reset(){
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



void Interpreter::setDescription(string line){
	unsigned int starting;
	starting=line.find_first_of("-");
	if(starting != 0){
	    wholeEvent.description=line.substr(0,starting-1);
	}
	if(starting == string::npos){
	    wholeEvent.description=line;
	}
}

void Interpreter::convert(string line){  	

	setDescription(line);
	setStart(line);
	setEnd(line);
	appendMissingInfo();
	
}

void Interpreter::setStartYear(int year){
	wholeEvent.startYear=year;
}

void Interpreter::setStartMonth(int month){
	wholeEvent.startMonth=month;
}
void Interpreter::setStartTime(int time){
	wholeEvent.startTime=time;
}
void Interpreter::setStartDay(int day){
	wholeEvent.startDay=day;
}	   


void Interpreter::setIsValidInput(bool isValid){
	wholeEvent.isValidInput=isValid;

}

void Interpreter::setStart(string line){
	
	istringstream in(line);
	string tempTime="";
	int tempInt;
	bool isValidMonth=true;

	if (line.find("-st")!= string::npos && line.find("-et") == string::npos){
		setIsValidInput(false);
	}


    if(line.find("-st")!=string::npos){
	    
		while(tempTime!="-st"){
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
						 for(int i=0;isExceedMaximumMonth(i,isValidMonth);i++){			
							 if(isInputEqualsStandardMonth(tempTime,i)){			
								 setStartMonth(i+1);			
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



void Interpreter::setEndYear(int year){
	wholeEvent.endYear=year;
}

void Interpreter::setEndMonth(int month){
	wholeEvent.endMonth=month;
}
void Interpreter::setEndTime(int time){
	wholeEvent.endTime=time;
}
void Interpreter::setEndDay(int day){
	wholeEvent.endDay=day;
}

void Interpreter::setEnd(string line){
	
	istringstream in(line);
	string tempTime="";
	int tempInt;
	bool isValidMonth=true;
	       
if(line.find("-et")!=string::npos){
	     while(tempTime!="-et"){
		    in>>tempTime;
		}
		if(in.eof()){
			setIsValidInput(false);
		}
		 //1100pm 1 July 2014
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
						 for(int i=0;isExceedMaximumMonth(i,isValidMonth);i++){			
							 if(isInputEqualsStandardMonth(tempTime,i)){			
								 setEndMonth(i+1);			
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

bool Interpreter::isFoundAM(string tempTime){
	if(tempTime.find("am")!=string::npos)  {
		return true;
	}else {
		return false;
	}

}

bool Interpreter::isFoundPM(string tempTime){
	if(tempTime.find("pm")!=string::npos){
		return true;
	}else {
		return false;
	}
}

bool Interpreter::isYear(int tempInt){
	if(2100>tempInt && tempInt >1900){
		return true;
	}else{
		return false;
		}
}

bool Interpreter::isMonth(int tempInt){
	if(0<tempInt && tempInt<32){
		return true;
	}else{
		return false;
	}

}
bool Interpreter::isExceedMaximumMonth(int month,bool isValidMonth){
	if(month<12 &&isValidMonth){
		return true;
	}else{
		return false;
	}
}
bool Interpreter::isInputEqualsStandardMonth(string tempTime, int i){
	if (tempTime == STD_MONTH[i]){
		return true;
	}else{
		return false;
}

}
void Interpreter::appendMissingInfo(){
	
	appendMissingStartInfo();
	checkFeasibleDate(getStartDay(),getStartMonth(),getStartYear());
	appendMissingEndInfo();
	checkFeasibleDate(getEndDay(),getEndMonth(),getEndYear());

}

bool Interpreter::isEverythingMissing(int time,int day,int month,int year){
	if (time == -1 && day == -1 && month == -1 && year ==-1 ){
		return true;
	}
	else{
		return false;
	}
}

bool Interpreter::isTheUnitMissing(int valueOfTimeUnit){
	if (valueOfTimeUnit==-1){
		return true;
	}
	else return false;

}

void Interpreter::checkFeasibleDate(int day, int month, int year){
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

bool Interpreter::isFebThirtieth(int day,int month){
		if(month==2&&day==30){
			return true;
		}else{
			return false;
		}
	}

bool Interpreter::isFebThirtyFirst(int day,int month){
		if(month==2&&day==31){
			return true;
		}else{
			return false;
		}
	}

bool Interpreter::isAprThirtyFirst(int day,int month){
		if(month==4&&day==31){
			return true;
		}else{
			return false;
		}
	}

bool Interpreter::isJunThirtyFirst(int day,int month){
		if(month=6&&day==31){
			return true;
		}else{
			return false;
		}
	}
	
bool Interpreter::isSepThirtyFirst(int day,int month){
		if(month==9 && day==31){
			return true;
		}else{
			return false;
		}
	}

bool Interpreter::isNovThirtyFirst(int day,int month){
		if(month==11&&day==31){
			return true;
		}else{
			return false;
		}
	}

bool Interpreter::isFebTwentyNinth(int day,int month,int year){
		if (month == 2 && day== 29 && ((year % 100 == 0 && year % 400 != 0) || (year% 100 != 0 && year % 4 != 0))){
			return true;
		}else{
			return false;
		}
	}


void Interpreter::appendMissingStartInfo(){

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


void Interpreter::appendMissingEndInfo(){
	
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