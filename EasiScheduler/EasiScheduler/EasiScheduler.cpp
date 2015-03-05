//
//  EasiScheduler.cpp
//  EasiScheduler
//
//  Created by Shirley, Wang Jiexuan on 1/23/15.
//  Copyright (c) 2015 wang. All rights reserved.
//

#include "EasiScheduler.h"
using namespace std;

const string EasiScheduler::PROMPT_WELCOME = "Welcome to EasiScheduler. %s is ready for use\n";
const string EasiScheduler::PROMPT_EMPTY = "%s is empty\n";
const string EasiScheduler::PROMPT_ADDED = "added to %s: \"%s\"\n";
const string EasiScheduler::PROMPT_DELETED = "deleted from %s: \"%s\"\n";
const string EasiScheduler::PROMPT_CLEARED = "all content deleted from %s\n";
const string EasiScheduler::PROMPT_INVALID_COMMAND = "Invalid command format:\nadd {text}\tto add line\ndisplay\tto display all lines\ndelete {line number}\tto delete certainlines\nclear\tto clear all lines\nexit\tto exit program\n";
const string EasiScheduler::PROMPT_PROGRAM_EXIT = "Enter any key to exit: \n";

EasiScheduler::EasiScheduler(char* argv[]){
    setFilename(readFilename(argv));
    setInitialNoOfLines();
	printWelcomeMessage();
	
}

string EasiScheduler::readFilename(char* argv[]){
    return argv[1];
}

void EasiScheduler::setFilename(string filename){
    _filename=filename;
}

void EasiScheduler::setInitialNoOfLines(){
     _no_of_lines=0;
}

void EasiScheduler::printWelcomeMessage(){
	printf(PROMPT_WELCOME.c_str(),_filename.c_str());
}

string EasiScheduler::readCommand(){
    string command;
    cin>>command;
    return command;
}

EasiScheduler::CommandType const EasiScheduler::determineCommandType(string command){
    
    transform(command.begin(),command.end(),command.begin(),::tolower);
    
	if (command=="add"){
        return CommandType::ADD;
    }
    else if (command=="delete"){
        return CommandType::DELETE_LINE;
    }
    else if (command=="clear"){
        return CommandType::CLEAR_ALL;
    }
    else if (command=="display"){
        return CommandType::DISPLAY_ALL;
    }
    else if (command=="exit"){
        return CommandType::EXIT;
    }
    else
        return CommandType::INVALID;
}

void EasiScheduler::executeCommand(EasiScheduler::CommandType _commandType){
    switch (_commandType) {
        case ADD:{
            performAddLine();
            break;
        }
        case DISPLAY_ALL:{
            performDisplayAll();
            break;
        }
        case DELETE_LINE:{
            performDeleteLine();
            break;
        }
        case CLEAR_ALL:{
            performClearAll();
			break;
        }
        case EXIT:{
            performProgramExit();
            break;
        }
        case INVALID:{
            printMessageifCommandInvalid();
            break;
        }
            
        default:
            break;
    }
}

void EasiScheduler::performAddLine(){
	string line=readNewLine();
	pushBackLine(line);
    incrementNoOfLines();
	printMessageAfterAdded(line);
}

string EasiScheduler::readNewLine(){
	getchar();
	string line;
    getline(cin,line);
	return line;
}

void EasiScheduler::pushBackLine(string line){
    _lines.push_back(line);
}

void EasiScheduler::incrementNoOfLines(){
	_no_of_lines++;
}

void EasiScheduler::printMessageAfterAdded(string line){
printf(PROMPT_ADDED.c_str(),EasiScheduler::_filename.c_str(),line.c_str());
}



void EasiScheduler::performDeleteLine(){
    int index=readIndex();
	checkValidIndex(index);
	decrementNoOfLines(index);
	printMessageAfterDeleted(index);
	vector<string>::iterator iteratorPointingToLineDeleted = getIteratorOfLineDeleted(index);
    deleteLine(iteratorPointingToLineDeleted);
}

int EasiScheduler::readIndex(){
	int index;
	cin>>index;
	return index;
}

void EasiScheduler::checkValidIndex(int index){
	if(index>_no_of_lines){
		cout<<"invalid index\n";
		exit(2);
	}
}

void EasiScheduler::decrementNoOfLines(int index){
	 _no_of_lines--;
}

void EasiScheduler::printMessageAfterDeleted(int lineIndex){
	printf(PROMPT_DELETED.c_str(),EasiScheduler::_filename.c_str(),_lines[lineIndex-1].c_str());
}

vector<string>::iterator EasiScheduler:: getIteratorOfLineDeleted(int lineIndex){
	vector<string>::iterator iter=_lines.begin();
    for (int i=1; i!=lineIndex; i++,iter++) {
    }
    return iter;
}

void EasiScheduler::deleteLine(vector<string>::iterator iter){
	 _lines.erase(iter);
}

void EasiScheduler::performClearAll(){
	
    clearAllLines();
	printMessageAfterClear();
}

void EasiScheduler::clearAllLines(){
	for (;_no_of_lines!=0;_no_of_lines--) {
        popBackLine();
    }
}

void EasiScheduler::popBackLine(){
	_lines.pop_back();
}

void EasiScheduler::printMessageAfterClear(){
	printf(PROMPT_CLEARED.c_str(),EasiScheduler::_filename.c_str());
}

void EasiScheduler::performProgramExit(){
    exit(0);
}

void EasiScheduler::printMessageifCommandInvalid(){
    printf(PROMPT_INVALID_COMMAND.c_str());
}

void EasiScheduler::performDisplayAll(){
    if (_no_of_lines==0) {
       printMessageIfNoLine(); 
    }
    else{
        displayAllLines();
	}  
}

void EasiScheduler::printMessageIfNoLine(){
  printf(PROMPT_EMPTY.c_str(),_filename.c_str());
}

void EasiScheduler::displayAllLines(){
	for (int i=0; i<_no_of_lines; i++) {
            printOneLine(i);
	}
}

void EasiScheduler::printOneLine(int lineIndex){
	cout<<lineIndex+1<<". "<<_lines[lineIndex]<<endl;
}

void EasiScheduler::saveToFile(){
    ofstream outFile;
	openOutputFile(outFile);
    removeCacheInFile();
    writeLinesInFile(outFile);
	closeOutputFile(outFile);
}
void EasiScheduler::openOutputFile(ofstream & outFile){
    outFile.open(_filename);
}
void EasiScheduler::removeCacheInFile(){
	remove(_filename.c_str());
}
void EasiScheduler::writeLinesInFile(ofstream & outFile){
	for (int i=0; i<_no_of_lines; i++) {
       writeOneLineInFile(outFile,i);
	}
}
void EasiScheduler::writeOneLineInFile(ofstream & outFile, int lineIndex){
	outFile<<lineIndex+1<<". "<<_lines[lineIndex]<<endl;
}

void EasiScheduler::closeOutputFile(ofstream & outFile){
	outFile.close();
}