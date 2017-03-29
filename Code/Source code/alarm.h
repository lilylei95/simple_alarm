#include <iostream>
#include <ctime>
using namespace std;

class alarm{
	public:

	alarm();
	~alarm();
	void run();


	private:
	void printAlarmHeader();
	void choice();
	void setAlarm();
	void listAlarm();
    void setting();
	void exitMsg();
	void introMsg();
	void startAlarm();

	//variables
	int *hr;
	int *min;
	int arraysize;
	int currAlarm;
	bool is12format;
	bool *isActivated;
	
};
