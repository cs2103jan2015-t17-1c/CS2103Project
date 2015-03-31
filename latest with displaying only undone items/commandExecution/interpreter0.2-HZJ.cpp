#include <string>
#include <iostream>
#include <sstream>
#include "interpreter.h"
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

interpreter::interpreter(){
    wholeEvent.day=-1;
    wholeEvent.month="empty";
    wholeEvent.startTime=-1;
    wholeEvent.endTime=-1;
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

int interpreter::getEndTime(){
    return wholeEvent.endTime;
}

int interpreter::getDay(){
    return wholeEvent.day;
}

string interpreter::getMonth(){
    return wholeEvent.month;
}

int interpreter::getIntMonth(){
    for(int i=0;i<12;i++){
        if(wholeEvent.month == STD_MONTH[i]){
            return i+1;
        }
    }
    return 0;
}

void interpreter::convert(string line){
    istringstream in(line);
	int firstChar;
	int lastChar;
    string dummy;
    in>>wholeEvent.month;
    in>>wholeEvent.day;
    if(line.find("-s")!=string::npos)
    {
        in>>dummy;
        in>>wholeEvent.startTime;
    }
    if(line.find("-e")!=string::npos)
    {
        in>>dummy;
        in>>wholeEvent.endTime;
    }
    
    in>>dummy;
    firstChar=line.find(dummy);
	lastChar=line.find_last_not_of(" ");
    wholeEvent.description=line.substr(firstChar,lastChar-firstChar+1);
}
