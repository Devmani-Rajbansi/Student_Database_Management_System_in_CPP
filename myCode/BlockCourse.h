/*
 * BlockCourse.cpp
 *
 * Author: devma
 */

#ifndef BLOCKCOURSE_H_
#define BLOCKCOURSE_H_

#include <iostream>

#include <Poco/Data/Time.h>
#include <Poco/Data/Date.h>
#include "Course.h"

/**
 * @class BlockCourse
 * @brief Represents the Blocked Courses and a derieved class of Course
 * These copurses have a fixed time block on the calender thus they have start
 * and end date
 *
 */
class BlockCourse: public Course
{
private:

	/**@brief represents the start date of Block course*/
	Poco::Data::Date startDate;

	/**@brief represents the end date of Block course*/
	Poco::Data::Date endDate;


	/**@brief Represnts the start time when course lecture is conducted*/
	Poco::Data::Time startTime;

	/**@brief Represnts the end time when course lecture is finishes*/
	Poco::Data::Time endTime;

public:

	/**
	 * @brief Constructor of the BlockCourse Class
	 *
	 * @param title Title/Name of the course
	 * @param creditPoints Number of CP allocated for the course
	 * @param courseKey The short key code of the course
	 * @param majorInString Name of the Major in string
	 * @param startDate Starting date of the course
	 * @param endDate Starting date of the course
	 * @param startTime Starting time of lecture of the course
	 * @param endDate Ending time of lecture of the course
	 */
	BlockCourse(unsigned int courseKey,std::string title,std::string majorInString,
			float creditPoints,	Poco::Data::Date startDate, Poco::Data::Date endDate,
			Poco::Data::Time startTime,Poco::Data::Time endTime);

    /**
     * @brief Constructor of the BlockCourse Class
     * @param The input stream from which BlockCourse data is read.
     */
	BlockCourse(std::istream &in);

	/**
	* @brief Write the content of the BlockCourse in an output stream
	*
	* @param Reference of type ostream
	*/
	void write(std::ostream &out) const;

    /**
     * @brief Function for input stream of BlockCourse data.
     * @param The input stream from which BlockCourse data is read.
     */
	void read(std::istream &in);

};

#endif /* BLOCKCOURSE_H_ */
