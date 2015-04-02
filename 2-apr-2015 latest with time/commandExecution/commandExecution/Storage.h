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
#include "task.h"

using namespace std;

class Storage{
    
private:
    vector<Task> _tasklist;
    vector<Task> _previoustasklist;
    
public:
    Storage(){
    };
    
    Task getTask(int index){
        return _tasklist[index];
    }
    
    void addTask(string eventdescription, int starttime, int endtime, int day, int month, int year){
        Task newTask(eventdescription, starttime, endtime, day, month, year);
        _tasklist.push_back(newTask);
    }
    
    void deleteTask(int index){
        _tasklist.erase(_tasklist.begin()+index-1);
    }
    
    void updateTask(int index, string eventdescription, int starttime, int endtime, int day, int month, int year){
        
        _tasklist[index].setEventInformation(eventdescription);
        _tasklist[index].setStartTime(starttime);
        _tasklist[index].setEndTime(endtime);
        _tasklist[index].setDay(day);
        _tasklist[index].setMonth(month);
        _tasklist[index].setYear(year);
    }
    
    void displayTasks(){
            for (unsigned i=0; i< _tasklist.size();i++)
            cout << (i+1) << ". " << "start time " << _tasklist[i].getStartTime() << " end time " << _tasklist[i].getEndTime() << "Event: " << _tasklist[i].getEventInformation() << endl;
    }
    
    
    void readTask(int index){
        
        cout << index << ". " << "start time " << _tasklist[index].getStartTime() << " end time " << _tasklist[index].getEndTime() << "Event: " << _tasklist[index].getEventInformation() << endl;
    }
    
    
};


#endif
