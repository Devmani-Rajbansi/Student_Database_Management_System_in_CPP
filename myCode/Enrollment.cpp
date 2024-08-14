/*
 * BlockCourse.cpp
 *
 * Author: devma
 */

#include <iostream>
#include<fstream>
#include<iomanip>

#include "Enrollment.h"
#include "Course.h"

Enrollment::Enrollment(const Course* course,std::string semester):course(course),
semester(semester){
	grade=0.0;
}

Enrollment::~Enrollment()
{

}

const Course* Enrollment::getCourse() const
{
	return course;
}

float Enrollment::getGrade() const
{
	return grade;
}

const std::string& Enrollment::getSemester() const
{
	return semester;
}

void Enrollment::setGrade(float grade)
{
	this->grade = grade;
}

void Enrollment::write(std::ostream &out) const
{
	std::ostringstream ossGrade;
	ossGrade <<std::fixed<< std::setprecision(1) <<grade;
	unsigned int tempCourseKey=course->getCourseKey();
	out<<std::to_string(tempCourseKey)+";";
	out<<semester+";";
	out<<ossGrade.str()<<"\n";
}
