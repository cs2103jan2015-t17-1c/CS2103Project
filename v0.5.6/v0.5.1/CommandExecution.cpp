#include "CommandExecution.h"

using namespace std;




#define MESSAGE_SUCCESSFUL_SCHEDULE_TASK_ADDED(description) "Successfully added (Schedule Task) '" + description + "' to the schedule\r\n";
#define MESSAGE_SUCCESSFUL_DEADLINE_TASK_ADDED(description) "Successfully added (Deadline Task) '" + description + "' to the schedule\r\n";
#define MESSAGE_SUCCESSFUL_FLOATING_TASK_ADDED(description) "Successfully added (Floating Task) '" + description + "' to the schedule\r\n";
#define MESSAGE_SUCCESSFUL_UPDATED "The event is updated\r\n";
#define MESSAGE_SUCCESSFUL_UNDO "Undo is successful\r\n";
#define MESSAGE_SUCCESSFUL_REDO "Redo is successful\r\n";
#define MESSAGE_SUCCESSFUL_MARK "Event marked done\r\n";
#define MESSAGE_SUCCESSFUL_UNMARK "Event unmarked done\r\n";
#define MESSAGE_SUCCESSFUL_DELETION "Successfully deleted\r\n";


#define MESSAGE_EMPTY_CONTENT "Don't be lazy, please type something\r\n";

#define MESSAGE_INVALID_COMMAND_FORMAT "Wrong command format, plesae refer to user guide\r\n";
#define MESSAGE_INVALID_UPDATE_INPUT "Invalid UPDATE Input\r\n";
#define MESSAGE_INVALID_UNDO "Cannot undo twice\r\n";
#define MESSAGE_INVALID_ADD_INPUT "Invalid ADD Input\r\n";
#define MESSAGE_INVALID_INDEX "Invalid index\r\n";
#define MESSAGE_INVALID_REDO "Cannot redo because no UNDO command has been done\r\n";

CommandExecution::CommandExecution() {
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
	string content = "";
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
			if(isInvalidFormat(userInput, end)) {
				return MESSAGE_INVALID_COMMAND_FORMAT;
			} else {
				executeCommand(determineCommandType(command), message, "");
			}
		} else {
			if(end == string::npos) {
				return MESSAGE_INVALID_COMMAND_FORMAT;
			} else {
				content = retrieveContent(userInput, end);
				if(isEmptyContent(content)) {
					return MESSAGE_EMPTY_CONTENT;
				} else {
					executeCommand(determineCommandType(command), message, content);
				}
			}
		}
	}
	return message;
}



bool CommandExecution::isInvalidFormat(string userInput, size_t end) {
	return _checker.isInvalidCommandFormat(userInput, end);
}




string CommandExecution::getCommand(string userInput, size_t & end) {
	return _checker.getCommand(userInput, end);
}



bool CommandExecution::isExit(string command) {
	return _checker.isExitCommand(command);
}



bool CommandExecution::isSingleWordCommand(string command) {
	return _checker.isSingleWordCommand(command);
}



bool CommandExecution::isEmptyContent(string content) {
	return _checker.isEmptyContent(content);
}



string CommandExecution::retrieveContent(string userInput, size_t end) {
	return _checker.getContent(userInput, end);
}



CommandExecution::StandardCommand const CommandExecution::determineCommandType(string command){
	if (_checker.isAddCommand(command)){
		return StandardCommand::ADD;
	}
   
	if (_checker.isDeleteCommand(command)){
		return StandardCommand::DEL;
	}

	if (_checker.isUpdateCommand(command)) {
		return StandardCommand::UPDATE;
	}

	if (_checker.isDisplayCommand(command)) {
		return StandardCommand::DISPLAY;
	}
	if(_checker.isSearchCommand(command)) {
		return StandardCommand::SEARCH;
	}

	if(_checker.isLocationCommand(command)) {
		return StandardCommand::LOCATION;
	}
						
	if(_checker.isUndoCommand(command)) {
		return StandardCommand::UNDO;
	}

	if(_checker.isRedoCommand(command)) {
		return StandardCommand::REDO;
	}

	if(_checker.isMarkCommand(command)) {
		return StandardCommand::MARK;
	}

	if(_checker.isUnmarkCommand(command)) {
	    return StandardCommand::UNMARK;
	}
	
	if(_checker.isTrackCommand(command)) {
		return StandardCommand::TRACK;
	}

	return 	StandardCommand::INVALID;	
}



