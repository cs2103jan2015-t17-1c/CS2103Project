//
//  storage.cpp
//  storage
//
//  Created by wangjiexuan on 31/3/15.
//  Copyright (c) 2015 wang. All rights reserved.
//
#include<iostream>
#include<iomanip>
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
		int overdue=0;
        
		while(getline(readFile,line)){
				istringstream in(line);
				in >> startyear;
				in >> startmonth;
				in >> startday;
				in >> starttime;
				in >>endyear;
				in >>endmonth;
				in >>endday;
				in >>endtime;
				in >>unit;
				in >>mark;
				in >>overdue;
				in>>dummy;
				
				firstChar=line.find(dummy);
				lastChar=line.find_last_not_of(" ");
				eventdescription=line.substr(firstChar,lastChar-firstChar+1);
                Task newTask(eventdescription, starttime, startday, startmonth, startyear, endtime, endday, endmonth, endyear, unit, mark,overdue);
                _taskLists.push_back(newTask);
            }   
        int tempLargestUnit=0;		
		for (unsigned int i=0; i< _taskLists.size();i++){
			if( _taskLists[i].getUnit() > tempLargestUnit){
				tempLargestUnit= _taskLists[i].getUnit();
			}			
			totalUnits=tempLargestUnit;
		}       
		readFile.close();



	}else{
		
		totalUnits = 0;
	}
};

Task Storage::getTask(int index){
    return  _taskLists[index];
}

void Storage::addTask(string eventdescription, int starttime, int startday, int startmonth, int startyear, int endtime, int endday, int endmonth, int endyear){
    totalUnits++;
    Task newTask(eventdescription, starttime, startday, startmonth, startyear, endtime, endday, endmonth, endyear,totalUnits);
     _taskLists.push_back(newTask);
}


bool Storage::isDeleted(int index){
	unsigned int i;
    for(i = 0; i < _taskLists.size(); i++){
        
		if(index == _taskLists[i].getUnit()){      
			_taskLists.erase(_taskLists.begin() + i);
			return true;
		}
    }
	return false;
 
}


void Storage::updateTask(int index, string eventdescription, int starttime, int startday, int startmonth,int startyear, int endtime, int endday, int endmonth, int endyear){
    
	int i=0;
	while( _taskLists[i].getUnit() != index){	
		i++;
	}

     _taskLists[i].setEventInformation(eventdescription);
     _taskLists[i].setStartTime(starttime);
     _taskLists[i].setStartDay(startday);
     _taskLists[i].setStartMonth(startmonth);
     _taskLists[i].setStartYear(startyear);
	 _taskLists[i].setEndTime(endtime);
	 _taskLists[i].setEndDay(endday);
	 _taskLists[i].setEndMonth(endmonth);
	 _taskLists[i].setEndYear(endyear);
}

string Storage::displayTasks(){

    ostringstream out;

    out << "Displaying: \r\n" ;

	checkOverdue();

    

    for (unsigned i=0; i< _taskLists.size();i++){

		if (_taskLists[i].getMark()==0){

		   if((_taskLists[i].getStartYear()!=-1)&&(_taskLists[i].getEndYear()!=-1)){

           out<< "Unit No." << setfill('0')<<setw(4)<<_taskLists[i].getUnit()<<" "<< _taskLists[i].getStartYear() << "/" <<setw(2)<< _taskLists[i].getStartMonth() << "/" <<setw(2)<< _taskLists[i].getStartDay() << "/" <<  setfill('0') << setw(4) << _taskLists[i].getStartTime() <<" - " << _taskLists[i].getEndYear() << "/" <<setw(2)<< _taskLists[i].getEndMonth()<< "/" <<setw(2)<< _taskLists[i].getEndDay() << "/" <<  setfill('0') << setw(4) << _taskLists[i].getEndTime() ;
		   if(_taskLists[i].getOverdue()==1){
		     out<<"[O] "<<" Event: " << _taskLists[i].getEventInformation() << "\r\n";
		   }else{
			 out<<"    "<<" Event: " << _taskLists[i].getEventInformation() << "\r\n";
		   }

		   }

		   else if((_taskLists[i].getStartYear()==-1)&&(_taskLists[i].getEndYear()!=-1)){

		   out<< "Unit No." <<  setfill('0') << setw(4)<<_taskLists[i].getUnit()<<" ----/--/--/---- - " << _taskLists[i].getEndYear() << "/" <<setw(2)<< _taskLists[i].getEndMonth()<< "/" <<setw(2)<< _taskLists[i].getEndDay() << "/" << setfill('0') << setw(4) << _taskLists[i].getEndTime();
		  if(_taskLists[i].getOverdue()==1){
		     out<<"[O] "<<" Event: " << _taskLists[i].getEventInformation() << "\r\n";
		   }else{
			 out<<"    "<<" Event: " << _taskLists[i].getEventInformation() << "\r\n";
		   }

		   }

		   else{

		   out<< "Unit No." <<  setfill('0') << setw(4)<<_taskLists[i].getUnit()<<" ----/--/--/---- - ----/--/--/----  " <<"    "<<" Event: " << _taskLists[i].getEventInformation() << "\r\n";

		   }

		}

    }

	

    return out.str();

}

