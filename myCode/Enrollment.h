/*
 * Enrollment.h
 *
 * Author: devma
 */

#ifndef ENROLLMENT_H_
#define ENROLLMENT_H_

#include <string>

#include "Course.h"


/**
 * @class Enrollment
 * @brief Represents an Enrollment of the student in a specific course in
 * specific semester
 *
 */
class Enrollment
{
private:

	/**Grade scored by the student : "0" if not yet graded */
	float grade;

	/**Semester in which the student is enrolled. */
	std::string semester;

	/**Pointer to the course the student is enrolled.*/
	const Course* course;

public:

	/**
	 * @brief Constructor for the Enrollment class
	 *
	 * @param course Pointer to the course the student is enrolled
	 * @param semester Semester in which the student is enrolled.
	 */
	Enrollment(const Course* course,std::string semester);

    /**
     * @brief Destructor of the Enrollment class.
     */
	virtual ~Enrollment();

    /**
     * @brief Gets the enrolled course.
     * @return Pointer to the course enrolled.
     */
	const Course* getCourse() const;

    /**
     * @brief Gets the grade achieved in the course.
     * @return The grade scoreed by the student.
     */
	float getGrade() const;

    /**
     * @brief Gets the semester in which the student is enrolled.
     * @return The semester in which student is enrolled.
     */
	const std::string& getSemester() const;

    /**
     * @brief Sets the grade scored in the course.
     * @param grade The grade to be set.
     */
	void setGrade(float grade);

    /**
     * @brief Writes the information about the enrollment to an output stream.
     * @param out The output stream.
     */
	void write(std::ostream &out) const;

};

#endif /* ENROLLMENT_H_ */
