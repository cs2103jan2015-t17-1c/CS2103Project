#include "CommandChecker.h"
#include<ctype.h>
#include <algorithm>
#include <string>


CommandChecker::CommandChecker(void) {
}


CommandChecker::~CommandChecker(void) {
}

string CommandChecker::getCommand(string userInput, size_t & end) {
	end = userInput.find_first_of(" ");
	string command = userInput.substr(0, end);
	command = interpretCommand(command);
	return command;
}

string CommandChecker::interpretCommand(string command) {

    std::transform(command.begin(), command.end(), command.begin(), ::tolower);
	return command;
}


string CommandChecker::getContent(string userInput, size_t end) {
	return userInput.substr(end + 1, userInput.size() - end);
}

bool CommandChecker::isExitCommand(string command) {
	return command == "exit";
}

bool CommandChecker::isAddCommand(string command) {
	return command == "add";
}

bool CommandChecker::isDeleteCommand(string command) {
	return command == "delete";
}

bool CommandChecker::isDisplayCommand(string command) {
	return command == "display";
}

bool CommandChecker::isUpdateCommand(string command) {
	return command == "update";
}

bool CommandChecker::isMarkCommand(string command) {
	return command == "mark";
}

bool CommandChecker::isUnmarkCommand(string command) {
	return command == "unmark";
}

bool CommandChecker::isUndoCommand(string command) {
	return command == "undo";
}

bool CommandChecker::isRedoCommand(string command) {
	return command == "redo";
}

bool CommandChecker::isSearchCommand(string command) {
	return command == "search";
}

bool CommandChecker::isTrackCommand(string command) {
	return command == "track";
}

bool CommandChecker::isLocationCommand(string command) {
	return command == "location";
}

bool CommandChecker::isSingleWordCommand(string command) {
	return command == "display" || command == "undo" || command == "redo"|| command == "track";
}


bool CommandChecker::isInvalidCommandFormat(string userInput, size_t end) {
	if(end != string::npos && userInput.find_first_not_of(" ", end) != string:: npos) {
		return true;
	} else {
		return false;
	}
}

bool CommandChecker::isEmptyContent(string content) {
	size_t end = content.find_first_not_of(" ");
	if(end == string::npos) {
		return true;
	} else {
		return false;
	}
}