void CommandExecution::executeCommand(StandardCommand commandType, string& message, string content) {
	 switch (commandType) {

        case ADD:{
            performAdd(message, content);
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

        case DEL:{
            performDelete(message, content);
			_tasks.sortTasks();
			saveInFile();
            break;
        }

        case UPDATE:{
            performUpdate(message, content);
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

        case MARK:{
            performMark(message, content);
			saveInFile();
            break;
        }

		case UNMARK:{
            performUnmark(message, content);
			saveInFile();
            break;
        }

        case INVALID:{
            performInvalidMessage(message);
            break;
        } 

		case SEARCH:{
			performSearch(message, content);
			break;
		}

		case LOCATION:{
			performLocation(message, content);
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
	_adder.convert(content);
	if(_adder.getIsValidInput()){
		storeInTaskInfo();
		saveTaskLists();
		addEventToList();
		message = getAddResult(getStartYear(), getEndYear(), getDescription());
		_adder.reset();
	} else {
		message = MESSAGE_INVALID_ADD_INPUT;
		_adder.reset();
	}
}



void CommandExecution::storeInTaskInfo() {
	_taskInfo.description = _adder.getDescription();
	_taskInfo.startMonth = _adder.getStartMonth();
	_taskInfo.endMonth = _adder.getEndMonth();
	_taskInfo.startDay = _adder.getStartDay();
	_taskInfo.endDay = _adder.getEndDay();
	_taskInfo.startTime = _adder.getStartTime();
	_taskInfo.endTime = _adder.getEndTime();
	_taskInfo.startYear=_adder.getStartYear();
	_taskInfo.endYear=_adder.getEndYear();
}



void CommandExecution::addEventToList() {
	_tasks.addTask(_taskInfo.description, _taskInfo.startTime,_taskInfo.startDay,_taskInfo.startMonth,_taskInfo.startYear,  _taskInfo.endTime, _taskInfo.endDay, _taskInfo.endMonth,_taskInfo.endYear);
	_tasks.setUndoStatus(false);
}



string CommandExecution::getAddResult(int startYear, int endYear, string description) {
	if(isScheduleTask(startYear, endYear)) {
		return MESSAGE_SUCCESSFUL_SCHEDULE_TASK_ADDED(description); 
	} else {
		if(isDeadlineTask(startYear, endYear)) {
			return MESSAGE_SUCCESSFUL_DEADLINE_TASK_ADDED(description);
		} else {
			return MESSAGE_SUCCESSFUL_FLOATING_TASK_ADDED(description);
		}
	}
}

bool CommandExecution::isScheduleTask (int startYear, int endYear){
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
	if(!isdigit(content[0])){
		message = MESSAGE_INVALID_INDEX; 
	}else{
            int index = stoi(content.c_str());
	        saveTaskLists();
            if(_tasks.isValidIndex(index)){
				   _tasks.deleteTask(index);
		           _tasks.setUndoStatus(false);
		           message = MESSAGE_SUCCESSFUL_DELETION;
	        } else {
		              message = MESSAGE_INVALID_INDEX; 
	               }
		}

}



void CommandExecution::performUpdate(string& message, string userInput) {
	int index;
	string updatedContent;

	seperateInputForUpdate(userInput, index, updatedContent);
    _adder.convert(updatedContent);
	if(isValidIndex(index)) {
		if(_adder.getIsValidInput()){
				if(updateToTasks(index)){
				message = MESSAGE_SUCCESSFUL_UPDATED;
				_adder.reset();}
			 else {
				message = MESSAGE_INVALID_UPDATE_INPUT;
			}
		}
	} else {
		message = MESSAGE_INVALID_INDEX;
	}
}

void CommandExecution::seperateInputForUpdate(string userInput, int& index, string& updatedContent) {
	istringstream in(userInput);
	size_t start;
	string dummy;
	in >> index;
	in >> dummy;
	start = userInput.find(dummy);
	updatedContent = userInput.substr(start, userInput.size() - start);
}


bool CommandExecution::updateToTasks(int index) {
	storeInTaskInfo();
    saveTaskLists();
	_tasks.setUndoStatus(false);
    return (_tasks.isUpdatedTask(index, _taskInfo.description, _taskInfo.startTime,_taskInfo.startDay,_taskInfo.startMonth,_taskInfo.startYear,  _taskInfo.endTime, _taskInfo.endDay, _taskInfo.endMonth,_taskInfo.endYear));  
}

void CommandExecution::performDisplay(string& message) {
	
		message = _tasks.displayTasks();
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
	if(!isdigit(content[0])){
		message = MESSAGE_INVALID_INDEX;
	}else{
	         int index = stoi(content.c_str());
             saveTaskLists();
		     if(_tasks.isValidIndex(index)){
				    _tasks.operateMark(index);
		            _tasks.setUndoStatus(false);
		            message = MESSAGE_SUCCESSFUL_MARK;
			 } else{
		            message = MESSAGE_INVALID_INDEX;
					}
	}
}



void CommandExecution::performUnmark(string& message, string content){
	if(!isdigit(content[0])){
		message = MESSAGE_INVALID_INDEX; 
	}else{
		int index=stoi(content.c_str());
		if(_tasks.isValidIndex(index)){  
		    _tasks.operateUnmark(index);
			saveTaskLists();
		    _tasks.setUndoStatus(false);
		    message = MESSAGE_SUCCESSFUL_UNMARK;
		}else{
		message = MESSAGE_INVALID_INDEX;
	}
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


bool CommandExecution::isValidIndex(int index) {
	return _tasks.isValidIndex(index);
}

int CommandExecution::getSize() {
	return _tasks.getSize();
}



// For UI
string CommandExecution::readRecentTask(int index){
	return _tasks.readTask(index);
}




