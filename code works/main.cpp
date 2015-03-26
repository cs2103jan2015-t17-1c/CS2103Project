//
//  main.cpp
//  testing-xm
//
//  Created by Xu Meng on 12/3/15.
//  Copyright (c) 2015 Xu Meng. All rights reserved.
//

#include <iostream>
#include <string>
#include "commandExecution.h"
#include "interpreter.h"
#include "Storage.h"
#include "Task.h"

using namespace std;

int main(int argc, const char * argv[]) {
    string input;
    getline(cin,input);
    CommandExecution v01;
    
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
