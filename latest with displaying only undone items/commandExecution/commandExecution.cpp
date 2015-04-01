#include "commandExecution.h"
using namespace std;

#define MESSAGE_NORMAL_TASK_ADDED "Successfully added 'on " + taskInfo.month + " " << taskInfo.day << " from " << taskInfo.startTime << " to " << taskInfo.endTime << " " + taskInfo.description + "' to the schedule\r\n";
#define MESSAGE_UPDATED "The event is updataed to:\r\n'on " + taskInfo.month + " " << taskInfo.day << " from " << taskInfo.startTime << " to " << taskInfo.endTime << " " + taskInfo.description + "'\r\n";



CommandExecution::CommandExecution(void) {
	_content="";
	taskInfo.description="";
	taskInfo.month="";
	taskInfo.day=0;
	taskInfo.startTime=0;
	taskInfo.endTime=0;
}


CommandExecution::~CommandExecution(void) {
}

string CommandExecution::readCommand(string userInput) { 
	string message="";

	//logging user input
	ofstream log;
	log.open("userInputLogger.txt",ofstream::out | ofstream::app);
	log<<userInput<<endl;

	size_t end=userInput.find_first_of(" ");
	string command=userInput.substr(0, end);
	command=inter.interpretCommand(command);

	if (command == "exit") {
		performExit();
	} else { 
		if (command == "display" || command == "undo" || command == "redo") {
			if(isInvalid(end, userInput)) {
				message = "Wrong error format, plesae refer to user guide\r\n";
				return message;
			} else {
				executeCommand(determineCommandType(command), message);
			}
		} else {
			if(end == string::npos) {
				message = "Wrong error format, plesae refer to user guide\r\n";
				return message;
			} else {
				_content=userInput.substr(end+1, userInput.size()-end);
				executeCommand(determineCommandType(command), message);
			}
		}
	}
	return message;
}

bool CommandExecution::isInvalid(size_t end, string userInput) {
	if(end != string::npos && userInput.find_first_not_of(" ", end) != string:: npos) {
		return true;
	} else {
		return false;
	}
}


CommandExecution::StardardCommand const CommandExecution::determineCommandType(string command){
      
	if (command=="add"){
		return StardardCommand::ADD;
    }
    else if (command=="delete"){
        return StardardCommand::DELET;
    }
    else if (command=="update"){
        return StardardCommand::UPDATE;
    }
    else if (command=="display"){
        return StardardCommand::DISPLAY;
    }
    else if (command=="exit"){
        return StardardCommand::EXIT;
    }
	else if(command=="search"){
	    return StardardCommand::SEARCH;
	}
	else if(command=="location"){
		return StardardCommand::LOCATION;
	}
	else if(command=="undo"){
		return StardardCommand::UNDO;
	}

	else if(command=="redo"){
		return StardardCommand::REDO;
	}

	else if(command=="mark"){
		return StardardCommand::MARK;
	}
    else
        return StardardCommand::INVALID;
}

void CommandExecution::executeCommand(StardardCommand commandType, string& message) {
	 switch (commandType) {
        case ADD:{
            performAdd(message);
			saveInFile();
            break;
        }
        case DISPLAY:{
            performDisplay(message);
            break;
        }
        case DELET:{
            performDelete(message);
			saveInFile();
            break;
        }
        case UPDATE:{
            performUpdate(message);
			saveInFile();
			break;
        }
		case UNDO:{
			performUndo(message);
			saveInFile();
			break;
		}

		case REDO:{
			performRedo(message);
			saveInFile();
			break;
		}
        case EXIT:{
            performExit();
            break;
        }
        case MARK:{
            performMark(message);
            break;
        }
        case INVALID:{
            //printMessageifCommandInvalid();
            break;
        } 
		case SEARCH:{
			performSearch(message);
			break;
		}
		case LOCATION:{
			performLocation(message);
			break;
		}
        default:
            break;
    }
}

void CommandExecution::performAdd(string& message){
	inter.convert(_content); 
	storeInTaskInfo();
	//backup TaskLists
	saveTaskLists();
	addEventToList();
	message=addResult();
}

void CommandExecution::storeInTaskInfo() {
	taskInfo.description=inter.getDescription();
	taskInfo.month=inter.getMonth();
	taskInfo.intMonth=inter.getIntMonth();
	taskInfo.day=inter.getDay();
	taskInfo.startTime=inter.getStartTime();
	taskInfo.endTime=inter.getEndTime();
}

void CommandExecution::addEventToList() {
	tasks.addTask(taskInfo.description, taskInfo.startTime, taskInfo.endTime, taskInfo.day, taskInfo.intMonth, 2015);
	tasks.setUndoStatus(false);
}

string CommandExecution::addResult() {
	ostringstream out;
	out<<MESSAGE_NORMAL_TASK_ADDED;
	return out.str();
}

void CommandExecution::performDelete(string& message) {
	int index=stoi(_content.c_str());
	if(index <1) {
		message = "Invalid index!\r\n"; 
	} else {
		//backup TaskLists
		saveTaskLists();
		tasks.deleteTask(index);
		tasks.setUndoStatus(false);
		message="deleted\r\n";
	}
}

void CommandExecution::performUpdate(string& message) {
	size_t end = _content.find_first_of(" ");
	string indexString = _content.substr(0, end);
	int index = stoi(indexString.c_str());
	_content = _content.substr(end+1, _content.size()-end);
	inter.convert(_content); 
	storeInTaskInfo();
	//backup TaskLists
	saveTaskLists();
	tasks.updateTask(index, taskInfo.description, taskInfo.startTime, taskInfo.endTime, taskInfo.day, taskInfo.intMonth, 2015);
	tasks.setUndoStatus(false);
	ostringstream out;
	out<<MESSAGE_UPDATED;

	message=out.str();
}

void CommandExecution::performDisplay(string& message) {
	message = "All displayed. \r\n";
	message += tasks.displayTasks();
}

void CommandExecution::performSearch(string& message){
	message = tasks.searchTask(_content);
}

void CommandExecution::saveInFile(){
    tasks.writeIntoFile();
}

void CommandExecution::performLocation(string& message){
	message=tasks.changeFileLocation(_content);
}

void CommandExecution::performUndo(string& message){
	if (tasks.getUndoStatus() == true){
		message = message + "Cannot undo twice. \n";
	}
	else {
		tasks.undoCommand();
		tasks.setUndoStatus(true);
		message=message+"Undo is successful \n";  
	}
}

void CommandExecution::performRedo(string& message){
	if (tasks.getUndoStatus() == false){
		message = message + "Cannot redo because no UNDO command has been done. \n";
	}
	else {
		//We temporarily use the same code for redo because it is just swap the tasklists
	    tasks.undoCommand();
		tasks.setUndoStatus(false);
		message=message+"Redo is successful \n";  
	}
}

void CommandExecution::saveTaskLists(){
	tasks.copyTaskLists();
}

void CommandExecution::performExit(){
	tasks.operateExit();
}

void CommandExecution::performMark(string& message){
	int index=stoi(_content.c_str());
    tasks.operateMark(index);
	tasks.setUndoStatus(false);
	message = "Event marked done. \r\n";

}