/*
 * WeeklyCourse.h
 *
 * Author: devma
 */

#ifndef WEEKLYCOURSE_H_
#define WEEKLYCOURSE_H_

#include <iostream>

#include <Poco/Data/Time.h>
#include "Course.h"


/**
 * @class WeeklyCourse
 * @brief Represents the Weekly Courses and a derieved class of Course
 *
 * These course repeats every week and thus have weekly schedule
 */
class WeeklyCourse: public Course
{
private:

	/**@brief represnts the day of the week when course is conducted*/
	Poco::DateTime::DaysOfWeek dayOfWeek;

	/**@brief represnts the start time when course is conducted*/
	Poco::Data::Time startTime;

	/**@brief represnts the end time when course is finishes*/
	Poco::Data::Time endTime;

public:

	/**
	 * @brief Constructor of the WeeklyCourse Class
	 *
	 * @param title Title/Name of the course
	 * @param creditPoints Number of CP allocated for the course
	 * @param courseKey The short key code of the course
	 * @param majorInString Name of the Major in string
	 * @param dayOfWeek Day on which weekly the course is conducted
	 * @param startTime Starting time of lecture of the course
	 * @param endDate Ending time of lecture of the course
	 */
	WeeklyCourse(unsigned int courseKey,std::string title,std::string majorInString,
			float creditPoints,	Poco::DateTime::DaysOfWeek dayOfWeek,
			Poco::Data::Time startTime,Poco::Data::Time endTime);

    /**
     * @brief Constructor of the WeeklyCourse Class
     * @param The input stream from which WeeklyCourse data is read.
     */
	WeeklyCourse(std::istream &in);

	/**
	* @brief Write the content of the WeeklyCourse in an output stream
	*
	* @param Reference of type ostream
	*/
	void write(std::ostream &out) const;

    /**
     * @brief Function for input stream of WeeklyCourse data.
     * @param The input stream from which WeeklyCourse data is read.
     */
	void read(std::istream &in);

};

#endif /* WEEKLYCOURSE_H_ */