string Storage::trackTasks(){

    ostringstream out;

    out << "Tracking:" << "\r\n";

    

    for (unsigned i=0; i< _taskLists.size();i++){

		if (_taskLists[i].getMark()==1){

		   if((_taskLists[i].getStartYear()!=-1)&&(_taskLists[i].getEndYear()!=-1)){

           out<< "Unit No." <<  setfill('0') << setw(4)<<_taskLists[i].getUnit()<<" "<< _taskLists[i].getStartYear() << "/" <<setw(2)<< _taskLists[i].getStartMonth() << "/" <<setw(2)<< _taskLists[i].getStartDay() << "/" <<  setfill('0') << setw(4) << _taskLists[i].getStartTime() <<" - " << _taskLists[i].getEndYear() << "/" <<setw(2)<< _taskLists[i].getEndMonth()<< "/" <<setw(2)<< _taskLists[i].getEndDay() << "/" <<  setfill('0') << setw(4) << _taskLists[i].getEndTime() <<"  " <<" Event: " << _taskLists[i].getEventInformation() << "\r\n";

		   }

		   else if((_taskLists[i].getStartYear()==-1)&&(_taskLists[i].getEndYear()!=-1)){

		   out<< "Unit No." <<  setfill('0') << setw(4)<<_taskLists[i].getUnit()<<" ----/--/--/---- - " << _taskLists[i].getEndYear() << "/" <<setw(2)<< _taskLists[i].getEndMonth()<< "/" <<setw(2)<< _taskLists[i].getEndDay() << "/" <<  setfill('0') << setw(4) << _taskLists[i].getEndTime() <<"  "<<" Event: " << _taskLists[i].getEventInformation() << "\r\n";

		   }

		   else{

		   out<< "Unit No." <<  setfill('0') << setw(4)<<_taskLists[i].getUnit()<<" ----/--/--/---- - ----/--/--/----  " <<" Event: " << _taskLists[i].getEventInformation() << "\r\n";

		   }

		}

    }





    return out.str();

}

string Storage::readTask(int index){
    ostringstream out;

	if (totalUnits>=index){
		out << index << ". " <<  _taskLists[index-1].getEventInformation() << "\r\n";
	}else 
		out<<"No Task to display";

	return out.str();
}

string Storage::searchTask(string content){
    
	vector<Task>::iterator iter;
    string line;
    ostringstream out;
    
	int i=1;
    
	for(iter =  _taskLists.begin();iter !=  _taskLists.end();iter++){
        line=(*iter).getEventInformation();
        if(line.find(content) != string::npos){
            out << i << ". " << " Start Year" << (*iter).getStartYear() << " Start Month: " << (*iter).getStartMonth()<<" Start Day: "<<(*iter).getStartDay() << " Start Time " <<(*iter).getStartTime() <<" End Year" << (*iter).getEndYear() << " End Month: " << (*iter).getEndMonth()<< " End Day: " << (*iter).getEndDay() << " End Time" << (*iter).getEndTime() <<" unit number: "<<(*iter).getUnit(); 
            if((*iter).getMark()==0){
                out<<" status: "<<"undone";
			}else{
                out<<" status "<<"done";
			}

			out<<" Event: " << (*iter).getEventInformation() << "\r\n";

			i++;
        }
    }    
	
	if(i==1){
        out<< "no match!"<<"\r\n";
	}
    
	return out.str();
}

void Storage::writeIntoFile(){
    
	vector<Task>::iterator iter;
    string line;
    
	if (std::ifstream(fileName.c_str())){
        remove(fileName.c_str());
    }
    
	writeFile.open(fileName.c_str());
    
	for(iter =  _taskLists.begin();iter !=  _taskLists.end();iter++){
        writeOneTaskToFile(iter);
    }
    
	writeFile.close();
}

void Storage::writeOneTaskToFile(vector<Task>::iterator &iter){
	 writeFile << (*iter).getStartYear() <<" " << (*iter).getStartMonth()<<" "<< (*iter).getStartDay() << " " <<(*iter).getStartTime() <<" "<< (*iter).getEndYear() <<" " << (*iter).getEndMonth()<<" "<< (*iter).getEndDay()<<" " << (*iter).getEndTime() << " " <<(*iter).getUnit()<<" "<<(*iter).getMark()<<" "<< (*iter).getOverdue() <<(*iter).getEventInformation() << "\r\n";
}


