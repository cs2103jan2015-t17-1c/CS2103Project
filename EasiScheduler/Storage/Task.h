//

//  Header.h

//  Task

//

//  Created by Xu Meng on 10/3/15.

//  Copyright (c) 2015 Xu Meng. All rights reserved.

//



#ifndef Task_h

#define Task_h

#include <string>



using namespace std;



class Task{

private:

    int _starttime;

    int _endtime;

    string _eventdescription;

    int _day;

    int _month;

    int _year;

public:

 

    Task(){

        _starttime=-1;

        _endtime=-1;

        _eventdescription="EMPTY";

        _day=-1;

        _month=-1;

        _year=-1;

    }

    

    Task(string eventdescription,  int starttime, int endtime, int day, int month, int year){

        _starttime=starttime;

        _endtime=endtime;

        _eventdescription=eventdescription;

        _day=day;

        _month=month;

        _year=year;

    }

    

    string getEventInformation(){

        return _eventdescription;

    }

    

    int getEndTime(){

        return _endtime;

    }

    

    int getStartTime(){

        return _starttime;

    }

    

    int getDay(){

        return _day;

    }

    

    int getMonth(){

        return _month;

    }

    int getYear(){

        return _year;

    }

    

    void setEventInformation(string eventdescription){

        _eventdescription = eventdescription;

    }

    

    void setEndTime(int endtime){

        _endtime=endtime;

    }

    

    void setStartTime(int starttime){

        _starttime=starttime;

    }

    

    void setDay(int day){

        _day=day;

    }

    

    void setMonth(int month){

        _month=month;

    }

    void setYear(int year){

        _year=year;

    }

    

    

    

    

};











#endif

