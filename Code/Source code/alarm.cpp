#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h>
#include "alarm.h"
using namespace std;

	alarm::alarm(){
		//initialize hr and min
		arraysize = 1; //1 is on default but can be changed 
					   //any more need multi-threading
		currAlarm = 0;
		is12format = true;

		hr = new int[arraysize];
		min = new int[arraysize];
		isActivated = new bool[arraysize];

		for (int i = 0; i < arraysize; i++) {
			hr[i] = 0;
			min[i] = 0; 
		}
		
	}
	
	alarm::~alarm(){

		delete [] hr;
		delete [] min;
		
	}

	void alarm::run(){
		//prints out the header	
		introMsg();
		//gets the input from users
		choice();
	}
	
	void alarm::printAlarmHeader(){
		cout << "*******************************************************************************\n";
		cout << "**************************~Simple Alarm Clock~*********************************\n";
		cout << "*******************************************************************************\n";
		
	}


	void alarm::introMsg() {
		printAlarmHeader();
		cout << "Welcome to my simple alarm clock program." << endl;
		system("pause");
		system("cls");

	}

	void alarm::choice() {

		int number_choice;

		cout << "Please choose from the following choices.\n";
		cout << "1- Set a new alarm.\n";
		cout << "2- List of alarms.\n";
		cout << "3- RELEASE THE ALARM CLOCK!\n";
		cout << "4- Setting.\n";
        cout << "5- Exit the program. \n";

		cin >> number_choice;
		system("cls");

		switch (number_choice) {
		case 1: 
				cout << "You selected 1: Set a new alarm.\n";
				setAlarm(); 
				break;

		case 2: 		
				cout << "You selected 2: List all the current alarms.\n";
				listAlarm(); 
				break;

		case 3:
				cout << "You selected 3: RELEASE THE ALARM CLOCK\n";
				startAlarm();
				break;

		case 4: 
				cout << "You selected 4: Settings\n";
				setting(); 
				break;
       
       	case 5: 
				exitMsg();
				break;

		default: cout << "Invalid choice.\n"; choice(); break;

		}


	}

	void alarm::setAlarm() {
		string userin ;
		stringstream stream1;
		int pos;
		int coloncount = 0;
		
		/*
			These are your current alarms:
			Alarm 1 : 0 : 00   Deactivated
			Alarm 2 : 0 : 00   Deactivated
			Alarm 3 : 0 : 00   Deactivated
		*/

		cout << "These are your current alarms:\n";

		for (int i = 0; i < arraysize; i++) {
			cout << "Alarm " << i + 1 << ": " << hr[i] << ":";
			if (min[i] < 10)
				cout << '0' << min[i] << "\t";
			else
				cout << min[i] << "\t";

			if (isActivated[i] == true)
				cout << "Activated\n";
			else
				cout << "Deactivated\n";
		}

		cout << "\n";
		cout << "Please enter an alarm in this format hh:mm.\n";
		cout << "The current format is ";
		if (is12format == true)
			cout << "12 hour format\n";
		else if (is12format == false)
			cout << "24 hour format\n";
		cout << "Example: 08:20. \n";

		EnterTime:
		coloncount = 0;
		cin >> userin;
		cout << userin << endl;

		//1st pass: check for letter and symbols
		for (int i = 0; i < userin.size(); i++) {
			if (userin[i] == ':')
				coloncount++; 
			else if (userin[i] < '0' || userin[i] >'9') {
				cout << "You have an invalid input\n";
				cout << "Please reenter a time that contain number between 0 and 9\n";
				goto EnterTime;
			}
		}
		if (coloncount != 1) {
			cout << "This is not a time. Please renter a time\n";
			goto EnterTime;
		}

		pos = userin.find(':');
		stream1.clear();
		stream1 << userin.substr(0, pos);
		stream1 >> hr[currAlarm];
		stream1.clear();
		stream1 << userin.substr(pos+1, userin.length()+1);
		stream1 >> min[currAlarm];
		
		//used for testing
		//cout << hr[currAlarm] << " " << min[currAlarm] << " " << pos << endl;

		//2nd pass: CHECKING TIME
		if (is12format == true) {
			//check if the hour is between 1-12
			if (hr[currAlarm] < 1 || hr[currAlarm] >12 || min[currAlarm] < 0 || min[currAlarm] > 59) {
				cout << "Invalid alarm, hour must be between 1 and 12 and min has to be between 0 and 59\n";
				cout << "please renter a time for the alarm\n";
				goto EnterTime;
			}
		}
		else if (is12format == false) {
			//check if the hour is between 0-23
			if (hr[currAlarm] < 0 || hr[currAlarm] >23 || min[currAlarm] < 0 || min[currAlarm] > 59) {
				cout << "Invalid alarm, hour must be between 0 and 23 and min has to be between 0 and 59\n";
				cout << "please renter a time for the alarm\n";
				goto EnterTime;
			}
		}
		cout << "You have set Alarm" << currAlarm+1 << " to " << hr[currAlarm] << ":" << min[currAlarm] << "\n";
		isActivated[currAlarm] = true;
		currAlarm++;
		if (currAlarm >= arraysize)
			currAlarm = 0;

		system("break");
		choice();

	}
	
	void alarm::listAlarm() {


		/* Print the message and show current alarm set if any
		------------------------------------------------------

		You selected 2: List all the current alarms.
			Alarm 1 : 0 : 00   Deactivated
			Alarm 2 : 0 : 00   Deactivated
			Alarm 3 : 0 : 00   Deactivated
		*/



		for (int i = 0; i < arraysize; i++) {
			cout << "Alarm " << i + 1 << ": " << hr[i] << ":";
			if (min[i] < 10)
				cout << '0' << min[i] << "\t";
			else
				cout << min[i] << "\t";

			if (isActivated[i] == true)
				cout << "Activated\n";
			else
				cout << "Deactivated\n";
		}
		choice();
	}

	void alarm::startAlarm() {
		time_t current_time;
		tm timeinfo;
		stringstream stream1;
		int hours;
		int mins;
		int activatedalarm = 0;
		bool getoutLoop = false;

		for (int i = 0; i < arraysize; i++) {
			if (isActivated[i] == true)
				activatedalarm++;
		}
		if (activatedalarm == 0) {
			cout << "No alarm has been activated or set. Please set an alarm in option 1.\n";
			choice();
		}

		cout << "Starting alarms!\n";
		for (int i = 0; i < arraysize; i++) {
			cout << "Alarm " << i + 1 << ": " << hr[i] << ":";
			if (min[i] < 10)
				cout << '0' << min[i] << "\t";
			else
				cout << min[i] << "\t";

			if (isActivated[i] == true)
				cout << "Activated\n";
			else
				cout << "Deactivated\n";
		}

		while (true) {
			time(&current_time);
			timeinfo = *localtime(&current_time);

			cout << timeinfo.tm_hour << ":" << timeinfo.tm_min << endl;

			if (is12format == true) {
				stream1.clear();
				stream1 << timeinfo.tm_hour;
				stream1 >> hours;
				if (hours > 12)
					hours -= 12;
				stream1.clear();
				stream1 << timeinfo.tm_min;
				stream1 >> mins;
				stream1.clear();
			}
			cout << hours << ":" << mins << endl;
			for (int i = 0; i < arraysize; i++) {
				//check for the alarm
				if (hr[i] == hours && min[i] == mins && isActivated[i] == true) {
					//play sound and wait for user response to stop the sound
					cout << "Alarm found!\n\a";
					isActivated[i] = false;
					//PlaySound("$(SolutionDir)/Alarm_v1/Loud_Alarm_Clock_Buzzer.mp3", 0, 0);
					getoutLoop = true;
					break;
				}
				
			}
			if (getoutLoop == true)
				break;
			Sleep(30000);
		}
		choice();
	}
	
    void alarm::setting(){
		int settingChoice;
		
		cout << "These are your current options\n";
		
		cout << "1. Change to a 12 or 24 hour format - Current format is ";
		if (is12format == true)
			cout << "12 hour format\n";
		else
			cout << "24 hour format\n";

		cin >> settingChoice;
		switch (settingChoice) {
			case 1:
				system("cls");
				cout << "You have selected 1: changing hour format\n";
				cout << "Current hour format is 24 hours\n";
				is12format = false;
				choice();
				break;
			default:
				system("cls");
				cout << "Incorrect choice, please reenter choice\n";
				setting();
				break;
		}

    }
    
	void alarm::exitMsg() {
		printAlarmHeader();
		cout << "Thank you for using the Simple Alarm Clock program!" << endl;
		cout << "test" << endl;
		system("pause");
	
	}

