/*
 * StudentDb.h
 *
 * Author: devma
 */

#ifndef STUDENTDB_H_
#define STUDENTDB_H_

#include <map>
#include <memory>
#include <string>
#include <boost/asio.hpp>

#include "Student.h"

/**
 * @class StudentDb
 * @brief This class models the Student Database and forms the bridge between
 * the User interface and the processing of the Database
 *
 */
class StudentDb
{
private:

	/**
	 * @brief Container for storing the data of all students identified by the
	 * matrikel number*/
	std::map <int,Student> students;

	/**
	 * @brief Container for storing the data of all courses identified by the
	 * Course Key*/
	std::map <int, std::unique_ptr<const Course>> courses;

public:

    /**
     * @brief Constructor for StudentDb class.
     */
	StudentDb();

    /**
     * @brief Destructor for StudentDb class.
     */
	virtual ~StudentDb();

    /**
     * @brief Gets the map of courses.
     *
     * @return Map of courses.
     */
	const std::map<int, std::unique_ptr<const Course> >& getCourses() const;

    /**
     * @brief Get the map of students.
     *
     * @return Map of students.
     */
	const std::map<int, Student>& getStudents() const;

    /**
     * @brief Add an enrollment for a quired student.
     *
     * @param matrikelNumber Matrikel number of the student.
     * @param courseId Course ID of the Course for the enrollment.
     * @param semester Semester for the enrollment.
     * @return enrollmentError.
     */
	int addEnrollment(unsigned int matrikelNumber,unsigned int courseId,
			std::string semester);

    /**
     * @brief Add a course to the Database.
     *
     * @param course Course to be added in the database.
     */
	void addCourse(std::unique_ptr<Course>& course);

    /**
     * @brief Add a student to the Database.
     *
     * @param student Student to be added in the database.
     */
	void addStudent(Student student);

    /**
     * @brief Search for students based on a name substring and print a list of
     * all the students to an output stream.
     *
     * @param nameSubString Substring to search for in student first or last name.
     * @param out Output stream to print the results.
     * @return True if students are found, false if not found.
     */
	bool searchStudents(std::string nameSubString,std::ostream &out) const;

    /**
     * @brief Update a student's ID, first name, last name, Date of Birth and
     * address.
     *
     * @param matrikelNumber Matrikel number of the student to update.
     * @param option Identifier of Update type.
     * @param dataToUpdate Encoded string carrying data to update.
     */
	void updateStudentID(unsigned int matrikelNumber ,unsigned short option,
		std::string dataToUpdate);

    /**
     * @brief Update a student's Enrollment status by removing the enrollment or
     * grading an enrollment
     *
     * @param matrikelNumber Matrikel number of the student to update.
     * @param courseKey the course identifier
     * @param grade Grade achieved by the student
     * @param isRemove True,if the enrollment has to be removed, false otherwise
     */
	void updateStudentEnrollment(unsigned int matrikelNumber,unsigned int courseKey,
			float grade, bool isRemove);

    /**
     * @brief Writes the database contents to an output stream.
     *
     * @param out Output stream to write to.
     */
	void write(std::ostream &out);

    /**
     * @brief Read the database contents from an input stream.
     *
     * @param in Input stream to read from.
     */
	void read(std::istream& in);

    /**
     * @brief Read the database contents from a server stream converted in string.
     *
     * @param strigStream string extraction of Server stream to read from.
     */
	void readFromServer(std::string& stringStream);

    /**
     * @brief To check the if the string has valid charcacters or not
     *
     * @param strig of the Data
     */
	bool isValidName(std::string& str);

};

#endif /* STUDENTDB_H_ */
