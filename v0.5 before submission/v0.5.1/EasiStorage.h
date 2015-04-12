#pragma once
//@Hu Zhujun A0119426E
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <windows.h>
#include <stdlib.h>
#include <algorithm>
#include "Task.h"
#include "CurrentTime.h"

using namespace std;

class EasiStorage{
private:
    vector<Task> _taskLists;
    vector<Task> _previousTaskLists;
    ifstream _readFile;
    string _fileName;
    ofstream _writeFile;
    int _totalUnits;
    bool _isUndoOnce;
	int _indicatorOfEmptyInput;

public:

    EasiStorage();

	bool isLocationAvailable(string fileStoringLocation);
	bool isFileAvailable(string _fileName);
    bool isMarkEqualsOne(int indexOfTask);
	bool isMarkEqualsZero(int indexOfTask);
	bool isScheduleTask(int startYear,int endYear);
	bool isDeadlineTask(int startYear,int endYear);
	bool isWithinRange(unsigned int index, unsigned int maximumSize);
	bool isEqualsIndex(int currentIndex, int targetIndex);
	bool isDatePast(int dayRecorded, int monthRecorded, int yearRecorded, int dayCurrent, int monthCurrent, int yearCurrent);
    bool isValidIndex(int index);
	bool isUpdatedTask(int index, string eventdescription, int starttime, int startday, int startmonth,int startyear, int endtime, int endday, int endmonth, int endyear);
    bool isOverDue(Task & task); 
	bool isSortNeeded(int endTime1, int endTime2);
	bool isFoundInList(int searchPosition);
	bool isUndoStatus();
		
	void setUndoStatus(bool status);
	void trackFloatingTask(ostringstream &outMessage, int unitIndex);
	void trackDeadlineTask(ostringstream &outMessage,int unitIndex);
	void trackScheduleTask(ostringstream &outMessage,int unitIndex);
	void addTask(string eventdescription, int starttime, int startday, int startmonth, int startyear, int endtime, int endday, int endmonth, int endyear);
    void deleteTask(int index);		
	void displayFloatingTask(ostringstream &outMessage, Task &task);
	void displayDeadlineTask(ostringstream &outMessage,Task &task);
	void displayScheduleTask(ostringstream &outMessage,Task &task);
	void displaySearchedFloatingTask(ostringstream &outMessage, Task &task);
	void displaySearchedDeadlineTask(ostringstream &outMessage,Task &task);
	void displaySearchedScheduleTask(ostringstream &outMessage,Task &task);
	void writeIntoFile();
    void writeOneTaskToFile(vector<Task>::iterator &iter);
	void operateMark(int index);
	void operateUnmark(int index);
	void setDueStatusIfDayPast();
	void sortTasks();
	void copyTaskLists();
    void undoCommand();
    void operateExit();		
	void verifyTotalUnit();
	void Tasks();
	
	Task getTask(int index);

	string getTrackTasks();
	string getReadTask(int index);
	string getSearchTask(string content);
	string getDisplayTasks();
    string getChangeFileLocation(string newLocation);

	//function added or changed for unit testing
	int getListSize();
	int getTotalUnit();
	
};



