#include <string>
#include <iostream>
#include <sstream>
#include "interpreter.h"
#include <stdlib.h>
#include "CurrentTime.h"
using namespace std;


const string interpreter::COMMAND_ADD[3]={"add","ADD","Add"};
const string interpreter::COMMAND_DELETE[3]={"delete","DELETE","Delete"};
const string interpreter::COMMAND_CLEAR[3]={"clear","Clear","CLEAR"};
const string interpreter::COMMAND_DISPLAY[3]={"Display","display","DISPLAY"};
const string interpreter::COMMAND_UPDATE[3]={"Update","update","UPDATE"};
const string interpreter::COMMAND_SEARCH[3]={"Search","search", "SEARCH"};
const string interpreter::COMMAND_LOCATION[3]={"Location","location","LOCATION"};
const string interpreter::COMMAND_UNDO[3]={"Undo","undo","UNDO"};
const string interpreter::COMMAND_REDO[3]={"Redo","redo","REDO"};
const string interpreter::COMMAND_EXIT[3]={"Exit","exit","EXIT"};
const string interpreter::COMMAND_MARK[3]={"mark","Mark","MARK"};
const string interpreter::COMMAND_TRACK[3]={"track","Track","TRACK"};
const string interpreter::COMMAND_UNMARK[3]={"unmark","Unmark","UNMARK"};
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
    wholeEvent.startTime=-1;
	wholeEvent.startDay=-1;
    wholeEvent.startMonth=-1;
	wholeEvent.startYear=-1;
	wholeEvent.endTime=-1;
	wholeEvent.endDay=-1;
    wholeEvent.endMonth=-1;
	wholeEvent.endYear=-1;
    wholeEvent.description="empty";
}

string interpreter::interpretCommand(string cmd){
    if(checkEachPossibility(COMMAND_ADD,cmd)){
        return STD_ADD;
    }
    else if(checkEachPossibility(COMMAND_DELETE,cmd)){
        return STD_DELETE;
    }
    else if(checkEachPossibility(COMMAND_CLEAR,cmd)){
        return STD_CLEAR;
    }
    
    else if(checkEachPossibility(COMMAND_DISPLAY,cmd))
        return STD_DISPLAY;
    
    else if(checkEachPossibility(COMMAND_UPDATE,cmd))
        return STD_UPDATE;

	else if(checkEachPossibility(COMMAND_SEARCH,cmd))
		return STD_SEARCH;

	else if(checkEachPossibility(COMMAND_LOCATION,cmd))
		return STD_LOCATION;
		
	else if(checkEachPossibility(COMMAND_UNDO,cmd))
		return STD_UNDO;

	else if(checkEachPossibility(COMMAND_REDO,cmd))
		return STD_REDO;
	
	else if(checkEachPossibility(COMMAND_EXIT,cmd))
		return STD_EXIT;

	else if(checkEachPossibility(COMMAND_MARK,cmd))
		return STD_MARK;

	else if(checkEachPossibility(COMMAND_UNMARK,cmd))
		return STD_UNMARK;

	else if(checkEachPossibility(COMMAND_TRACK,cmd))
		return STD_TRACK;

    else
        return "wrong";
}

