#include "commandExecution.h"


#define MESSAGE_NORMAL_TASK_ADDED "Successfully added ¡°on " + taskInfo.month + " " << taskInfo.day << " from " << taskInfo.startTime << " to " << taskInfo.endTime << " " + taskInfo.description + "¡± to the schedule\n";
#define MESSAGE_UPDATED "The event is updataed to:\n¡°on " + taskInfo.month + " " << taskInfo.day << " from " << taskInfo.startTime << " to " << taskInfo.endTime << " " + taskInfo.description + "¡±\n";



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
	if(command != "display" ) {
		_content=userInput.substr(end+1, userInput.size()-end);
	} else {
		try {
			verify(end, userInput);
		} catch (exception &e) {
			message=e.what();
			return message;
		}
	}
	command=inter.interpretCommand(command);
	executeCommand(determineCommandType(command),message);
	return message;
}

void CommandExecution::verify(size_t end, string userInput) {
	if(end != string::npos && userInput.find_first_not_of(" ", end) != string:: npos)
		throw new exception ("error format");
}


CommandExecution::StardardCommand const CommandExecution::determineCommandType(string command){
      
	if (command=="add"){
		return StardardCommand::ADD;
    }
    else if (command=="delete"){
        return StardardCommand::DELETE;
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
    else
        return StardardCommand::INVALID;
}

void CommandExecution::executeCommand(StardardCommand commandType, string& message) {;
	 switch (commandType) {
        case ADD:{
            performAdd(message);
            break;
        }
        case DISPLAY:{
            performDisplay(message);
            break;
        }
        case DELETE:{
            performDelete(message);
            break;
        }
        case UPDATE:{
            performUpdate(message);
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

void CommandExecution::performAdd(string& message) {
	inter.convert(_content); 
	storeInTaskInfo();
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
	tasks.addTask(taskInfo.description, taskInfo.day, taskInfo.intMonth, taskInfo.startTime, taskInfo.endTime, 2015);
}

string CommandExecution::addResult() {
	ostringstream out;
	out<<MESSAGE_NORMAL_TASK_ADDED;
	return out.str();
}

void CommandExecution::performDelete(string& message) {
	int index=stoi(_content.c_str());
	assert(index > 0); 
	tasks.deleteTask(index);
	message="deleted\n";
}

void CommandExecution::performUpdate(string& message) {
	istringstream in(_content);
	int index;
	in>>index;
	in>>_content;
	inter.convert(_content); 
	storeInTaskInfo();
	tasks.updateTask(index, taskInfo.description, taskInfo.day,taskInfo.intMonth, taskInfo.startTime, taskInfo.endTime, 2015); 
	ostringstream out;
	out<<MESSAGE_UPDATED;
	message=out.str();
}

void CommandExecution::performDisplay(string& message) {
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
