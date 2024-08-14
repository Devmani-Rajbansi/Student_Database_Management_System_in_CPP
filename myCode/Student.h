/*
 * Student.h
 *
 * Author: devma
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <vector>

#include <Poco/Data/Date.h>
#include "Enrollment.h"
#include "Address.h"



/**
 * @class Student
 * @brief Represents a student with all properties in the database.
 */
class Student
{
private:

	/**@brief Next matriculation number generator*/
	static unsigned int nextMatrikelNumber;

	/**@brief Object of the Address class*/
	Address* address;

	/**@brief Matriculation Number of the student*/
	unsigned int matrikelNumber;

	/**@brief First Name of the student*/
	std::string firstName;

	/**@brief Last name of the student*/
	std::string lastName;

	/**@brief DOB of the student*/
	Poco::Data::Date dateOfBirth;

	/**@brief Storage of all the enrollments*/
	std::vector<Enrollment> enrollments;

public:

	/**
	 * @fn
	 * @brief Constructor for Student class
	 *
     * @param firstName The first name of the student.
     * @param lastName The last name of the student.
     * @param dateOfBirth The date of birth of the student.
     * @param street The street of the student's address.
     * @param postalCode The postal code of the student's address.
     * @param cityName The city name of the student's address.
     * @param additionalInfo Additional information about the student's address (optional).
	 *
	 */
	Student(std::string firstName,std::string lastName,Poco::Data::Date dateOfBirth,
	string street,unsigned short postalCode,string cityName,string additionalInfo="");

    /**
     * @brief Default Constructor for Student class.
     */
	Student();

    /**
     * @brief Constructor for Student class using input stream.
     * @param in The input stream from which to read student data.
     */
	Student(std::istream &in);

    /**
     * @brief Destructor for Student class.
     */
    ~Student();

	/**
	 * @brief Gets the enrollments of a student
	 * @return A vector of Enrollment objects representing the student's enrollments.
	 */
	std::vector<Enrollment> getEnrollments() const;

    /**
     * @brief Gets the first name of the student.
     * @return A constant reference to the first name.
     */
    const std::string& getFirstName() const;

    /**
     * @brief Gets the last name of the student.
     * @return A constant reference to the last name.
     */
    const std::string& getLastName() const;

    /**
    * @brief Gets the matriculation number of the student.
    * @return The matriculation number as an unsigned integer.
    */
	unsigned int getMatrikelNumber() const;

    /**
     * @brief Gets the pointer to the Address of the student
     * @return The pointer to the Address property of the Student
     */
	const Address* getAddress() const;

    /**
    * @brief Gets the date of birth of the student.
    * @return The Date of birth as Poco Date object.
    */
	const Poco::Data::Date& getDateOfBirth() const;

    /**
     * @brief Adds a new enrollment in the vector of enrollments
     * @param Object of Enrollment class
     */
	void addEnrollment(Enrollment enrollment);

    /**
     * @brief Function for output stream of student data.
     * @param The output stream to which student data is written.
     */
	void write(std::ostream &out) const;

    /**
     * @brief Function for input stream of student data.
     * @param The input stream from which student data is read.
     */
	void read(std::istream &in);

    /**
     * @brief Updates the firstName, lastName and the dateOfBirth of the student.
     * @param firstName The first name of the student.
     * @param lastName The last name of the student.
     * @param dateOfBirth The date of birth of the student.
     */
	void updateStudentID(std::string firstName, std::string lastName,
			int day, int month, int year);

    /**
     * @brief updates and creates new Address object of the student.
     *
     * @param street The street of the student's address.
     * @param postalCode The postal code of the student's address.
     * @param cityName The city name of the student's address.
     * @param additionalInfo Additional information about the student's address
     */
	void updateStudentAddress(std::string street,unsigned short postalCode,std::string cityName,
			std::string additionalInfo);

    /**
     * @brief Updates the student's Enrollment.
     * @param courseKey The course identifier
     * @param Grade scored by the student
     * @param bool isRemove : to determine to remove or keep the enrollment
     */
	void updateStudentEnrollment(unsigned int courseKey,float grade,bool isRemove);

};

#endif /* STUDENT_H_ */
