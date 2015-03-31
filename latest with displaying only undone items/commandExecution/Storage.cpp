//
//  storage.cpp
//  storage
//
//  Created by wangjiexuan on 31/3/15.
//  Copyright (c) 2015 wang. All rights reserved.
//
#include<iostream>
#include "storage.h"

using namespace std;
Storage::Storage(){
	bool undoOnce=false;

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
        int unit=-1;
        int mark=0;
        while(getline(readFile,line)){
            istringstream in(line);
            in>>month;
            if(in>>day){
                in>>starttime>>endtime;
                in>>unit;
                in>>mark;
                in>>dummy;
                firstChar=line.find(dummy);
                lastChar=line.find_last_not_of(" ");
                eventdescription=line.substr(firstChar,lastChar-firstChar+1);
                Task newTask(eventdescription, starttime, endtime, day, month, year,unit);
                taskLists.push_back(newTask);
            }
            else{
                totalUnits=month;
            }
        }
        readFile.close();
    }
    else{
        totalUnits=0;
    }
};

Task Storage::getTask(int index){
    return taskLists[index];
}

void Storage::addTask(string eventdescription, int starttime, int endtime, int day, int month, int year){
    totalUnits++;
    Task newTask(eventdescription, starttime, endtime, day, month, year,totalUnits);
    taskLists.push_back(newTask);
}

void Storage::deleteTask(int index){
    for(unsigned int i=0;i<taskLists.size();i++)
    {
        if(index==taskLists[i].getUnit())
            taskLists.erase(taskLists.begin()+i);
    }
}

void Storage::updateTask(int index, string eventdescription, int starttime, int endtime, int day, int month, int year){
    
    taskLists[index-1].setEventInformation(eventdescription);
    taskLists[index-1].setStartTime(starttime);
    taskLists[index-1].setEndTime(endtime);
    taskLists[index-1].setDay(day);
    taskLists[index-1].setMonth(month);
    taskLists[index-1].setYear(year);
}

string Storage::displayTasks(){
    ostringstream out;
    out << "Displaying:" << endl;
    
    for (unsigned i=0; i< taskLists.size();i++){
		if (taskLists[i].getMark()==0){
        out << (i+1) << ". " << " month: " << taskLists[i].getMonth() << " day: " << taskLists[i].getDay() << " start time" << taskLists[i].getStartTime() << " end time" << taskLists[i].getEndTime() <<" unit number: "<<taskLists[i].getUnit();
        if(taskLists[i].getMark()==0)
            out<<" status: "<<"undone";
        else
			//not actually useful as only undone work is shown and displayed
            out<<" status "<<"done";
        out<<" Event: " << taskLists[i].getEventInformation() << endl;
		}
    }
    return out.str();
}


string Storage::readTask(int index){
    ostringstream out;
    out << index << ". " << " start time " << taskLists[index].getStartTime() << " end time " << taskLists[index].getEndTime() << " Event: " << taskLists[index].getEventInformation() << endl;
    return out.str();
}

string Storage::searchTask(string content){
    vector<Task>::iterator iter;
    string line;
    ostringstream out;
    int i=1;
    for(iter = taskLists.begin();iter != taskLists.end();iter++){
        line=(*iter).getEventInformation();
        if(line.find(content) != string::npos){
            out << i << ". " << " month: " << (*iter).getMonth() << " day: " << (*iter).getDay() << " start time " <<(*iter).getStartTime() << " end time " << (*iter).getEndTime() <<" unit number: "<<(*iter).getUnit();
            if((*iter).getMark()==0)
                out<<" status: "<<"undone";
            else
                out<<" status "<<"done";
            out<<" Event: " << (*iter).getEventInformation() << endl;
            i++;
        }
    }
    if(i==1)
        out<< "no match!"<<endl;
    return out.str();
}

void Storage::writeIntoFile(){
    vector<Task>::iterator iter;
    string line;
    if (std::ifstream(fileName.c_str())){
        remove(fileName.c_str());
    }
    writeFile.open(fileName.c_str());
    for(iter = taskLists.begin();iter != taskLists.end();iter++){
        writeFile << (*iter).getMonth() <<" " << (*iter).getDay() << " " <<(*iter).getStartTime() << " " << (*iter).getEndTime() << " " <<(*iter).getUnit()<<" "<<(*iter).getMark()<<" "<<(*iter).getEventInformation() << "\r\n";
    }
    writeFile.close();
}

string Storage::changeFileLocation(string newlocation){
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
        writeFile << (*iter).getMonth() <<" " << (*iter).getDay() << " " <<(*iter).getStartTime() << " " << (*iter).getEndTime() << " " <<(*iter).getUnit()<<" " <<(*iter).getMark()<<" "<< (*iter).getEventInformation() << "\r\n";
    }
    writeFile.close();
    return "Changed File Location to " + newlocation + "\r\n";
}

void Storage::copyTaskLists(){
    previousTaskLists.clear();
    
    for (unsigned int i=0; i<taskLists.size();i++)
        previousTaskLists.push_back(taskLists[i]);
    
    
}

void Storage::undoCommand(){
    vector<Task> tempTaskLists;
    tempTaskLists.clear();
    
    vector<Task> tempPreviousTaskLists;
    tempPreviousTaskLists.clear();
    
    for (unsigned int i=0; i<taskLists.size();i++)
        tempTaskLists.push_back(taskLists[i]);
    


    for (unsigned int i=0; i<previousTaskLists.size();i++)
        tempPreviousTaskLists.push_back(previousTaskLists[i]);

    taskLists.clear();
    previousTaskLists.clear();
    
    
    for (unsigned int i=0; i<tempTaskLists.size();i++)
        previousTaskLists.push_back(tempTaskLists[i]);

    for (unsigned int i=0; i<tempPreviousTaskLists.size();i++)
        taskLists.push_back(tempPreviousTaskLists[i]);

}

void Storage::operateExit(){
    writeFile.open(fileName.c_str(), std::ios_base::app);
    writeFile<<totalUnits;
    writeFile.close();
    exit(0);
}

void Storage::operateMark(int index){
    for(unsigned int i=0;i<taskLists.size();i++)
    {
        if(index==taskLists[i].getUnit()){
            taskLists[i].setMark(1);
        }
    }
}

bool Storage::getUndoStatus(){
	return undoOnce;
}

void Storage::setUndoStatus(bool status){
	undoOnce=status;
}
