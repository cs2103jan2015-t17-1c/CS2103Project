
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
    vector<Task> _previousTaskLists;
    ifstream _readFile;
    string _fileName;
    ofstream _writeFile;
    int _totalUnits;
    bool _isUndoOnce;
  
public:

    Storage();
	bool isLocationAvailable(string fileStoringLocation);
	bool isFileAvailable(string _fileName);
	
	int getListSize();
    Task getTask(int index);
	
	void setUndoStatus(bool status);
	
	
    bool isMarkEqualsOne(int indexOfTask);
	bool isMarkEqualsZero(int indexOfTask);
	bool isScheduleTask(int startYear,int endYear);
	bool isDeadlineTask(int startYear,int endYear);
	bool isWithinRange(unsigned int index, unsigned int maximumSize);
	bool isEqualsIndex(int currentIndex, int targetIndex);
	bool isDatePast(int dayRecorded,int monthRecorded,int yearRecorded,int dayCurrent,int monthCurrent, int yearCurrent);
    
	void trackFloatingTask(ostringstream &outMessage, int unitIndex);
	void trackDeadlineTask(ostringstream &outMessage,int unitIndex);
	void trackScheduleTask(ostringstream &outMessage,int unitIndex);
	bool isValidIndex(int index);

	



	void addTask(string eventdescription, int starttime, int startday, int startmonth, int startyear, int endtime, int endday, int endmonth, int endyear);
    void deleteTask(int index);
	bool isUpdatedTask(int index, string eventdescription, int starttime, int startday, int startmonth,int startyear, int endtime, int endday, int endmonth, int endyear);
    
	string displayTasks();
	void displayFloatingTask(ostringstream &outMessage, Task &task);
	void displayDeadlineTask(ostringstream &outMessage,Task &task);
	void displayScheduleTask(ostringstream &outMessage,Task &task);
	bool isOverDue(Task &task); 
   
	string readTask(int index);
	string searchTask(string content);
	bool isFoundInList(int searchPosition);
    
	void writeIntoFile();
    void writeOneTaskToFile(vector<Task>::iterator &iter);
    string changeFileLocation(string newlocation);
    
	void copyTaskLists();
    void undoCommand();
    void operateExit();
		
	
	void Tasks();
	bool Storage::isSortNeeded(int endTime1,int endTime2);
	
	void operateMark(int index);
	void operateUnmark(int index);
    string trackTasks();
	void setDueStatusIfDayPast();
	void sortTasks();
	

	//function added or changed for unit testing
	int getSize();
	bool getIsUndoStatus();
};





#endif
