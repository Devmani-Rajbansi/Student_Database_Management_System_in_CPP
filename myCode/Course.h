/*
 * Course.h
 *
 * Author: devma
 */

#ifndef COURSE_H_
#define COURSE_H_

#include <map>
#include <string>
#include <Poco/Data/Time.h>
#include <Poco/Data/Date.h>


/**
 * @class Course
 * @brief Represents the Courses in a university which a student can opt
 *
 * This class has methods to get the details of the course such as title,
 * credit points, courseKey and major
 */
class Course
{
private:

	/**@brief Static map for mapping the internal major
	 * with external majorInString*/
	static std::map<unsigned char,std::string> majorById;

	/**@brief Key/short name of the course*/
	unsigned int courseKey;

	/**@brief Title of the course*/
	std::string title;

	/**@brief Internal stored name of the major*/
	unsigned char major;

	/**@brief Credit Points defined for the course*/
	float creditPoints;

public:


    /**
     * @brief Default Constructor for the Course class.
     */
	Course();

	/**
	 * @fn Course(string title,float creditPoints, unsigned int courseKey,
	 * string majorInString )
	 * @brief Constructor of the Course Class
	 *
	 * @param title Title/Name of the course
	 * @param creditPoints Number of CP allocated for the course
	 * @param courseKey The short key code of the course
	 * @param majorInString Name of the Major in string
	 */
	Course( unsigned int courseKey,std::string title,std::string majorInString,
				float creditPoints);

    /**
     * @brief Destructor for the Course class.
     */
	virtual ~Course();

	/**
	* @fn unsigned int getCourseKey() const
	* @brief Gets the courseKey of the course
	*
	* @return The number of course Key of the course
	*/
	unsigned int getCourseKey() const;

	/**
	* @fn float getCreditPoints() const
	* @brief Gets the creditPoints allocated for the course
	*
	* @return The creditPoints of the course
	*/
	float getCreditPoints() const;

	/**
	* @fn std::string getMajor() const
	* @brief gets the mapped string value of the major
	*
	* @return The mapped value of the majorById data member
	*/
	std::string getMajor() const;

	/**
	* @fn const std::string& getTitle() const
	* @brief Gets the Title of the course
	*
	* @return The Title of the course
	*/
	const std::string& getTitle() const;

	/**
	* @brief Function to write the content of the Course in the file
	*
	* @param Reference of type ostream
	*/
	virtual void write(std::ostream& out) const;

    /**
     * @brief Function for input stream of Course data.
     * @param The input stream from which course data is read.
     */
	virtual void read(std::istream& in);

};

#endif /* COURSE_H_ */