bool interpreter::checkEachPossibility(const string command[], string cmd){
    for(int i=0;i<3;i++){
        if(command[i]==cmd)
            return true;
    }
    return false;
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

int interpreter::getEndYear(){
    return wholeEvent.endYear;
}

void interpreter::reset(){
    wholeEvent.startTime=-1;
	wholeEvent.startDay=-1;
    wholeEvent.startMonth=-1;
	wholeEvent.startYear=-1;
	wholeEvent.endTime=-1;
	wholeEvent.endDay=-1;
    wholeEvent.endMonth=-1;
	wholeEvent.endYear=-1;
    wholeEvent.description="empty";
}


/*int interpreter::getIntMonth(){
    for(int i=0;i<12;i++){
        if(wholeEvent.month == STD_MONTH[i]){
            return i+1;
        }
    }
    return 0;
}
*/

void interpreter::convert(string line){
    istringstream in(line);
	unsigned int starting;
	string tempTime="";
	int tempInt;
	
	starting=line.find_first_of("-");
	wholeEvent.description=line.substr(0,starting-1);
	
    if(line.find("-st")!=string::npos){
	    while(tempTime!="-st"){
		    in>>tempTime;
		}
		//1100pm 1 July 2014  cannot be only -st
	   in>>tempTime;
	   while(tempTime!="-et"){
	   if(tempTime.find("am")!=string::npos)
	   {
	   tempTime=tempTime.substr(0,4);
	   wholeEvent.startTime=atoi(tempTime.c_str());
	   }
	   else if(tempTime.find("pm")!=string::npos){
	     tempTime=tempTime.substr(0,4);
	     wholeEvent.startTime=atoi(tempTime.c_str())+1200;
	   }
	   else if(isdigit(tempTime[0])){
	   tempInt=atoi(tempTime.c_str());
	      if(tempInt>1900){
	      wholeEvent.startYear=tempInt;
	      }
	      else{
		   wholeEvent.startDay=tempInt;
	      }
	   }
	   else{
		   for(int i=0;i<12;i++){
			if(tempTime == STD_MONTH[i]){
			wholeEvent.startMonth=i+1;
			}
	       }
	   }
	   in>>tempTime;
	   }
	}

       if(line.find("-et")!=string::npos){
	     while(tempTime!="-et"){
		    in>>tempTime;
		}
		//1100pm 1 July 2014
	   while(in>>tempTime){
	   if(tempTime.find("am")!=string::npos)
	   {
	   tempTime=tempTime.substr(0,4);
	   wholeEvent.endTime=atoi(tempTime.c_str());
	   }
	   else if(tempTime.find("pm")!=string::npos){
	   tempTime=tempTime.substr(0,4);
	   wholeEvent.endTime=atoi(tempTime.c_str())+1200;
	   }else 
	   if(isdigit(tempTime[0])){
	      tempInt=atoi(tempTime.c_str());
	      if(tempInt>1900){
	      wholeEvent.endYear=tempInt;
	      }
	      else{
		   wholeEvent.endDay=tempInt;
	      }
	   }
	   else{
		   for(int i=0;i<12;i++){
			if(tempTime == STD_MONTH[i]){
			wholeEvent.endMonth=i+1;
			}
	       }
	   }
	   }
	}
	
	 CurrentTime timeInfo;

	if (wholeEvent.startTime != -1 && wholeEvent.startDay == -1 && wholeEvent.startMonth == -1 && wholeEvent.startYear ==-1){
		wholeEvent.startDay = timeInfo.getDay();
		wholeEvent.startMonth=timeInfo.getMonth();
		wholeEvent.startYear=timeInfo.getYear();
	}

	else if (wholeEvent.startTime != -1 && wholeEvent.startDay != -1 && wholeEvent.startMonth == -1 && wholeEvent.startYear ==-1){
		wholeEvent.startMonth=timeInfo.getMonth();
		wholeEvent.startYear=timeInfo.getYear();
	}

	else if (wholeEvent.startTime != -1 && wholeEvent.startDay != -1 && wholeEvent.startMonth != -1 && wholeEvent.startYear ==-1){
		wholeEvent.startYear=timeInfo.getYear();
	}
	else {
	}

	if (wholeEvent.endTime != -1 && wholeEvent.endDay == -1 && wholeEvent.endMonth == -1 && wholeEvent.endYear ==-1){
		wholeEvent.endDay = timeInfo.getDay();
		wholeEvent.endMonth=timeInfo.getMonth();
		wholeEvent.endYear=timeInfo.getYear();
	}

	else if (wholeEvent.endTime != -1 && wholeEvent.endDay != -1 && wholeEvent.endMonth == -1 && wholeEvent.endYear ==-1){
		wholeEvent.endMonth=timeInfo.getMonth();
		wholeEvent.endYear=timeInfo.getYear();
	}

	else if (wholeEvent.endTime != -1 && wholeEvent.endDay != -1 && wholeEvent.endMonth != -1 && wholeEvent.endYear ==-1){
		wholeEvent.endYear=timeInfo.getYear();
	}
	else {
	}

	

	
}
	   



	