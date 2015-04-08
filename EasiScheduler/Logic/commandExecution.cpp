#include "commandExecution.h"

using namespace std;




#define MESSAGE_SUCCESSFUL_NORMAL_TASK_ADDED(description) "Successfully added (Normal Task) '" + description + "' to the schedule\r\n";
#define MESSAGE_SUCCESSFUL_DEADLINE_TASK_ADDED(description) "Successfully added (Deadline Task) '" + description + "' to the schedule\r\n";
#define MESSAGE_SUCCESSFUL_FLOATING_TASK_ADDED(description) "Successfully added (Floating Task) '" + description + "' to the schedule\r\n";
#define MESSAGE_SUCCESSFUL_UPDATED "The event is updated\r\n";
#define MESSAGE_SUCCESSFUL_UNDO "Undo is successful\r\n";
#define MESSAGE_SUCCESSFUL_REDO "Redo is successful\r\n";
#define MESSAGE_SUCCESSFUL_MARK "Event marked done\r\n";
#define MESSAGE_SUCCESSFUL_UNMARK "Event unmarked done\r\n";
#define MESSAGE_SUCCESSFUL_DELETION "Successfully deleted\r\n";


#define MESSAGE_EMPTY_CONTENT "Don't be lazy, please type something\r\n";
#define MESSAGE_EMPTY_LIST "Schedule is empty\r\n";

#define MESSAGE_INVALID_COMMAND_FORMAT "Wrong command format, plesae refer to user guide\r\n";
#define MESSAGE_INVALID_UPDATE_INPUT "Invalid UPDATE Input\r\n";
#define MESSAGE_INVALID_UNDO "Cannot undo twice\r\n";
#define MESSAGE_INVALID_ADD_INPUT "Invalid ADD Input\r\n";
#define MESSAGE_INVALID_INDEX "Invalid index\r\n";
#define MESSAGE_INVALID_REDO "Cannot redo because no UNDO command has been done\r\n";

