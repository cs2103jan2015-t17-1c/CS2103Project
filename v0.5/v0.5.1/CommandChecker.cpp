//@author A0093868J
#include "CommandChecker.h"
#include <ctype.h>
#include <algorithm>
#include <string>
#include <exception>

const int MAX_INPUT_LENGTH = 1000;
const char* MESSAGE_EXCEPTION_MAXIMUN_INPUT_CHARACTER = "Exceed Maximun Length of Input!";
const string EXIT_COMMAND = "exit";
const string ADD_COMMAND = "add";
const string DELETE_COMMAND = "delete";
const string UPDATE_COMMAND = "update";
const string TRACK_COMMAND = "track";
const string SEARCH_COMMAND = "search";
const string UNDO_COMMAND = "undo";
const string REDO_COMMAND = "redo";
const string MARK_COMMAND = "mark";
const string UNMARK_COMMAND = "unmark";
const string DISPLAY_COMMAND = "display";
const string LOCATION_COMMAND = "location";


CommandChecker::CommandChecker(void) {
}


CommandChecker::~CommandChecker(void) {
}

//Purpose: To cut the first word of the string as the command
string CommandChecker::getCommand(string userInput, size_t & end) {
	end = userInput.find_first_of(" ");
	string command = userInput.substr(0, end);
	command = interpretCommand(command);
	return command;
}

//Purpose: To transform all the string to lower case
//Prerequiest: The characters are all alphabetic 
string CommandChecker::interpretCommand(string command) {

    std::transform(command.begin(), command.end(), command.begin(), ::tolower);
	return command;
}

//Purpose: To get the remaining content except the first word
string CommandChecker::getContent(string userInput, size_t end) {
	return userInput.substr(end + 1, userInput.size() - end);
}

bool CommandChecker::isExitCommand(string command) {
	return command == EXIT_COMMAND;
}

bool CommandChecker::isAddCommand(string command) {
	return command == ADD_COMMAND;
}

bool CommandChecker::isDeleteCommand(string command) {
	return command == DELETE_COMMAND;
}

bool CommandChecker::isDisplayCommand(string command) {
	return command == DISPLAY_COMMAND;
}

bool CommandChecker::isUpdateCommand(string command) {
	return command == UPDATE_COMMAND;
}

bool CommandChecker::isMarkCommand(string command) {
	return command == MARK_COMMAND;
}

bool CommandChecker::isUnmarkCommand(string command) {
	return command == UNMARK_COMMAND;
}

bool CommandChecker::isUndoCommand(string command) {
	return command == UNDO_COMMAND;
}

bool CommandChecker::isRedoCommand(string command) {
	return command == REDO_COMMAND;
}

bool CommandChecker::isSearchCommand(string command) {
	return command == SEARCH_COMMAND;
}

bool CommandChecker::isTrackCommand(string command) {
	return command == TRACK_COMMAND;
}

bool CommandChecker::isLocationCommand(string command) {
	return command == LOCATION_COMMAND;
}

bool CommandChecker::isSingleWordCommand(string command) {
	return (command == DISPLAY_COMMAND || command == UNDO_COMMAND|| command == REDO_COMMAND|| command == TRACK_COMMAND);
}

//Purpose: To check whether the string only contains one or more words.
//If containing one word, return true;
//If containing more than one word, return false;
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

//Purpose: To cut the string into two part, one is the first integer,
//the other one is the remaining string.
void CommandChecker::seperateContent(string userInput, int& index, string& updatedContent) {
	istringstream in(userInput);
	size_t start;
	string dummy;
	in >> index;
	in >> dummy;
	start = userInput.find(dummy);
	if(dummy == "") {
		updatedContent = " ";
	} else {
		updatedContent = userInput.substr(start, userInput.size() - start);
	}
}


void CommandChecker::verifyLengthOfUserInput(string userInput) {
	if(userInput.size() > MAX_INPUT_LENGTH) {
		throw new exception(MESSAGE_EXCEPTION_MAXIMUN_INPUT_CHARACTER);
	}
}