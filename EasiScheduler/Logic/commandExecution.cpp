#include "commandExecution.h"

<<<<<<< HEAD
=======

#define MESSAGE_NORMAL_TASK_ADDED "Successfully added ��on " + taskInfo.month + " " << taskInfo.day << " from " << taskInfo.startTime << " to " << taskInfo.endTime << " " + taskInfo.description + "�� to the schedule\n";
#define MESSAGE_UPDATED "The event is updataed to:\n��on " + taskInfo.month + " " << taskInfo.day << " from " << taskInfo.startTime << " to " << taskInfo.endTime << " " + taskInfo.description + "��\n";

>>>>>>> 1a9627c352d469f80d0c7bc5047c1c52093dd144

//problem with output message format
#define MESSAGE_NORMAL_TASK_ADDED "Successfully added 'from "<<_taskInfo.startYear<<" "<< _taskInfo.startMonth<< " " << _taskInfo.startDay<<" "<<_taskInfo.startTime<<" to "<< _taskInfo.endYear<< " " << _taskInfo.endMonth<<" "<<_taskInfo.endDay<<" "<< _taskInfo.endTime<<" "<< _taskInfo.description<< "' to the schedule\r\n";
#define MESSAGE_UPDATED "The event is updataed to:\r\n'on " << _taskInfo.startMonth + " " << _taskInfo.startDay << " from " << _taskInfo.startTime << " to " << _taskInfo.endTime << " " + _taskInfo.description + "'\r\n";
#define MESSAGE_DEADLINE_TASK_ADDED "Successfully added 'on " <<_taskInfo.endYear<<" "<< _taskInfo.endMonth<< " " << _taskInfo.endDay << " before " << _taskInfo.endTime << " " << _taskInfo.description << "' to the schedule\r\n";
#define MESSAGE_FLOATING_TASK_ADDED "Successfully added 'on " << _taskInfo.startYear<<" "<<_taskInfo.startMonth<<" "<< _taskInfo.startDay << " " <<_taskInfo.startTime << " "<< _taskInfo.description<< "' to the schedule\r\n";

