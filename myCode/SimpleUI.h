/*
 * SimpleUI.h
 *
 * Author: devma
 */

#ifndef SIMPLEUI_H_
#define SIMPLEUI_H_

#include <Poco/Data/Time.h>
#include <Poco/Data/Date.h>

#include "StudentDb.h"
#include "WeeklyCourse.h"
#include "BlockCourse.h"
#include "Student.h"

/**
 * @class SimpleUI
 * @brief This class forms the View and Controller of this StudentDB project
 * This class has a run time execution which interats with the user to read and
 * write data from the console, file and webserver
 *
 */
class SimpleUI
{
private:

	/**@brief Pointer to the StudentDB class*/
	StudentDb* db;

public:

    /**
     * @brief Constructor for SimpleUI class.
     * @param db Pointer to the Database class for accesing various
     * functionality.
     */
	SimpleUI(StudentDb* db);

    /**
     * @brief Run time execution of the program and creates a user interface and
     * real time prompting and corresponding actions
     */
	void run();

    /**
     * @brief Destructor for SimpleUI class.
     */
	virtual ~SimpleUI();

};

#endif /* SIMPLEUI_H_ */
