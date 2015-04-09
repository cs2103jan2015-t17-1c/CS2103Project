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
	setDefaultValidInput();
}

void interpreter::setDefaultStartTime(){
	wholeEvent.startTime=-1;
}

void interpreter::setDefaultValidInput(){
    wholeEvent.validInput=true;
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
	 wholeEvent.description="empty event";
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
	setDefaultValidInput();
}



void interpreter::setDescription(string line){
	unsigned int starting;
	starting=line.find_first_of("-");
	if(starting!=0){
	    wholeEvent.description=line.substr(0,starting-1);
	}
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
	string tempTime="";
	int tempInt;
	bool validMonth=true;

	if (line.find("-st")!= string::npos && line.find("-et") == string::npos){
		wholeEvent.validInput = false;
	}


    if(line.find("-st")!=string::npos){
	    
		while(tempTime!="-st"){
		    in>>tempTime;
		}
		
		
	   in>>tempTime;//1100pm 1 July 2014  cannot be only -st
	  
	   while(tempTime!="-et" && wholeEvent.validInput){
		   
			 if(tempTime.find("am")!=string::npos)  
			 {
				 tempTime=tempTime.substr(0,4);	
				 setStartTime(atoi(tempTime.c_str()));
			 }else 
				 if(tempTime.find("pm")!=string::npos){
					 tempTime=tempTime.substr(0,4);
					 setStartTime(atoi(tempTime.c_str())+1200);
				 }else 
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
	 if (wholeEvent.startTime == -1 && wholeEvent.startDay == -1 && wholeEvent.startMonth == -1 && wholeEvent.startYear ==-1 ){	
	} else {
		if (wholeEvent.startTime == -1){
			wholeEvent.startTime = 1200;
		}
		
		if (wholeEvent.startDay == -1){
			wholeEvent.startDay = timeInfo.getDay();
		}

		if (wholeEvent.startMonth == -1){
			wholeEvent.startMonth = timeInfo.getMonth();
		}

		if (wholeEvent.startYear == -1){
			wholeEvent.startYear = timeInfo.getYear();
		}
	 }

	 //Test Invalid Input for Wrong Date e.g. 30/2, 31/4 and so on 

	 if (wholeEvent.startMonth == 2 && wholeEvent.startDay == 30){
		 wholeEvent.validInput = false;
	 }
	 if (wholeEvent.startMonth == 2 && wholeEvent.startDay == 31){
		 wholeEvent.validInput = false;
	 }
	 if (wholeEvent.startMonth == 4 && wholeEvent.startDay == 31){
		 wholeEvent.validInput = false;
	 }
	 if (wholeEvent.startMonth == 6 && wholeEvent.startDay == 31){
		 wholeEvent.validInput = false;
	 }
	 if (wholeEvent.startMonth == 9 && wholeEvent.startDay == 31){
		 wholeEvent.validInput = false;
	 }
	 if (wholeEvent.startMonth == 11 && wholeEvent.startDay == 31){
		 wholeEvent.validInput = false;
	 }
	 if (wholeEvent.startMonth == 2 && wholeEvent.startDay == 29 && ((wholeEvent.startYear % 100 == 0 && wholeEvent.startYear % 400 != 0) || (wholeEvent.startYear % 100 != 0 && wholeEvent.startYear % 4 != 0))){
		 wholeEvent.validInput = false;
	 }

}

void interpreter::appendMissingEndInfo(){
	
	CurrentTime timeInfo;
	
		 if (wholeEvent.endTime == -1 && wholeEvent.endDay == -1 && wholeEvent.endMonth == -1 && wholeEvent.endYear ==-1 ){	
	} else {
		if (wholeEvent.endTime == -1){
			wholeEvent.endTime = 1200;
		}
		
		if (wholeEvent.endDay == -1){
			wholeEvent.endDay = timeInfo.getDay();
		}

		if (wholeEvent.endMonth == -1){
			wholeEvent.endMonth = timeInfo.getMonth();
		}

		if (wholeEvent.endYear == -1){
			wholeEvent.endYear = timeInfo.getYear();
		}
	}
	 
		 if (wholeEvent.endMonth == 2 && wholeEvent.endDay == 30){
		 wholeEvent.validInput = false;
	 }
	 if (wholeEvent.endMonth == 2 && wholeEvent.endDay == 31){
		 wholeEvent.validInput = false;
	 }
	 if (wholeEvent.endMonth == 4 && wholeEvent.endDay == 31){
		 wholeEvent.validInput = false;
	 }
	 if (wholeEvent.endMonth == 6 && wholeEvent.endDay == 31){
		 wholeEvent.validInput = false;
	 }
	 if (wholeEvent.endMonth == 9 && wholeEvent.endDay == 31){
		 wholeEvent.validInput = false;
	 }
	 if (wholeEvent.endMonth == 11 && wholeEvent.endDay == 31){
		 wholeEvent.validInput = false;
	 }
	 if (wholeEvent.endMonth == 2 && wholeEvent.endDay == 29 && ((wholeEvent.endYear % 100 == 0 && wholeEvent.endYear % 400 != 0) || (wholeEvent.endYear % 100 != 0 && wholeEvent.endYear % 4 != 0))){
		 wholeEvent.validInput = false;
	 }
}