/*
 * Student.cpp
 *
 * Author: devma
 */

#include <iostream>
#include<string>
#include<sstream>
#include "boost/algorithm/string.hpp"
#include "Poco/Exception.h"

#include "Student.h"
#include "Enrollment.h"

unsigned int Student::nextMatrikelNumber=100000;

Student::Student(std::string firstName, std::string lastName,Poco::Data::Date dateOfBirth,
		string street,unsigned short postalCode,string cityName,string additionalInfo):firstName(firstName),lastName(lastName),
				dateOfBirth(dateOfBirth)
{
	/*Creating a new Address object by allocting it memory*/
	this->address = new Address(street,postalCode,cityName,additionalInfo);

	/*Updating the matriculation number in sequence for new student*/
	this->matrikelNumber=nextMatrikelNumber++;
}

std::vector<Enrollment> Student::getEnrollments() const
{
	return enrollments;
}

const std::string& Student::getFirstName() const
{
	return firstName;
}

const std::string& Student::getLastName() const
{
	return lastName;
}

unsigned int Student::getMatrikelNumber() const
{
	return matrikelNumber;
}

void Student::addEnrollment(Enrollment enrollment)
{
	/*Adding enrollment in the vector of enrollments*/
	enrollments.push_back(enrollment);
}

const Poco::Data::Date& Student::getDateOfBirth() const
{
	return dateOfBirth;
}

void Student::write(std::ostream &out) const
{
	out<<std::to_string(matrikelNumber)+";"<<lastName+";"<<firstName+";";
	out<<std::to_string(dateOfBirth.day())+"."<<std::to_string(dateOfBirth.month())
			+"."<<std::to_string(dateOfBirth.year())+";";
	getAddress()->write(out);
	out<<std::endl;
}

Student::Student(){

}

void Student::updateStudentID(std::string firstName, std::string lastName,
		int day, int month, int year)
{
	try{
		if(firstName != ""){
			this->firstName=firstName;
		}
		if(lastName != ""){
			this->lastName=lastName;
		}
		if(day>0 && month>0 && year>0){
			this->dateOfBirth = Poco::Data::Date(year,month,day);
		}
	}catch(const Poco::Exception& e){
		std::cerr<<"The Poco exception is "<<e.displayText()<<std::endl;
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}

const Address* Student::getAddress() const
{
	return address;
}

void Student::updateStudentAddress(std::string street, unsigned short postalCode,
		std::string cityName, std::string additionalInfo)
{
	delete this->address;
	/*Deleting the old address and creating a new object*/
	this->address = new Address(street,postalCode,cityName,additionalInfo);
}

Student::Student(std::istream &in){
	read(in);
}

Student::~Student(){

}

void Student::updateStudentEnrollment(unsigned int courseKey,float grade,bool isRemove)
{
	std::vector<Enrollment> enrollment=this->getEnrollments();
	std::vector<Enrollment>::iterator itr;
	if(isRemove==0){
		for(auto& it:enrollment){
			const Course* course=it.getCourse();
			if(course->getCourseKey()==courseKey){
				it.setGrade(grade);			/*Set the grade for this course*/
			}
		}
	}
	else if(isRemove==1 && grade==0){		/*Course can't be removed if graded*/
		for(itr=enrollment.begin();itr!=enrollment.end();itr++){
			const Course* course=itr->getCourse();
			if(course->getCourseKey()==courseKey){
				enrollment.erase(itr);		/*Erasing the enrollment*/
			}
		}
	}
	this->enrollments=enrollment;
}

void Student::read(std::istream &in)
{
	try{
	std::string inputString;
	std::getline(in,inputString);
	std::vector<std::string> studentData;

	boost::split(studentData,inputString,boost::is_any_of(";"));
	this->matrikelNumber= std::stoi(studentData[0]);
	this->lastName=studentData[1];
	this->firstName=studentData[2];

	/*Updating the next matrikel Number and checking for the highest matrikel number*/
	if(nextMatrikelNumber<=this->matrikelNumber){
		Student::nextMatrikelNumber=matrikelNumber+1;
	}

	/**Read and parse date of birth*/
	std::vector<std::string> dateOfBirthVec;
	boost::split(dateOfBirthVec,studentData[3],boost::is_any_of("."));
	int birthDateDay=std::stoi(dateOfBirthVec[0]); 		/*Splitting Date*/
	int birthDateMonth=std::stoi(dateOfBirthVec[1]); 	/*Splitting Month*/
	int birthDateYear=std::stoi(dateOfBirthVec[2]); 	/*Splitting Year*/
	this->dateOfBirth = Poco::Data::Date(birthDateYear,birthDateMonth,birthDateDay);

	std::string street=studentData[4];					/*Street Name Extraction*/
	unsigned short postalCode=std::stoul(studentData[5]); /*Postal Code Extraction*/
	std::string cityName=studentData[6];				/*City Name Extraction*/
	std::string additionalInfo=studentData[7];			/*Additional Info Extraction*/

	/*Creating a new object of the Address*/
	this->address = new Address(street,postalCode,cityName,additionalInfo);
	}catch(const Poco::Exception& e){
		std::cerr<<"The Poco exception is "<<e.displayText()<<std::endl;
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}

