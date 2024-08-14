/*
 * StudentDb.cpp
 *
 * Author: devma
 */
#include<iostream>
#include<map>
#include<memory>
#include<sstream>
#include<Poco/JSON/Parser.h>
#include "Poco/Exception.h"
#include "boost/algorithm/string.hpp"
#include <Poco/Data/Date.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "StudentDb.h"
#include "WeeklyCourse.h"
#include "BlockCourse.h"

using std::endl;
using std::string;


StudentDb::StudentDb(){

}

StudentDb::~StudentDb(){

}

const std::map<int, std::unique_ptr<const Course> >& StudentDb::getCourses() const
{
	return std::move(courses);
}

const std::map<int, Student>& StudentDb::getStudents() const
{
	return students;
}


int StudentDb::addEnrollment(unsigned int matrikelNumber,
		unsigned int courseId,std::string semester)
{
	auto it = students.find(matrikelNumber);
	if(it!=students.end()){
		Student& student = students.at(matrikelNumber);

		/**Creating temp vector of all enrollments done by the student */
		std::vector<Enrollment> studentEnroll=student.getEnrollments();

		/**Iterator for finding the quired Course*/
		for(auto& itrCourses:courses){
			if(itrCourses.first==courseId){
				for(auto it : studentEnroll){
					unsigned int key = it.getCourse()->getCourseKey();
					std::string sem = it.getSemester();
					if(key==courseId && sem==semester){
						return 1; /**Enrollment exsist in vector*/
					}
				}
				const Course* course=itrCourses.second.get();
				Enrollment enrollment(course,semester);
				student.addEnrollment(enrollment);
				return 0; /**Successfully added in vector*/
			}
		}
		return 2;		/**Course dosen't exsist*/
	}
	return 3;			/**Student dosen't exsist*/
}

void StudentDb::addCourse(std::unique_ptr<Course> &course)
{
	courses[course->getCourseKey()]=std::move(course);
}

void StudentDb::addStudent(Student student)
{
	students[student.getMatrikelNumber()]=student;
}


bool StudentDb::searchStudents(std::string nameSubString,
		std::ostream &out) const
{
	bool isMatch=false;
	for(const auto& itr : students){
		if(((itr.second.getFirstName().find(nameSubString)) != std::string::npos)
			||((itr.second.getLastName().find(nameSubString)) != std::string::npos)){
			out<<std::to_string(itr.second.getMatrikelNumber())+";";
			out<<itr.second.getLastName()+";";
			out<<itr.second.getFirstName();out<<endl;
			isMatch=true;
		}
	}
	return isMatch;
}

void StudentDb::updateStudentID(unsigned int matrikelNumber,unsigned short option,
		std::string dataToUpdate)
{
	/*Option identifies the task to be done*/
	std::string noChange="";
	Student* student=&(students.at(matrikelNumber));
	if(option==11){ 		/*Updating first name*/
		student->updateStudentID(dataToUpdate,noChange,0,0,0);
	}
	if(option==12){			/*Updating last name*/
		student->updateStudentID(noChange,dataToUpdate,0,0,0);
	}
	if(option==13){			/*Updating dateOfBirth*/
		std::vector<std::string> dateVec;

		/*Decoding the Date of birth*/
		boost::split(dateVec,dataToUpdate,boost::is_any_of("."));
		int day=std::stoi(dateVec[0]);
		int month=std::stoi(dateVec[1]);
		int year=std::stoi(dateVec[2]);
		student->updateStudentID("","",day,month,year);
	}
	/*Updating various component of the Address*/
	if((option == 21) || (option == 22)|| (option == 23) || (option == 24)){
		std::string street=student->getAddress()->getStreet();
		unsigned short postalCode=student->getAddress()->getPostalCode();
		std::string cityName=student->getAddress()->getCityName();
		std::string addiInfo=student->getAddress()->getAdditionalInfo();
		if(option==21){
		student->updateStudentAddress(dataToUpdate,postalCode,cityName,addiInfo);
		}
		if(option==22){
		unsigned int tempPostal=stoi(dataToUpdate);
		student->updateStudentAddress(street,tempPostal,cityName,addiInfo);
		}
		if(option==23){
		student->updateStudentAddress(street,postalCode,dataToUpdate,addiInfo);
		}
		if(option==24){
		student->updateStudentAddress(street,postalCode,cityName,dataToUpdate);
		}
	}
}

void StudentDb::updateStudentEnrollment(unsigned int matrikelNumber,
		unsigned int courseKey, float grade, bool isRemove)
{
	Student* student=&(students.at(matrikelNumber));
	student->updateStudentEnrollment(courseKey,grade,isRemove);
}

void StudentDb::write(std::ostream &out)
{
	/**Printing the course details first*/
	out<<courses.size()<<endl;
	for(const auto& itrCourses : courses){
		itrCourses.second->write(out);
	}

	/**Printing the students details*/
	out<<students.size()<<endl;
	for(const auto& itStudents : students){
		itStudents.second.write(out);
	}

	/**Printing enrollments of the students*/
	for(const auto& itStudent : students){
		int enrollNum=itStudent.second.getEnrollments().size();
		if(enrollNum>0){
			out<<enrollNum<<"\n";
			for(const auto& itEnroll : itStudent.second.getEnrollments()){
				out<<itStudent.second.getMatrikelNumber()<<";";
				itEnroll.write(out);
			}
		}
	}
}


