#include <iostream>
#include <ctime>

using namespace std;


int main (){
	time_t now_time=time(0);
	struct tm *timeinfo;
	timeinfo=localtime(&now_time);
	cout<< asctime(timeinfo);
	int year;
	int month;
	int day;
	
	year = 1900 + timeinfo->tm_year;
	month = 1 + timeinfo->tm_mon;
	day = timeinfo->tm_mday;
	cout << "year  " << year <<endl;
	cout << "month  " << month << endl;
	cout << "day  " << day << endl;
	
	
	return 0;
	
	
	
	
	
}
