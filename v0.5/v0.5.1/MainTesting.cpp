//@author A0093868J-unused
//Used code is to build exe file without UI for internal testing
#include <iostream>
#include <string>
#include "CommandExecution.h"
#include "SmartAdder.h"
#include "EasiStorage.h"
#include "Task.h"
#include "CurrentTime.h"
using namespace std;

int main(int argc, const char * argv[]) {
    string input;
    getline(cin,input);
    CommandExecution v01;
    
	string stopCommand;

	//To allow many rounds of testings
    cout<<v01.readCommand(input);
    getline(cin,input);
	cout<<v01.readCommand(input);
    getline(cin,input);
	cout<<v01.readCommand(input);
    getline(cin,input);
	cout<<v01.readCommand(input);
    getline(cin,input);
	cout<<v01.readCommand(input);
    getline(cin,input);
	cout<<v01.readCommand(input);
    getline(cin,input);
	cout<<v01.readCommand(input);
    getline(cin,input);
	cout<<v01.readCommand(input);
	getline(cin,input);
	cout<<v01.readCommand(input);
	getline(cin,input);
	cout<<v01.readCommand(input);
	getline(cin,input);
	cout<<v01.readCommand(input);
	getline(cin,input);
	cout<<v01.readCommand(input);
	getline(cin,input);
	cout<<v01.readCommand(input);
	getline(cin,input);
	cout<<v01.readCommand(input);
	getline(cin,input);
	cout<<v01.readCommand(input);
	getline(cin,input);
	cout<<v01.readCommand(input);




    
    return 0;
}