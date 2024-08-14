//============================================================================
// Name        : Student Database
// Author      : Devmani Rajbansi
// Version     :
// Copyright   : The source code can be used free of cost
// Description : This project emulates a student database with read/write
// capabilies from a file and server interaction over TCP network
//============================================================================
// Standard (system) header files
#include <iostream>

using std::cout;
using std::endl;

// My Project's header files
#include"Course.h"
#include"Student.h"
#include"Address.h"
#include"SimpleUI.h"
#include"StudentDb.h"
#include"Enrollment.h"

/*Main program for run time executoion*/
int main ()
{
	StudentDb dbObj;
	SimpleUI uiObj(&dbObj);
	uiObj.run();

	cout << "\n Closing the StudentDB." << endl;
	return 0;
}

