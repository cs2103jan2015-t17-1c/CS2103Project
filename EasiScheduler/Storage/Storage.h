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

#include "Task.h"



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

        

        _tasklist[index-1].setEventInformation(eventdescription);

        _tasklist[index-1].setStartTime(starttime);

        _tasklist[index-1].setEndTime(endtime);

        _tasklist[index-1].setDay(day);

        _tasklist[index-1].setMonth(month);

        _tasklist[index-1].setYear(year);

    }

    

    string displayTasks(){

        ostringstream out;

        out << "Displaying:" << "\r\n";

        

        for (unsigned i=0; i< _tasklist.size();i++){

            out << (i+1) << ". " << " month: " << _tasklist[i].getMonth() << " day: " << _tasklist[i].getDay() << " start time" << _tasklist[i].getStartTime() << " end time" << _tasklist[i].getEndTime() << " Event: " << _tasklist[i].getEventInformation() << "\r\n";

        }

        return out.str();

    }

    

    

    string readTask(int index){

        ostringstream out;

        out << index << ". " << " start time " << _tasklist[index].getStartTime() << " end time " << _tasklist[index].getEndTime() << " Event: " << _tasklist[index].getEventInformation() << "\r\n";

        return out.str();

    }

    

      string searchTask(string content){

	    vector<Task>::iterator iter;

		string line;

		ostringstream out;

		int i=1;

		for(iter = _tasklist.begin();iter != _tasklist.end();iter++){

			line=(*iter).getEventInformation();

			if(line.find(content) != string::npos){

            out << i << ". " << " month: " << (*iter).getMonth() << " day: " << (*iter).getDay() << " start time£∫ " <<(*iter).getStartTime() << " end time£∫ " << (*iter).getEndTime() << " Event: " << (*iter).getEventInformation() << "\r\n";

            i++;

			}

		}

		if(i==1)

			out<< "no match!";

		 return out.str();

	}

};









#endif

