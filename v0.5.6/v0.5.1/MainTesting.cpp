#include <iostream>
#include <string>
#include "CommandExecution.h"
#include "SmartAdder.h"
#include "Storage.h"
#include "Task.h"
#include "CurrentTime.h"
using namespace std;

int main(int argc, const char * argv[]) {
    string input;
    getline(cin,input);
    CommandExecution v01;
    
	string stopCommand;


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