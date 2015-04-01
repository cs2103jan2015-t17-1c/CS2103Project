#include "commandExecution.h"
using namespace std;

#define MESSAGE_NORMAL_TASK_ADDED "Successfully added 'on " + _taskInfo.month + " " << _taskInfo.day << " from " << _taskInfo.startTime << " to " << _taskInfo.endTime << " " + _taskInfo.description + "' to the schedule\r\n";
#define MESSAGE_UPDATED "The event is updataed to:\r\n'on " + _taskInfo.month + " " << _taskInfo.day << " from " << _taskInfo.startTime << " to " << _taskInfo.endTime << " " + _taskInfo.description + "'\r\n";
#define MESSAGE_DEADLINE_TASK_ADDED "Successfully added 'on " + _taskInfo.month + " " << _taskInfo.day << " before " << _taskInfo.endTime << " " + _taskInfo.description + "' to the schedule\r\n";
#define MESSAGE_FLOATING_TASK_ADDED "Successfully added 'on " + _taskInfo.month + " " << _taskInfo.day << " " + _taskInfo.description + "' to the schedule\r\n";

CommandExecution::CommandExecution(void) {
	_content="";
	_taskInfo.description="";
	_taskInfo.month="";
	_taskInfo.day=0;
	_taskInfo.startTime=0;
	_taskInfo.endTime=0;
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
	command = _inter.interpretCommand(command);

	if (command == "exit") {
		performExit();
	} else { 
		if (command == "display" || command == "undo" || command == "redo"||command=="track") {
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
	
	else if(command=="unmark"){
	    return StardardCommand::UNMARK;
	}
	else if(command=="track"){
	    return StardardCommand::TRACK;
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
		case UNMARK:{
            performUnmark(message);
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
		case TRACK:{
			performTrack(message);
			break;
		}
        default:
            break;
    }
}

void CommandExecution::performAdd(string& message){
	_inter.convert(_content); 
	storeInTaskInfo();
	//backup TaskLists
	saveTaskLists();
	addEventToList();
	message=addResult();
}

void CommandExecution::storeInTaskInfo() {
	_taskInfo.description = _inter.getDescription();
	_taskInfo.month = _inter.getMonth();
	_taskInfo.intMonth = _inter.getIntMonth();
	_taskInfo.day = _inter.getDay();
	_taskInfo.startTime = _inter.getStartTime();
	_taskInfo.endTime = _inter.getEndTime();
}

void CommandExecution::addEventToList() {
	_tasks.addTask(_taskInfo.description, _taskInfo.startTime, _taskInfo.endTime, _taskInfo.day, _taskInfo.intMonth, 2015);
	_tasks.setUndoStatus(false);
}

string CommandExecution::addResult() {
	ostringstream out;
	if(_taskInfo.startTime != -1 && _taskInfo.endTime != -1) {
		out<<MESSAGE_NORMAL_TASK_ADDED;
	} else {
		if(_taskInfo.endTime != -1) {
			out<<MESSAGE_DEADLINE_TASK_ADDED;
		} else {
			out<<MESSAGE_FLOATING_TASK_ADDED;
		}
	}
	return out.str();
}

void CommandExecution::performDelete(string& message) {
	int index=stoi(_content.c_str());
	saveTaskLists();
	if(_tasks.deleteTask(index)) {
		_tasks.setUndoStatus(false);
		message = "Deleted\r\n";
	}
	else{
		message = "Invalid index!\r\n"; 
	}
}

void CommandExecution::performUpdate(string& message) {
	size_t end = _content.find_first_of(" ");
	string indexString = _content.substr(0, end);
	int index = stoi(indexString.c_str());
	_content = _content.substr(end+1, _content.size()-end);
	_inter.convert(_content); 
	storeInTaskInfo();
	//backup TaskLists
	saveTaskLists();
	_tasks.updateTask(index, _taskInfo.description, _taskInfo.startTime, _taskInfo.endTime, _taskInfo.day, _taskInfo.intMonth, 2015);
	_tasks.setUndoStatus(false);
	ostringstream out;
	out<<MESSAGE_UPDATED;

	message=out.str();
}

void CommandExecution::performDisplay(string& message) {
	message = _tasks.displayTasks();
}

void CommandExecution::performSearch(string& message){
	message = _tasks.searchTask(_content);
}

void CommandExecution::saveInFile(){
    _tasks.writeIntoFile();
}

void CommandExecution::performLocation(string& message){
	message = _tasks.changeFileLocation(_content);
}

void CommandExecution::performUndo(string& message){
	if (_tasks.getUndoStatus() == true){
		message = message + "Cannot undo twice. \n";
	}
	else {
		_tasks.undoCommand();
		_tasks.setUndoStatus(true);
		message=message+"Undo is successful \n";  
	}
}

void CommandExecution::performRedo(string& message){
	if (_tasks.getUndoStatus() == false){
		message = message + "Cannot redo because no UNDO command has been done. \n";
	}
	else {
		//We temporarily use the same code for redo because it is just swap the tasklists
	    _tasks.undoCommand();
		_tasks.setUndoStatus(false);
		message=message+"Redo is successful \n";  
	}
}

void CommandExecution::saveTaskLists(){
	_tasks.copyTaskLists();
}

void CommandExecution::performExit(){
	_tasks.operateExit();
}

void CommandExecution::performMark(string& message){
	int index=stoi(_content.c_str());
    _tasks.operateMark(index);
	_tasks.setUndoStatus(false);
	message = "Event marked done. \r\n";

}

void CommandExecution::performUnmark(string& message){
    int index=stoi(_content.c_str());
    _tasks.operateUnmark(index);
	_tasks.setUndoStatus(false);
	message = "Event unmarked done. \r\n";
}

void CommandExecution::performTrack(string& message){
   
	message = _tasks.trackTasks();
}