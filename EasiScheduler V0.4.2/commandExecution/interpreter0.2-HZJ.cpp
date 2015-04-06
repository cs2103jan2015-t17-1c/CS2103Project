#include <string>
#include <iostream>
#include <sstream>
#include "interpreter.h"
#include <stdlib.h>
using namespace std;


const string interpreter::STD_MONTH[12]={"January","February","March","April",
    "May","June","July","August","September","October","November", "December"};
const string interpreter::STD_ADD="add";
const string interpreter::STD_DELETE="delete";
const string interpreter::STD_CLEAR="clear";
const string interpreter::STD_DISPLAY="display";
const string interpreter::STD_UPDATE="update";
const string interpreter::STD_SEARCH="search";
const string interpreter::STD_LOCATION="location";
const string interpreter::STD_UNDO="undo";
const string interpreter::STD_REDO="redo";
const string interpreter::STD_EXIT="exit";
const string interpreter::STD_MARK="mark";
const string interpreter::STD_UNMARK="unmark";
const string interpreter::STD_TRACK="track";

interpreter::interpreter(){
    setDefaultStartTime();
	setDefaultStartDay();
    setDefaultStartMonth();
	setDefaultStartYear();
	setDefaultEndTime();
	setDefaultEndDay();
    setDefaultEndMonth();
	setDefaultEndYear();
    setDefaultDescription();
}

void interpreter::setDefaultStartTime(){
	wholeEvent.startTime=-1;
}

void interpreter::setDefaultStartDay(){
	wholeEvent.startDay=-1;
}
void interpreter::setDefaultStartMonth(){
	wholeEvent.startMonth=-1;
}
void interpreter::setDefaultStartYear(){
	wholeEvent.startYear=-1;
}
void interpreter::setDefaultEndTime(){
	wholeEvent.endTime=-1;
}
void interpreter::setDefaultEndDay(){
	wholeEvent.endDay=-1;
}
void interpreter::setDefaultEndMonth(){
	wholeEvent.endMonth=-1;
}
void interpreter::setDefaultEndYear(){
	wholeEvent.endYear=-1;
}
void interpreter::setDefaultDescription(){
	 wholeEvent.description="empty";
}




string interpreter::interpretCommand(string cmd){

    int i=0;
	while(cmd[i]){
		tolower(cmd[i]);
		i++;
	}
	return cmd;

}

string interpreter::getDescription(){

    return wholeEvent.description;

}



int interpreter::getStartTime(){

    return wholeEvent.startTime;

}



int interpreter::getStartDay(){

    return wholeEvent.startDay;

}



int interpreter::getStartMonth(){

    return wholeEvent.startMonth;

}



int interpreter::getStartYear(){

    return wholeEvent.startYear;

}



int interpreter::getEndTime(){

    return wholeEvent.endTime;

}



int interpreter::getEndDay(){

    return wholeEvent.endDay;

}



int interpreter::getEndMonth(){

    return wholeEvent.endMonth;

}



bool interpreter::getvalidInput(){

   return wholeEvent.validInput;

}

int interpreter::getEndYear(){

    return wholeEvent.endYear;

}

void interpreter::reset(){
	setDefaultStartTime();
	setDefaultStartDay();
    setDefaultStartMonth();
	setDefaultStartYear();
	setDefaultEndTime();
	setDefaultEndDay();
    setDefaultEndMonth();
	setDefaultEndYear();
    setDefaultDescription();
}



void interpreter::setDescription(string line){
	unsigned int starting;
	starting=line.find_first_of("-");
	wholeEvent.description=line.substr(0,starting-1);
}

void interpreter::convert(string line){  	

	setDescription(line);
	setStart(line);
	setEnd(line);
	appendMissingInfo();
	
}

void interpreter::setStartYear(int year){
	wholeEvent.startYear=year;
}

void interpreter::setStartMonth(int month){
	wholeEvent.startMonth=month;
}
void interpreter::setStartTime(int time){
	wholeEvent.startTime=time;
}
void interpreter::setStartDay(int day){
	wholeEvent.startDay=day;
}	   

void interpreter::setStart(string line){
	
	istringstream in(line);
	unsigned int starting;
	string tempTime="";
	int tempInt;
	bool validMonth=true;
	starting=line.find_first_of("-");
	
	if(starting!=0){
	wholeEvent.description=line.substr(0,starting-1);
	}

	if(starting==string::npos)
	
    if(line.find("-st")!=string::npos){
	    
		while(tempTime!="-st"){
		    in>>tempTime;
		}
		
		
	   in>>tempTime;//1100pm 1 July 2014  cannot be only -st
	  
	   while(tempTime!="-et"){
		   
		   if(tempTime.find("am")!=string::npos) {
			   tempTime=tempTime.substr(0,4);
			   setStartTime(atoi(tempTime.c_str()));
		   } else 			   
			   if(isdigit(tempTime[0])){	  
				   tempInt=atoi(tempTime.c_str());	      
				   
				   if(2100>tempInt && tempInt >1900){	      
					   setStartYear(tempInt);      
				   }else 
					   if(0<tempInt && tempInt<32){	  
						   setStartDay(tempInt);	      
					   }else{			 
					   wholeEvent.validInput=false;		  
					   }
			   }else{		   
				   for(int i=0;i<12&&validMonth;i++){			
					   if(tempTime == STD_MONTH[i]){			
						   setStartMonth(i+1);			
						   validMonth=false;			
					   }	      
				   }		   
				   if(validMonth){		  
					   wholeEvent.validInput=false;		   
				   }		  	   
			   }	   
			   in>>tempTime;
	   }
	}
}