CommandExecution::CommandExecution() {
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

CommandExecution::~CommandExecution() {
}



string CommandExecution::readCommand(string userInput) { 
	string message = "";
	string command = "";
	size_t end = 0;

	//logging user inputs 
	ofstream log;
	log.open("userInputLogger.txt", ofstream::out | ofstream::app);
	log << userInput << endl;	

	command = getCommand(userInput, end);

	if(isExit(command)) {
		performExit();
	} else { 
		if (isSingleWordCommand(command)) {
			if(isInvalidFormat(end, userInput)) {
				return MESSAGE_INVALID_COMMAND_FORMAT;
			} else {
				executeCommand(determineCommandType(command), message);
			}
		} else {
			if(end == string::npos) {
				return MESSAGE_INVALID_COMMAND_FORMAT;
			} else {
				retrieveContent(userInput, end);
				if(isEmptyContent(getContent())) {
					return MESSAGE_EMPTY_CONTENT;
				} else {
					executeCommand(determineCommandType(command), message);
				}
			}
		}
	}
	return message;
}



bool CommandExecution::isInvalidFormat(size_t end, string userInput) {
	if(end != string::npos && userInput.find_first_not_of(" ", end) != string:: npos) {
		return true;
	} else {
		return false;
	}
}




string CommandExecution::getCommand(string userInput, size_t & end) {
	end = userInput.find_first_of(" ");
	string command = userInput.substr(0, end);
	command = _inter.interpretCommand(command);
	return command;
}



bool CommandExecution::isExit(string command) {
	return command == "exit";
}



bool CommandExecution::isSingleWordCommand(string command) {
	return command == "display" || command == "undo" || command == "redo"|| command == "track";
}



bool CommandExecution::isEmptyContent(string content) {
	size_t end = content.find_first_not_of(" ");
	if(end == string::npos) {
		return true;
	} else {
		return false;
	}
}



void CommandExecution::retrieveContent(string userInput, size_t end) {
	_content = userInput.substr(end + 1, userInput.size() - end);
}



string CommandExecution::getContent() {
	return _content;
}



CommandExecution::StandardCommand const CommandExecution::determineCommandType(string command){
	if (command=="add"){
		return StandardCommand::ADD;
    } else {
		if (command=="delete") {
			return StandardCommand::DELET;
		} else {
			if (command=="update") {
				return StandardCommand::UPDATE;
			} else {
				if (command=="display") {
			        return StandardCommand::DISPLAY;
				} else {
					if (command=="exit") {
						return StandardCommand::EXIT;
					} else {
						if(command=="search"){
							return StandardCommand::SEARCH;
						} else {
							if(command=="location"){
								return StandardCommand::LOCATION;
							} else {
								if(command=="undo"){
									return StandardCommand::UNDO;
								} else {
									if(command=="redo"){
										return StandardCommand::REDO;
									} else {
										if(command=="mark") {
											return StandardCommand::MARK;
										} else {
											if(command=="unmark"){
											    return StandardCommand::UNMARK;
											} else {
												if(command=="track") {
													return StandardCommand::TRACK;
												} else {
													return StandardCommand::INVALID;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}



void CommandExecution::executeCommand(StandardCommand commandType, string& message) {
	 switch (commandType) {

        case ADD:{
            performAdd(message, getContent());
			_tasks.sortTasks();
			saveInFile();
            break;
        }

        case DISPLAY:{
 			_tasks.sortTasks();
			performDisplay(message);
			saveInFile();
            break;
        }

        case DELET:{
            performDelete(message, getContent());
			_tasks.sortTasks();
			saveInFile();
            break;
        }

        case UPDATE:{
            performUpdate(message, getContent());
			_tasks.sortTasks();
			saveInFile();
			break;
        }

		case UNDO:{
			performUndo(message);
			_tasks.sortTasks();
			saveInFile();
			break;
		}

		case REDO:{
			performRedo(message);
			_tasks.sortTasks();
			saveInFile();
			break;
		}

        case EXIT:{
            performExit();
            break;
        }

        case MARK:{
            performMark(message, getContent());
			saveInFile();
            break;
        }

		case UNMARK:{
            performUnmark(message, getContent());
			saveInFile();
            break;
        }

        case INVALID:{
            performInvalidMessage(message);
            break;
        } 

		case SEARCH:{
			performSearch(message, getContent());
			break;
		}

		case LOCATION:{
			performLocation(message, getContent());
			break;
		}

		case TRACK:{
			_tasks.sortTasks();
			performTrack(message);
			saveInFile();
			break;
		}

        default:
            break;
    }
}

void CommandExecution::performInvalidMessage(string& message){
	message = MESSAGE_INVALID_COMMAND_FORMAT;
}
	

void CommandExecution::performAdd(string& message, string content){
	_inter.convert(content);
	if(_inter.getIsValidInput()){
		storeInTaskInfo();
		saveTaskLists();
		addEventToList();
		message = getAddResult(getStartYear(), getEndYear(), getDescription());
		_inter.reset();
	} else {
		message = MESSAGE_INVALID_ADD_INPUT;
		_inter.reset();
	}
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
	_tasks.addTask(_taskInfo.description, _taskInfo.startTime,_taskInfo.startDay,_taskInfo.startMonth,_taskInfo.startYear,  _taskInfo.endTime, _taskInfo.endDay, _taskInfo.endMonth,_taskInfo.endYear);
	_tasks.setUndoStatus(false);
}



string CommandExecution::getAddResult(int startYear, int endYear, string description) {
	if(isNormalTask(startYear, endYear)) {
		return MESSAGE_SUCCESSFUL_NORMAL_TASK_ADDED(description); 
	} else {
		if(isDeadlineTask(startYear, endYear)) {
			return MESSAGE_SUCCESSFUL_DEADLINE_TASK_ADDED(description);
		} else {
			return MESSAGE_SUCCESSFUL_FLOATING_TASK_ADDED(description);
		}
	}
}

bool CommandExecution::isNormalTask (int startYear, int endYear){
    if((startYear != -1) && (endYear != -1)){
        return true;
    } else {
		return false;
	}
}

bool CommandExecution::isDeadlineTask (int startYear, int endYear){
    if((startYear == -1) && (endYear != -1)){
        return true;
    } else {
		return false;
	}
}

void CommandExecution::performDelete(string& message, string content) {
	int index = stoi(content.c_str());
	saveTaskLists();
	if(isValidIndexForDeletion(index)) {
		_tasks.setUndoStatus(false);
		message = MESSAGE_SUCCESSFUL_DELETION;
	} else {
		message = MESSAGE_INVALID_INDEX; 
	}
}



void CommandExecution::performUpdate(string& message, string userInput) {
	int index;
	string content;

	seperateInputForUpdate(userInput, index, content);
    _inter.convert(content);
	
	if(isInvalidIndex(index)) {
		message = MESSAGE_INVALID_INDEX;
		return;
	} else {
		if(_inter.getIsValidInput()){
			updateToTasks(index);
			message = MESSAGE_SUCCESSFUL_UPDATED;
			_inter.reset();
		} else {
			message = MESSAGE_INVALID_UPDATE_INPUT;
			_inter.reset();
		}
	}

}

void CommandExecution::seperateInputForUpdate(string userInput, int& index, string& content) {
	istringstream in(userInput);
	size_t start;
	string dummy;
	in >> index;
	in >> dummy;
	start = userInput.find(dummy);
	content = userInput.substr(start, userInput.size() - start);
}


void CommandExecution::updateToTasks(int index) {
	storeInTaskInfo();
    saveTaskLists();
    _tasks.updateTask(index, _taskInfo.description, _taskInfo.startTime,_taskInfo.startDay,_taskInfo.startMonth,_taskInfo.startYear,  _taskInfo.endTime, _taskInfo.endDay, _taskInfo.endMonth,_taskInfo.endYear);
    _tasks.setUndoStatus(false);
}

void CommandExecution::performDisplay(string& message) {
	if(getSize() == 0) {
		message = MESSAGE_EMPTY_LIST;
	} else {
		message = _tasks.displayTasks();
	}
}



void CommandExecution::performSearch(string& message, string content){
	message = _tasks.searchTask(content);
}



void CommandExecution::saveInFile(){
    _tasks.writeIntoFile();
}



void CommandExecution::performLocation(string& message, string content){
	message = _tasks.changeFileLocation(content);
}

bool CommandExecution::isUndoAlready(){
    if (_tasks.getIsUndoStatus()){
        return true;
    } else {
        return false;
    }
}


void CommandExecution::performUndo(string& message){
	if (isUndoAlready()){
		message = MESSAGE_INVALID_UNDO;
	} else {
		_tasks.undoCommand();
		_tasks.setUndoStatus(true);
		message = MESSAGE_SUCCESSFUL_UNDO;  
	}

}



void CommandExecution::performRedo(string& message){
	if (!isUndoAlready()){
		message = MESSAGE_INVALID_REDO;
	} else {
		//We temporarily use the same code for redo because it is just swap the tasklists
	    _tasks.undoCommand();
		_tasks.setUndoStatus(false);
		message = MESSAGE_SUCCESSFUL_REDO;  
	}
}



void CommandExecution::saveTaskLists(){
	_tasks.copyTaskLists();
}



void CommandExecution::performExit(){
	_tasks.operateExit();
}



void CommandExecution::performMark(string& message, string content){
	int index = stoi(content.c_str());
	if(isInvalidIndex(index)) {
		message = MESSAGE_INVALID_INDEX;
	} else {
		saveTaskLists();
		_tasks.operateMark(index);
		_tasks.setUndoStatus(false);
		message = MESSAGE_SUCCESSFUL_MARK;
	}
}



void CommandExecution::performUnmark(string& message, string content){
	int index=stoi(content.c_str());
	if(isInvalidIndex(index)) {
		message = MESSAGE_INVALID_INDEX;
	} else {
		saveTaskLists();
		_tasks.operateUnmark(index);
		_tasks.setUndoStatus(false);
		message = MESSAGE_SUCCESSFUL_UNMARK;
	}
}



void CommandExecution::performTrack(string& message){
	message = _tasks.trackTasks();
}





//new function for unit testing

int CommandExecution::getStartYear(){
	return _taskInfo.startYear;
}

int CommandExecution::getEndYear(){
	return _taskInfo.endYear;
}

string CommandExecution::getDescription() {
	return _taskInfo.description;
}

bool CommandExecution::isValidIndexForDeletion(int index) {
	return _tasks.isDeleted(index);
}

bool CommandExecution::isInvalidIndex(int index) {
	return index < 1 || index > getSize();
}

int CommandExecution::getSize() {
	return _tasks.getSize();
}



// For UI
string CommandExecution::readRecentTask(int index){
	return _tasks.readTask(index);
}



