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
const string interpreter::STD_MONTH[12]={"January","February","March","April",
    "May","June","July","August","September","October","November", "December"};
const string interpreter::STD_ADD="add";
const string interpreter::STD_DELETE="delete";
const string interpreter::STD_CLEAR="clear";
const string interpreter::STD_DISPLAY="display";
const string interpreter::STD_UPDATE="update";

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
    
    in>>wholeEvent.description;
}