string Storage::changeFileLocation(string newlocation){
    
	string line;
    remove("location.txt");
    writeFile.open("location.txt");
    writeFile<<newlocation;
    writeFile.close();
    
	
    remove(fileName.c_str());
    SetCurrentDirectoryA(newlocation.c_str());
    writeFile.open(fileName.c_str());
	
	vector<Task>::iterator iter;
    for(iter =  _taskLists.begin();iter !=  _taskLists.end();iter++){
        writeOneTaskToFile(iter);
    }
    
	writeFile.close();
    
	return "Changed File Location to " + newlocation + "\r\n";
}

void Storage::copyTaskLists(){
    previousTaskLists.clear();
    
    for (unsigned int i=0; i<_taskLists.size();i++)
        previousTaskLists.push_back(_taskLists[i]);
    
    
}

void Storage::undoCommand(){
    vector<Task> temp_taskLists;
    temp_taskLists.clear();
    
    vector<Task> tempPrevious_taskLists;
    tempPrevious_taskLists.clear();
    
    for (unsigned int i=0; i<_taskLists.size();i++)
        temp_taskLists.push_back(_taskLists[i]);
    


    for (unsigned int i=0; i<previousTaskLists.size();i++)
        tempPrevious_taskLists.push_back(previousTaskLists[i]);

    _taskLists.clear();
    previousTaskLists.clear();
    
    
    for (unsigned int i=0; i<temp_taskLists.size();i++)
        previousTaskLists.push_back(temp_taskLists[i]);

    for (unsigned int i=0; i<tempPrevious_taskLists.size();i++)
        _taskLists.push_back(tempPrevious_taskLists[i]);

}

void Storage::operateExit(){
   /* writeFile.open(fileName.c_str(), std::ios_base::app);
    writeFile<<totalUnits;
    writeFile.close();*/
    exit(0);
}

void Storage::operateMark(int index){
    for(unsigned int i=0;i< _taskLists.size();i++)
    {
        if(index== _taskLists[i].getUnit()){
             _taskLists[i].setMark(1);
        }
    }
}

void Storage::operateUnmark(int index){
	 for(unsigned int i=0;i< _taskLists.size();i++)
    {
        if(index== _taskLists[i].getUnit()){
             _taskLists[i].setUnmark(0);
        }
    }
}
bool Storage::getUndoStatus(){
	return undoOnce;
}

void Storage::setUndoStatus(bool status){
	undoOnce=status;
}


void Storage::sortTasks(){

	    Task tempTask;

		if (_taskLists.size() >=1 ) {

		for (unsigned int j=0; j<_taskLists.size()-1;j++)

			for (unsigned int i=0; i<_taskLists.size()-1-j;i++){

			if(_taskLists[i].getEndTime() == -1 || ( _taskLists[i].getEndTime() > _taskLists[i+1].getEndTime()) && _taskLists[i+1].getEndTime() != -1){

				tempTask=_taskLists[i];

				_taskLists[i]=_taskLists[i+1];

				_taskLists[i+1]=tempTask;

			}

		}

		

		for (unsigned int j=0; j<_taskLists.size()-1;j++)

			for (unsigned int i=0; i<_taskLists.size()-1-j;i++){

			if(_taskLists[i].getEndDay() == -1 || (_taskLists[i].getEndDay() > _taskLists[i+1].getEndDay()) && _taskLists[i+1].getEndDay() != -1){

				tempTask=_taskLists[i];

				_taskLists[i]=_taskLists[i+1];

				_taskLists[i+1]=tempTask;

			}

		}



		for (unsigned int j=0; j<_taskLists.size()-1;j++)

			for (unsigned int i=0; i<_taskLists.size()-1-j;i++){

			if(_taskLists[i].getEndMonth() == -1 ||(_taskLists[i].getEndMonth() > _taskLists[i+1].getEndMonth()) && _taskLists[i+1].getEndMonth() != -1){

				tempTask=_taskLists[i];

				_taskLists[i]=_taskLists[i+1];

				_taskLists[i+1]=tempTask;

			}

		}



		for (unsigned int j=0; j<_taskLists.size()-1;j++)

			for (unsigned int i=0; i<_taskLists.size()-1-j;i++){

			if(_taskLists[i].getEndYear() == -1 ||(_taskLists[i].getEndYear() > _taskLists[i+1].getEndYear()) && _taskLists[i+1].getEndYear() != -1){

				tempTask=_taskLists[i];

				_taskLists[i]=_taskLists[i+1];

				_taskLists[i+1]=tempTask;

			}

		}
		}
}

void Storage::checkOverdue() {
	CurrentTime timeInfo;
	for(unsigned int i=0;i<_taskLists.size();i++){
	    if((timeInfo.getYear()>_taskLists[i].getEndYear())||(timeInfo.getYear()==_taskLists[i].getEndYear() && timeInfo.getMonth()>_taskLists[i].getEndMonth())||(timeInfo.getYear()==_taskLists[i].getEndYear() && timeInfo.getMonth()==_taskLists[i].getEndMonth() && timeInfo.getDay()>_taskLists[i].getEndDay())){
			_taskLists[i].setOverdue(1);
		}
	}

}




