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
		int endday=-1;
		int endmonth=-1;
		int endyear=-1;
        int startday=-1;
        int startmonth=-1;
        int startyear=-1;
        int unit=-1;
        int mark=0;
        while(getline(readFile,line)){
				istringstream in(line);
				in >> starttime;
				in >> startday;
				in >> startmonth;
				in >> startyear;
				in >>endtime;
				in >>endday;
				in >>endmonth;
				in >>endyear;
				in >>unit;
				in >> mark;
				in>>dummy;
				firstChar=line.find(dummy);
				lastChar=line.find_last_not_of(" ");
				eventdescription=line.substr(firstChar,lastChar-firstChar+1);
                Task newTask(eventdescription, starttime, startday, startmonth, startyear, endtime, endday, endmonth, endyear, unit, mark);
                taskLists.push_back(newTask);
            }   


        int tempLargestUnit=0;
		for (unsigned int i=0; i<taskLists.size();i++){
			if(taskLists[i].getUnit() > tempLargestUnit){
				tempLargestUnit=taskLists[i].getUnit();
			}
        totalUnits=tempLargestUnit;
		}
        readFile.close();
	}
	else{
		totalUnits = 0;
	}
};

Task Storage::getTask(int index){
    return taskLists[index];
}

void Storage::addTask(string eventdescription, int starttime, int startday, int startmonth, int startyear, int endtime, int endday, int endmonth, int endyear){
    totalUnits++;
    Task newTask(eventdescription, starttime, startday, startmonth, startyear, endtime, endday, endmonth, endyear,totalUnits);
    taskLists.push_back(newTask);
}


bool Storage::deleteTask(int index){
	unsigned int i;
    for(i=0;i<taskLists.size();i++)
    {
        if(index==taskLists[i].getUnit()){
            taskLists.erase(taskLists.begin()+i);
			return true;
		}
    }
	return false;
 
}

void Storage::updateTask(int index, string eventdescription, int starttime, int startday, int startmonth,int startyear, int endtime, int endday, int endmonth, int endyear){
    
	int i=0;
	while(taskLists[i].getUnit() == index){
	i++;
	}
	
    taskLists[i-1].setEventInformation(eventdescription);
    taskLists[i-1].setStartTime(starttime);
    taskLists[i-1].setStartDay(startday);
    taskLists[i-1].setStartMonth(startmonth);
    taskLists[i-1].setStartYear(startyear);
	taskLists[i-1].setEndTime(endtime);
	taskLists[i-1].setEndDay(endday);
	taskLists[i-1].setEndMonth(endmonth);
	taskLists[i-1].setEndYear(endyear);
}

string Storage::displayTasks(){
    ostringstream out;
    out << "Displaying:" << endl;
	int indexNumber=1;
    
    for (unsigned i=0; i< taskLists.size();i++){
		if (taskLists[i].getMark()==0){
        out << indexNumber << ". " << " Start Year: " << taskLists[i].getStartYear() << " Start Month: " << taskLists[i].getStartMonth() << " Start Day: " << taskLists[i].getStartDay() << " Start Time: " << taskLists[i].getStartTime() << " End Year: " << taskLists[i].getEndYear() << " End Month: " << taskLists[i].getEndMonth()<< " End Day: " << taskLists[i].getEndDay() << " End Time: " << taskLists[i].getEndTime() <<" unit number: "<<taskLists[i].getUnit()<<" status: "<<"undone"<<" Event: " << taskLists[i].getEventInformation() << endl;
		indexNumber++;
		}
    }
    return out.str();
}

string Storage::trackTasks(){
    ostringstream out;
    out << "Tracking:" << endl;
    int indexNumber=1;
    
    for (unsigned i=0; i< taskLists.size();i++){
		if (taskLists[i].getMark()==1){
        out << indexNumber << ". " << " Start Year" << taskLists[i].getStartYear() << " Start Month: " << taskLists[i].getStartMonth() << " Start Day: " << taskLists[i].getStartDay() << " Start Time " << taskLists[i].getStartTime() << " End Year" << taskLists[i].getEndYear() << " End Month: " << taskLists[i].getEndMonth()<< " End Day: " << taskLists[i].getEndDay() << " End Time" << taskLists[i].getEndTime() <<" unit number: "<<taskLists[i].getUnit()<<" status: "<<"done"<<" Event: " << taskLists[i].getEventInformation() << endl;
		indexNumber++;
		}
    }
    return out.str();
}


string Storage::readTask(int index){
    ostringstream out;
    //Temporarily disable the function of readTask because it is already shown in display
	if (totalUnits>=index){
		out << index << ". " << taskLists[index-1].getEventInformation() << "\r\n";
	}
	else 
		out<<"No Task to display";
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
            out << i << ". " << " Start Year" << (*iter).getStartYear() << " Start Month: " << (*iter).getStartMonth()<<" Start Day: "<<(*iter).getStartDay() << " Start Time " <<(*iter).getStartTime() <<" End Year" << (*iter).getEndYear() << " End Month: " << (*iter).getEndMonth()<< " End Day: " << (*iter).getEndDay() << " End Time" << (*iter).getEndTime() <<" unit number: "<<(*iter).getUnit(); 
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
        writeFile << (*iter).getStartYear() <<" " << (*iter).getStartMonth()<<" "<< (*iter).getStartDay() << " " <<(*iter).getStartTime() <<" "<< (*iter).getEndYear() <<" " << (*iter).getEndMonth()<<" "<< (*iter).getEndDay()<<" " << (*iter).getEndTime() << " " <<(*iter).getUnit()<<" "<<(*iter).getMark()<<" "<<(*iter).getEventInformation() << "\r\n";
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
        writeFile << (*iter).getStartYear() <<" " << (*iter).getStartMonth()<<" "<< (*iter).getStartDay() << " " <<(*iter).getStartTime() <<" "<< (*iter).getEndYear() <<" " << (*iter).getEndMonth()<<" "<< (*iter).getEndDay()<<" " << (*iter).getEndTime() << " " <<(*iter).getUnit()<<" "<<(*iter).getMark()<<" "<<(*iter).getEventInformation() << "\r\n";
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
   /* writeFile.open(fileName.c_str(), std::ios_base::app);
    writeFile<<totalUnits;
    writeFile.close();*/
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

void Storage::operateUnmark(int index){
	 for(unsigned int i=0;i<taskLists.size();i++)
    {
        if(index==taskLists[i].getUnit()){
            taskLists[i].setUnmark(0);
        }
    }
}
bool Storage::getUndoStatus(){
	return undoOnce;
}

void Storage::setUndoStatus(bool status){
	undoOnce=status;
}

