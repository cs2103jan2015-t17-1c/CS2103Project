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

using namespace std;

class Storage{
    
private:
    vector<Task> taskLists;
    vector<Task> previousTaskLists;
	ifstream readFile;
    string fileName;
	ofstream writeFile;

    
public:
    Storage(){
		fileName="Easicalendar.txt";
		if (std::ifstream("location.txt")){
		string location;
		readFile.open("location.txt");
		readFile>>location;
		SetCurrentDirectoryA(location.c_str());
		readFile.close();
	    }
		if(std::ifstream(fileName.c_str())){
		readFile.open(fileName.c_str());
		string line;
		string dummy;
		int firstChar;
		int lastChar;
		string eventdescription;
		int starttime=-1;
		int endtime=-1;
		int day=-1;
		int month=-1;
		int year=-1;
		while(getline(readFile,line)){
		istringstream in(line);
		in>>month>>day>>starttime>>endtime;
		in>>dummy;
        firstChar=line.find(dummy);
	    lastChar=line.find_last_not_of(" ");
        eventdescription=line.substr(firstChar,lastChar-firstChar+1);
		Task newTask(eventdescription, starttime, endtime, day, month, year);
		taskLists.push_back(newTask);
		}
		readFile.close();
		}
    };
    
    Task getTask(int index){
        return taskLists[index];
    }
    
    void addTask(string eventdescription, int starttime, int endtime, int day, int month, int year){
        Task newTask(eventdescription, starttime, endtime, day, month, year);
        taskLists.push_back(newTask);
    }
    
    void deleteTask(int index){
        taskLists.erase(taskLists.begin()+index-1);
    }
    
    void updateTask(int index, string eventdescription, int starttime, int endtime, int day, int month, int year){
        
        taskLists[index-1].setEventInformation(eventdescription);
        taskLists[index-1].setStartTime(starttime);
        taskLists[index-1].setEndTime(endtime);
        taskLists[index-1].setDay(day);
        taskLists[index-1].setMonth(month);
        taskLists[index-1].setYear(year);
    }
    
    string displayTasks(){
        ostringstream out;
        out << "Displaying:" << endl;
        
        for (unsigned i=0; i< taskLists.size();i++){
            out << (i+1) << ". " << " month: " << taskLists[i].getMonth() << " day: " << taskLists[i].getDay() << " start time" << taskLists[i].getStartTime() << " end time" << taskLists[i].getEndTime() << " Event: " << taskLists[i].getEventInformation() << endl;
        }
        return out.str();
    }
    
    
    string readTask(int index){
        ostringstream out;
        out << index << ". " << " start time " << taskLists[index].getStartTime() << " end time " << taskLists[index].getEndTime() << " Event: " << taskLists[index].getEventInformation() << endl;
        return out.str();
    }
    
      string searchTask(string content){
	    vector<Task>::iterator iter;
		string line;
		ostringstream out;
		int i=1;
		for(iter = taskLists.begin();iter != taskLists.end();iter++){
			line=(*iter).getEventInformation();
			if(line.find(content) != string::npos){
            out << i << ". " << " month: " << (*iter).getMonth() << " day: " << (*iter).getDay() << " start time£º " <<(*iter).getStartTime() << " end time£º " << (*iter).getEndTime() << " Event: " << (*iter).getEventInformation() << endl;
            i++;
			}
		}
		if(i==1)
			out<< "no match!"<<endl;
		 return out.str();
	}

	 void writeIntoFile(){
		vector<Task>::iterator iter;
		string line;
		if (std::ifstream(fileName.c_str())){
	    remove(fileName.c_str());
		}
		writeFile.open(fileName.c_str()); 
		for(iter = taskLists.begin();iter != taskLists.end();iter++){
             writeFile << (*iter).getMonth() <<" " << (*iter).getDay() << " " <<(*iter).getStartTime() << " " << (*iter).getEndTime() << " " << (*iter).getEventInformation() << "\r\n";
		}
		writeFile.close();
	}

	 string changeFileLocation(string newlocation){
		string line;
		remove("location.txt");
		writeFile.open("location.txt"); 
		writeFile<<newlocation;
		writeFile.close();
		vector<Task>::iterator iter;
	    remove(fileName.c_str());
		SetCurrentDirectoryA(newlocation.c_str());
		writeFile.open(fileName.c_str()); 
		for(iter = taskLists.begin();iter != taskLists.end();iter++){
             writeFile << (*iter).getMonth() <<" " << (*iter).getDay() << " " <<(*iter).getStartTime() << " " << (*iter).getEndTime() << " " << (*iter).getEventInformation() << "\r\n";
		}
		writeFile.close();
		return "Changed File Location to " + newlocation + "\r\n";
	 }

	void copyTaskLists(){
		previousTaskLists.clear();

		for (unsigned int i=0; i<taskLists.size();i++)
		previousTaskLists.push_back(taskLists[i]);


	}

	void undoCommand(){
		vector<Task> tempTaskLists;
		tempTaskLists.clear();

		vector<Task> tempPreviousTaskLists;
		tempPreviousTaskLists.clear();
		
		for (unsigned int i=0; i<taskLists.size();i++)
		tempTaskLists.push_back(taskLists[i]);
		
		for (unsigned int i=0; i<previousTaskLists.size();i++)
		tempPreviousTaskLists.push_back(taskLists[i]);

		taskLists.clear();
		previousTaskLists.clear();

		
		for (unsigned int i=0; i<tempTaskLists.size();i++)
		previousTaskLists.push_back(tempTaskLists[i]);
		
		for (unsigned int i=0; i<tempPreviousTaskLists.size();i++)
		taskLists.push_back(tempPreviousTaskLists[i]);
		
	}



};


#endif
