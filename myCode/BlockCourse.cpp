/*
 * BlockCourse.cpp
 *
 * Author: devma
 */

#include<iostream>
#include<sstream>
#include<string.h>

#include "BlockCourse.h"
#include "boost/algorithm/string.hpp"


BlockCourse::BlockCourse(unsigned int courseKey, std::string title,
	std::string majorInString, float creditPoints,Poco::Data::Date startDate,
	Poco::Data::Date endDate,Poco::Data::Time startTime, Poco::Data::Time endTime)
	:Course(courseKey,title,majorInString,creditPoints),startDate(startDate),
	 endDate(endDate),startTime(startTime),endTime(endTime)
{

}

void BlockCourse::write(std::ostream &out) const
{
	/*Populating the outstream*/
	out <<"B;";
	Course::write(out);
	out<<std::to_string(startDate.day())+"."<<std::to_string(startDate.month())
			+"."<<std::to_string(startDate.year())+";";
	out<<std::to_string(endDate.day())+"."<<std::to_string(endDate.month())
			+"."<<std::to_string(endDate.year())+";";
	out<<std::to_string(startTime.hour())+":"+std::to_string(startTime.minute())+";";
	out<<std::to_string(endTime.hour())+":"+std::to_string(endTime.minute());
	out<<"\n";
}

void BlockCourse::read(std::istream &in)
{
	std::string inputString;
	std::getline(in,inputString);
	std::istringstream inputStream(inputString);

	/**Calling the base class Read function by sending the string stream*/
	Course::read(inputStream);

	/**Extracting the Block Course Info*/
	std::vector<std::string> blockCourseData;
	boost::split(blockCourseData,inputString,boost::is_any_of(";"));

	/**Read and parse start date*/
	std::vector<std::string> startDateVec;
	boost::split(startDateVec,blockCourseData[4],boost::is_any_of("."));
	int startDateDay=std::stoi(startDateVec[0]); 	/*Splitting Date*/
	int startDateMonth=std::stoi(startDateVec[1]); 	/*Splitting Month*/
	int startDateYear=std::stoi(startDateVec[2]); 	/*Splitting Year*/
	startDate = Poco::Data::Date(startDateYear,startDateMonth,startDateDay);

	/**Read and parse End date*/
	std::vector<std::string> endDateVec;
	boost::split(endDateVec,blockCourseData[5],boost::is_any_of("."));
	int endDateDay=std::stoi(endDateVec[0]); 		/*Splitting Date*/
	int endDateMonth=std::stoi(endDateVec[1]); 		/*Splitting Month*/
	int endDateYear=std::stoi(endDateVec[2]); 		/*Splitting Year*/
	startDate = Poco::Data::Date(endDateYear,endDateMonth,endDateDay);

	/**Read and parse start time*/
	std::vector<std::string> startTimeVec;
	boost::split(startTimeVec,blockCourseData[6],boost::is_any_of(":"));
	int startHours=std::stoi(startTimeVec[0]);		/*Splitting Hour*/
	int startMinutes=std::stoi(startTimeVec[1]);	/*Splitting Minute*/
	startTime = Poco::Data::Time(startHours,startMinutes,0);

	/**Read and parse end time*/
	std::vector<std::string> endTimeVec;
	boost::split(endTimeVec,blockCourseData[7],boost::is_any_of(":"));
	int endHours=std::stoi(endTimeVec[0]);
	int endMinutes=std::stoi(endTimeVec[1]);
	endTime = Poco::Data::Time(endHours,endMinutes,0);
}

BlockCourse::BlockCourse(std::istream &in)
{
	/**Calling the read function of the course class*/
	read(in);
}