CommandExecution::CommandExecution(void) {
	_content="";
	_taskInfo.description="";
	_taskInfo.startMonth=-1;
	_taskInfo.startDay=-1;
	_taskInfo.startTime=-1;
	_taskInfo.startYear=-1;
	_taskInfo.endTime=-1;
	_taskInfo.endMonth=-1;
	_taskInfo.endDay=-1;
	_taskInfo.endYear=-1;
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

<<<<<<< HEAD
bool CommandExecution::isInvalid(size_t end, string userInput) {
	if(end != string::npos && userInput.find_first_not_of(" ", end) != string:: npos) {
		return true;
	} else {
		return false;
	}
=======
void CommandExecution::verify(size_t end, string userInput) {
	if(end != string::npos && userInput.find_first_not_of(" ", end) != string:: npos)
		throw new exception ("error format");
>>>>>>> 1a9627c352d469f80d0c7bc5047c1c52093dd144
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
<<<<<<< HEAD
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
=======
>>>>>>> 1a9627c352d469f80d0c7bc5047c1c52093dd144
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
<<<<<<< HEAD
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
=======
>>>>>>> 1a9627c352d469f80d0c7bc5047c1c52093dd144
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
	_taskInfo.startMonth = _inter.getStartMonth();
	_taskInfo.endMonth = _inter.getEndMonth();
	_taskInfo.startDay = _inter.getStartDay();
	_taskInfo.endDay = _inter.getEndDay();
	_taskInfo.startTime = _inter.getStartTime();
	_taskInfo.endTime = _inter.getEndTime();
	_taskInfo.startYear=_inter.getStartYear();
	_taskInfo.endYear=_inter.getEndYear();
}

void CommandExecution::addEventToList() {
<<<<<<< HEAD
	_tasks.addTask(_taskInfo.description, _taskInfo.startTime,_taskInfo.startDay,_taskInfo.startMonth,_taskInfo.startYear,  _taskInfo.endTime, _taskInfo.endDay, _taskInfo.endMonth,_taskInfo.endYear);
	//cout<<_taskInfo.startTime<<_taskInfo.startDay<<_taskInfo.startMonth<<_taskInfo.startYear<<  _taskInfo.endTime<< _taskInfo.endDay<< _taskInfo.endMonth<<_taskInfo.endYear;
	_tasks.setUndoStatus(false);
=======
	tasks.addTask(taskInfo.description, taskInfo.day, taskInfo.intMonth, taskInfo.startTime, taskInfo.endTime, 2015);
>>>>>>> 1a9627c352d469f80d0c7bc5047c1c52093dd144
}

string CommandExecution::addResult() {
	ostringstream out;
	if(((_taskInfo.startTime != -1)||(_taskInfo.startDay != -1)||(_taskInfo.startYear != -1)||(_taskInfo.startMonth != -1) )&& ((_taskInfo.endTime != -1)||(_taskInfo.endDay != -1)||(_taskInfo.endMonth != -1)||(_taskInfo.endYear != -1))) {
		out<<MESSAGE_NORMAL_TASK_ADDED;
	} else {
		if(((_taskInfo.startTime == -1)||(_taskInfo.startDay == -1)||(_taskInfo.startYear == -1)||(_taskInfo.startMonth == -1) )&& ((_taskInfo.endTime != -1)||(_taskInfo.endDay != -1)||(_taskInfo.endMonth != -1)||(_taskInfo.endYear != -1))) {
			out<<MESSAGE_DEADLINE_TASK_ADDED;
		} else {
			out<<MESSAGE_FLOATING_TASK_ADDED;
		}
	}
	return out.str();
}

void CommandExecution::performDelete(string& message) {
	assert(stoi(_content.c_str()));
	int index=stoi(_content.c_str());
<<<<<<< HEAD
	saveTaskLists();
	if(_tasks.deleteTask(index)) {
		_tasks.setUndoStatus(false);
		message = "Deleted\r\n";
	}
	else{
		message = "Invalid index!\r\n"; 
=======
	if(index <1) {
		message = "Invalid index!\n";
	} else {
		tasks.deleteTask(index);
		message="deleted\n";
>>>>>>> 1a9627c352d469f80d0c7bc5047c1c52093dd144
	}
}

void CommandExecution::performUpdate(string& message) {
<<<<<<< HEAD
	size_t end = _content.find_first_of(" ");
	string indexString = _content.substr(0, end);
	int index = stoi(indexString.c_str());
	_content = _content.substr(end+1, _content.size()-end);
	_inter.convert(_content); 
	storeInTaskInfo();
	//backup TaskLists
	saveTaskLists();
	_tasks.updateTask(index, _taskInfo.description, _taskInfo.startTime,_taskInfo.startDay,_taskInfo.startMonth,_taskInfo.startYear,  _taskInfo.endTime, _taskInfo.endDay, _taskInfo.endMonth,_taskInfo.endYear);
	_tasks.setUndoStatus(false);
=======
	istringstream in(_content);
	int index;
	in>>index;
	in>>_content;
	inter.convert(_content); 
	storeInTaskInfo();
	tasks.updateTask(index, taskInfo.description, taskInfo.day,taskInfo.intMonth, taskInfo.startTime, taskInfo.endTime, 2015); 
>>>>>>> 1a9627c352d469f80d0c7bc5047c1c52093dd144
	ostringstream out;
	out<<MESSAGE_UPDATED;

	message=out.str();
}

void CommandExecution::performDisplay(string& message) {
<<<<<<< HEAD
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
=======
	message="All displayed. \n";
	tasks.displayTasks();
}


int main() {
	CommandExecution comd;
	string s;
	s=comd.readCommand("add July 10 -s 1400 -e 1600 play basketball");
	cout<<s<<endl;
	s=comd.readCommand("display");
	cout<<s<<endl;
	s=comd.readCommand ("update 1 August 15 -s 1200 -e 1400 play volleyball");
	cout<<s<<endl;
	s=comd.readCommand("delete 1");
	cout<<s<<endl;
	s=comd.readCommand("display");
	cout<<s<<endl;
	system("pause");
	return 0;
}
>>>>>>> 1a9627c352d469f80d0c7bc5047c1c52093dd144