void interpreter::setEndYear(int year){
	wholeEvent.endYear=year;
}

void interpreter::setEndMonth(int month){
	wholeEvent.endMonth=month;
}
void interpreter::setEndTime(int time){
	wholeEvent.endTime=time;
}
void interpreter::setEndDay(int day){
	wholeEvent.endDay=day;
}

void interpreter::setEnd(string line){
	
	istringstream in(line);
	string tempTime="";
	int tempInt;
	bool validMonth=true;
	       
if(line.find("-et")!=string::npos){
	     while(tempTime!="-et"){
		    in>>tempTime;
		}
		
		 //1100pm 1 July 2014
		 while(in>>tempTime){	   
			 if(tempTime.find("am")!=string::npos)  
			 {
				 tempTime=tempTime.substr(0,4);	
				 setEndTime(atoi(tempTime.c_str()));
			 }else 
				 if(tempTime.find("pm")!=string::npos){
					 tempTime=tempTime.substr(0,4);
					 setEndTime(atoi(tempTime.c_str())+1200);
				 }else 
					 if(isdigit(tempTime[0])){	
						 tempInt=atoi(tempTime.c_str());
						 if(2100>tempInt && tempInt >1900){
							 setEndYear(tempInt);
						 }else 
							 if(0<tempInt && tempInt<32){
		   								 setEndDay(tempInt);	    
							 }else{			  
								 wholeEvent.validInput=false;		  
							 }	   
					 }else{		  
						 for(int i=0;i<12&&validMonth;i++){			
							 if(tempTime == STD_MONTH[i]){			
								 setEndMonth(i+1);			
								 validMonth=false;			
							 }	       
						 }		  
						 if(validMonth){		   
							 wholeEvent.validInput=false;	   
						 }
					 }	  
		 }
	  
}
}


		  
void interpreter::appendMissingInfo(){
	
	appendMissingStartInfo();
	appendMissingEndInfo();

}

void interpreter::appendMissingStartInfo(){
	
	 CurrentTime timeInfo;
	 if (wholeEvent.startTime == -1 && wholeEvent.startDay == -1 && wholeEvent.startMonth == -1 && wholeEvent.startYear ==-1){	
	}else 
		if (wholeEvent.startTime != -1 && wholeEvent.startDay == -1 && wholeEvent.startMonth == -1 && wholeEvent.startYear ==-1){
		wholeEvent.startDay = timeInfo.getDay();
		wholeEvent.startMonth=timeInfo.getMonth();
		wholeEvent.startYear=timeInfo.getYear();
	}else 
		if (wholeEvent.startTime != -1 && wholeEvent.startDay != -1 && wholeEvent.startMonth == -1 && wholeEvent.startYear ==-1){
			wholeEvent.startMonth=timeInfo.getMonth();
			wholeEvent.startYear=timeInfo.getYear();
		}else 
			if (wholeEvent.startTime != -1 && wholeEvent.startDay != -1 && wholeEvent.startMonth != -1 && wholeEvent.startYear ==-1){
				wholeEvent.startYear=timeInfo.getYear();
			}else {
				wholeEvent.validInput=false;
			}

}

void interpreter::appendMissingEndInfo(){
	
	CurrentTime timeInfo;
	
	if (wholeEvent.endTime == -1 && wholeEvent.endDay == -1 && wholeEvent.endMonth == -1 && wholeEvent.endYear ==-1){
	}else 
		if (wholeEvent.endTime != -1 && wholeEvent.endDay == -1 && wholeEvent.endMonth == -1 && wholeEvent.endYear ==-1){
		wholeEvent.endDay = timeInfo.getDay();
		wholeEvent.endMonth=timeInfo.getMonth();
		wholeEvent.endYear=timeInfo.getYear();
		}else 
			if (wholeEvent.endTime != -1 && wholeEvent.endDay != -1 && wholeEvent.endMonth == -1 && wholeEvent.endYear ==-1){
				wholeEvent.endMonth=timeInfo.getMonth();
				wholeEvent.endYear=timeInfo.getYear();
			}else 
				if (wholeEvent.endTime != -1 && wholeEvent.endDay != -1 && wholeEvent.endMonth != -1 && wholeEvent.endYear ==-1){
					wholeEvent.endYear=timeInfo.getYear();
				}else{
					wholeEvent.validInput=false;
				}
}