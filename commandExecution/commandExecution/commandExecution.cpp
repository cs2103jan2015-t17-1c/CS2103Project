#include "commandExecution.h"


#define MESSAGE_NORMAL_TASK_ADDED "Successfully added "+taskInfo.description+" from "<<taskInfo.startTime<<" to "<<taskInfo.endTime<<" on "+taskInfo.month+" "<<taskInfo.day<<" to the schedule\n";
#define MESSAGE_UPDATED "The event is updataed to:\n"+taskInfo.description+" from "<<taskInfo.startTime<<" to "<<taskInfo.endTime<<" on "+taskInfo.month+" "<<taskInfo.day<<endl;



CommandExecution::CommandExecution(void) {
	taskInfo.description="";
	taskInfo.month="";
	taskInfo.day=0;
	taskInfo.startTime=0;
	taskInfo.endTime=0;
}


CommandExecution::~CommandExecution(void) {
}

string CommandExecution::readCommand() { 
	string command="";
	cin>> command;
	return inter.interpretCommand(command);
}

CommandExecution::StardardCommand const CommandExecution::determineCommandType(string command){
      
	if (command=="add"){
		return StardardCommand::ADD;
    }
    else if (command=="delete"){
        return StardardCommand::DELETE;
    }
    else if (command=="clear"){
        return StardardCommand::CLEAR;
    }
    else if (command=="display"){
        return StardardCommand::DISPLAY;
    }
    else if (command=="exit"){
        return StardardCommand::EXIT;
    }
    else
        return StardardCommand::INVALID;
}

void CommandExecution::executeCommand(StardardCommand commandType) {
	 switch (commandType) {
        case ADD:{
            performAdd();
            break;
        }
        case DISPLAY:{
            //performDisplay();
            break;
        }
        case DELETE:{
            performDelete();
            break;
        }
        case UPDATE:{
            performUpdate();
			break;
        }
        case EXIT:{
            //performExit();
            break;
        }
        case INVALID:{
            //printMessageifCommandInvalid();
            break;
        } 
        default:
            break;
    }
}

void CommandExecution::performAdd() {
	string content=getContentToBeAdded();
	inter.convert(content); 
	storeInTaskInfo();
	addEventToList();
	printAddResult();
}

string CommandExecution::getContentToBeAdded() {
	string contentToBeAdded="";
	cin.get();
	getline(cin, contentToBeAdded);
	return contentToBeAdded;
}

void CommandExecution::storeInTaskInfo() {
	taskInfo.description=inter.getDescription();
	taskInfo.month=inter.getMonth();
	taskInfo.day=inter.getDay();
	taskInfo.startTime=inter.getStartTime();
	taskInfo.endTime=inter.getEndTime();
}

void CommandExecution::addEventToList() {
	int intMonth=stoi(taskInfo.month.c_str());
	tasks.addTask(taskInfo.description, taskInfo.day, intMonth, taskInfo.startTime, taskInfo.endTime, 2015);
}

void CommandExecution::printAddResult() {
	cout<<MESSAGE_NORMAL_TASK_ADDED;
}

void CommandExecution::performDelete() {
	int index=0;
	cin>>index;
	tasks.deleteTask(index);
	cout<<"deleted"<<endl;
}

void CommandExecution::performUpdate() {
	int index=0;
	cin>>index;
	cin.get();
	string content=getContentToBeAdded();
	inter.convert(content); 
	storeInTaskInfo();
	int intMonth=stoi(taskInfo.month.c_str());
	tasks.updateTask(index, taskInfo.description, taskInfo.day, intMonth, taskInfo.startTime, taskInfo.endTime, 2015); 
	cout<<MESSAGE_UPDATED;
}

void CommandExecution::performDisplay() {
	tasks.displayTasks();
}