/**https://www.geeksforgeeks.org/boostsplit-c-library*/
/**split(Result, Input, Predicate Pred (boost::is_any_of)*/
void StudentDb::read(std::istream &in)
{
	this->courses.clear();
	this->students.clear();
	int countOfCourses=0;
	int countOfStudents=0;

	/**Parsing the data*/

	/**Counting number of courses*/
	std::string input;
	std::getline(in,input);
	countOfCourses=std::stoi(input);

	/**For assiging the course*/
	for(int count=0;count<countOfCourses;count++){

		/**Splitting base on the course type*/
		std::string courseType;
		std::getline(in,courseType,';');

		std::string inputString;
		std::getline(in,inputString);
		std::istringstream inputStream(inputString);

		if(courseType=="W" || courseType=="w"){
			std::unique_ptr<Course> weeklyCourse(new WeeklyCourse(inputStream));
			addCourse(weeklyCourse);
		}
		else if(courseType=="B" || courseType=="b"){
			std::unique_ptr<Course> blockCourse(new BlockCourse(inputStream));
			addCourse(blockCourse);
		}
		else{
			std::ostringstream message;
			message<<"File is corrupt"<<endl;
		}
	}

	/**Counting number of students*/
	std::getline(in,input);
	countOfStudents=std::stoi(input);

	for(int count=0;count<countOfStudents;count++){
		std::string inputString;
		std::getline(in,inputString);
		std::istringstream inputStream(inputString);
		Student student(inputStream);
		addStudent(student);
	}

	/**Parsing the enrolment data of all the students*/
	while(std::getline(in,input)){
	int countOfEnrollments=0;
	countOfEnrollments=std::stoi(input);

		/**Counting the enrolment of a single student*/
		for(int countEnroll=0;countEnroll<countOfEnrollments;countEnroll++)
		{
			std::string inputString;
			std::getline(in,inputString);
			std::istringstream inputStream(inputString);

			std::vector <std::string> enrollData;
			boost::split(enrollData,inputString,boost::is_any_of(";"));
			int matrikelNum = std::stoi(enrollData[0]);
			int courseKey = std::stoi(enrollData[1]);
			std::string semester= enrollData[2];
			float grade=std::stof(enrollData[3]);

			addEnrollment(matrikelNum,courseKey,semester);
			bool isRemove=false;
			auto itStudent = students.find(matrikelNum);
			auto itCourse = courses.find(courseKey);
			if(itStudent!=students.end() && itCourse!=courses.end()){
				addEnrollment(matrikelNum,courseKey,semester);
				updateStudentEnrollment(matrikelNum,courseKey,grade,isRemove);
			}
		}
	}
}

/**https://docs.pocoproject.org/current/Poco.JSON.Parser.html*/
/**https://www.cochoy.fr/boost-property-tree : Used here for light weight JSON*/
void StudentDb::readFromServer(std::string& jsonDataString)
{
	bool isValidData=true; /*Checks the validity of the data*/
	namespace pt = boost::property_tree;
	try{
	/*Create a root of property_tree*/
	pt::ptree root;

	/*Load the json stream in this ptree*/
	std::istringstream jsonDataStream(jsonDataString);
	pt::read_json(jsonDataStream, root);

	/*Parsing the JSON data using the property_tree for light weight JSON*/
	unsigned int dOBDay = root.get<int>("dateOfBirth.date");
	unsigned int dOBMonth = root.get<int>("dateOfBirth.month")+1;
	unsigned int dOBYear = root.get<int>("dateOfBirth.year")+1900;

	string tempfirstName = root.get<string>("name.firstName");
	string templastName = root.get<string>("name.lastName");

	string firstName;
	if(isValidName(tempfirstName)){ /*Checking the validity of Name*/
		firstName=tempfirstName;
	}else{isValidData=false;}

	string lastName;
	if(isValidName(templastName)){  /*Checking the validity of last Name*/
		lastName=templastName;
	}else{isValidData=false;}

	string tempStreet = root.get<string>("location.street");
	int postalCode = root.get<int>("location.postCode");
	string tempCity = root.get<string>("location.city");
	string tempInfo = root.get<string>("location.state");

	string street;
	string city ;
	string additionalInfo;

	if(isValidName(tempStreet)){ /*Checking the validity of street*/
		street=tempStreet;
	}else{isValidData=false;}

	if(isValidName(tempCity)){	/*Checking the validity of cityName*/
		city=tempCity;
	}else{isValidData=false;}

	if(isValidName(tempInfo)){	/*Checking the validity of AdditionalInfo*/
		additionalInfo=tempInfo;
	}else{isValidData=false;}

	Poco::Data::Date dateOfBirth;
	dateOfBirth.assign(dOBYear,dOBMonth,dOBDay);

	if(isValidData){
		/*Adding the student in the Students map if the data is valid*/
		addStudent(Student(firstName,lastName,dateOfBirth,street,postalCode,city,
				additionalInfo));
		}
	}

	catch(const pt::json_parser::json_parser_error& e){
		std::cerr<<"The JSON parser error is "<<e.what()<<std::endl;
	}
	catch(const Poco::Exception& e){
		std::cerr<<"The Poco exception is "<<e.displayText()<<std::endl;
	}
	catch(const std::exception& e){
		std::cerr<<"An error occured "<<e.what()<<std::endl;
	}

}

bool StudentDb::isValidName(std::string &str)
{
	for(auto c : str){
		/*Some name or addresses have "-" or "."*/
		if(!std::isalnum(c) && (c!=' ') && (c!='.') && (c!='-')){
			return false;
		}
	}
	return true;
}
