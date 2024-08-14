/*
 * Course.cpp
 *
 * Author: devma
 */

#include<string>
#include<iostream>
#include "boost/algorithm/string.hpp"

#include <Poco/Data/Time.h>
#include <Poco/Data/Date.h>

#include "Course.h"
#include "WeeklyCourse.h"

using std::cout;
using std::endl;

std::map<unsigned char,std::string> Course::majorById={
		{'A',"Automation"},
		{'C',"Communication"},
		{'E',"Embedded"},
		{'P',"Power"}
};

Course::~Course(){

}

unsigned int Course::getCourseKey() const
{
	return courseKey;
}

float Course::getCreditPoints() const
{
	return creditPoints;
}

std::string Course:: getMajor() const
{
	std::string majorInString=this->majorById[this->major];

	return majorInString;
}

Course::Course( unsigned int courseKey,std::string title,
	std::string majorInString, float creditPoints):courseKey(courseKey),
			title(title),creditPoints(creditPoints)

{
	std::string tempString=majorInString;
	for(const auto& pair:majorById){
		if((pair.second)==tempString){
			this->major=pair.first;
		}
	}
	auto itr=majorById.find(this->major);
	if(itr==majorById.end()){
		this->major='A';	/*If invalid input the default major is Automation*/
	}
}

const std::string& Course::getTitle() const
{
	return title;
}

void Course::write(std::ostream &out) const
{
	/*Populating the outstream*/
	out<<courseKey<<";"<<title<<";"<<getMajor()<<";"<<creditPoints<<";";
}

void Course::read(std::istream &in){
	std::string inputString;
	std::getline(in,inputString,'\n');
	std::vector<std::string> courseData;

	boost::split(courseData,inputString,boost::is_any_of(";"));
	/**Course Key extraction*/
	courseKey=std::stoi(courseData[0]);

	/**Course Title extraction*/
	title=courseData[1];

	/**Course Major extraction*/
	std::string tempString=courseData[2];
	for(const auto& pair:majorById){
		if((pair.second)==tempString){
			this->major=pair.first;
		}
	}

	/**Course CreditPoints extraction*/
	creditPoints=std::stof(courseData[3]);

	/**Reading Extracted data in-istream*/
	in>>courseKey>>title>>major>>creditPoints;
}

Course::Course(){

}

