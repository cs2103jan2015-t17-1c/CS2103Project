//

//  TaskList.h

//  Task

//

//  Created by Xu Meng on 10/3/15.

//  Copyright (c) 2015 Xu Meng. All rights reserved.

//



#ifndef TaskList_h

#define TaskList_h

#include <string>

#include <vector>

#include <sstream>

#include <fstream>

#include <windows.h>

#include "Task.h"

#include "CurrentTime.h"



using namespace std;



class Storage{

    

private:

    vector<Task> _taskLists;
    vector<Task> previousTaskLists;
    ifstream readFile;
    string fileName;
    ofstream writeFile;
    int totalUnits;
    bool undoOnce;


   

public:

    Storage();
	bool getUndoStatus();
	void setUndoStatus(bool status);
    Task getTask(int index);
    void addTask(string eventdescription, int starttime, int startday, int startmonth, int startyear, int endtime, int endday, int endmonth, int endyear);
    bool isDeleted(int index);
	void updateTask(int index, string eventdescription, int starttime, int startday, int startmonth,int startyear, int endtime, int endday, int endmonth, int endyear);
    string displayTasks(); 
    string readTask(int index);
	string searchTask(string content);
    void writeIntoFile();
    void writeOneTaskToFile(vector<Task>::iterator &iter);
    string changeFileLocation(string newlocation);
    void copyTaskLists();
    void undoCommand();
    void operateExit();
	void sortTasks();
	void operateMark(int index);
	void operateUnmark(int index);
    string trackTasks();
	void checkOverdue();


	

};





#endif

