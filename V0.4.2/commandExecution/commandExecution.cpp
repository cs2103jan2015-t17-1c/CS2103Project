#include "commandExecution.h"

using namespace std;





//problem with output message format

#define MESSAGE_NORMAL_TASK_ADDED "Successfully added (Normal Task) '" << _taskInfo.description<< "' to the schedule\r\n";

#define MESSAGE_DEADLINE_TASK_ADDED "Successfully added (Deadline Task) '" << _taskInfo.description<< "' to the schedule\r\n";

#define MESSAGE_FLOATING_TASK_ADDED "Successfully added (Floating Task) '" << _taskInfo.description<< "' to the schedule\r\n";

#define MESSAGE_UPDATED "The event is updated \r\n";

#define MESSAGE_ERORR_COMMAND_FORMAT "Wrong command format, plesae refer to user guide\r\n";

#define MESSAGE_EMPTY_CONTENT "Don't be lazy, please type something\r\n";



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



	ofstream log;

	log.open("userInputLogger.txt", ofstream::out | ofstream::app);

	log << userInput << endl;

	

	command = getCommand(userInput, end);

	

	if(isExit(command)) {

		performExit();

	} else { 

		if (isSingleWordCommand(command)) {

			if(isInvalidFormat(end, userInput)) {

				return MESSAGE_ERORR_COMMAND_FORMAT;

			} else {

				executeCommand(determineCommandType(command), message);

			}

		} else {

			if(end == string::npos) {

				return MESSAGE_ERORR_COMMAND_FORMAT;

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

            performDelete(message);

			_tasks.sortTasks();

			saveInFile();

            break;

        }

        case UPDATE:{

            performUpdate(message);

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

            performMark(message);

			saveInFile();

            break;

        }

		case UNMARK:{

            performUnmark(message);

			saveInFile();

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

			_tasks.sortTasks();

			performTrack(message);

			saveInFile();

			break;

		}

        default:

            break;

    }

}



void CommandExecution::performAdd(string& message){

	_inter.convert(_content);

	if(_inter.getvalidInput()){

	storeInTaskInfo();

	//backup TaskLists

	saveTaskLists();

	addEventToList();

	message=getAddResult();

	_inter.reset();

	}

	else{

	message="Invalid ADD Input \n";

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

	//cout<<_taskInfo.startTime<<_taskInfo.startDay<<_taskInfo.startMonth<<_taskInfo.startYear<<  _taskInfo.endTime<< _taskInfo.endDay<< _taskInfo.endMonth<<_taskInfo.endYear;

	_tasks.setUndoStatus(false);

}



string CommandExecution::getAddResult() {

	ostringstream out;

	if(isNormalTask()) {

		out<<MESSAGE_NORMAL_TASK_ADDED;

	} else {

		if(isDeadlineTask ()) {

			out<<MESSAGE_DEADLINE_TASK_ADDED;

		} else {

			out<<MESSAGE_FLOATING_TASK_ADDED;

		}

	}

	return out.str();

}

bool CommandExecution::isNormalTask (){
    if((_taskInfo.startYear != -1)||(_taskInfo.endYear != -1)){
        return true;
    }
    else return false;
}
bool CommandExecution::isDeadlineTask (){
    if((_taskInfo.startYear == -1)&&(_taskInfo.endYear != -1)){
        return true;
    }
    else return false;
}




void CommandExecution::performDelete(string& message) {

	int index=stoi(_content.c_str());

	saveTaskLists();

	if(_tasks.isDeleted(index)) {

		_tasks.setUndoStatus(false);

		message = "Deleted\r\n";

	} else {

		message = "Invalid index!\r\n"; 

	}

}



void CommandExecution::performUpdate(string& message) {

	istringstream in(_content);

	int index;

	int starting;

	string dummy;

	in>>index;

	in>>dummy;

	starting=_content.find(dummy);

	_content= _content.substr(starting,_content.size()-starting);

	

	/*size_t end = _content.find_first_of(" ");

	string indexString = _content.substr(0, end);

	int index = stoi(indexString.c_str());

	_content = _content.substr(end+1, _content.size()-end);*/

	
    _inter.convert(_content);

	if(_inter.getvalidInput()){

	
        storeInTaskInfo();

	//backup TaskLists

	
        saveTaskLists();

	
        _tasks.updateTask(index, _taskInfo.description, _taskInfo.startTime,_taskInfo.startDay,_taskInfo.startMonth,_taskInfo.startYear,  _taskInfo.endTime, _taskInfo.endDay, _taskInfo.endMonth,_taskInfo.endYear);

	
        _tasks.setUndoStatus(false);

	
        ostringstream out;

	
        out<<MESSAGE_UPDATED;

   
        message=out.str();

	
        _inter.reset();

	}else{

	
        message="Invalid Update Input \n";

	
        _inter.reset();

	}

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

bool CommandExecution::isUndoTrue(){
    if (_tasks.getUndoStatus() == true){
        return true;
    }else{
        return false;
    }
}



void CommandExecution::performUndo(string& message){

	if (isUndoTrue()){
		message = message + "Cannot undo twice. \n";
	}

	else {

		_tasks.undoCommand();

		_tasks.setUndoStatus(true);

		message=message+"Undo is successful \n";  

	}

}



void CommandExecution::performRedo(string& message){

	if (!isUndoTrue()){

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

	saveTaskLists();

    _tasks.operateMark(index);

	_tasks.setUndoStatus(false);

	message = "Event marked done. \r\n";



}



void CommandExecution::performUnmark(string& message){



	int index=stoi(_content.c_str());

	saveTaskLists();

    _tasks.operateUnmark(index);

	_tasks.setUndoStatus(false);

	message = "Event unmarked done. \r\n";

}



void CommandExecution::performTrack(string& message){

   

	message = _tasks.trackTasks();

}



string CommandExecution::readRecentTask(int index){



	return _tasks.readTask(index);



}





