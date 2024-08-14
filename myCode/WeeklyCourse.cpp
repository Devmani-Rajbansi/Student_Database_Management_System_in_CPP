/*
 * WeeklyCourse.cpp
 *
 * Author: devma
 */

#include<iostream>
#include<sstream>
#include<string>

#include "WeeklyCourse.h"
#include "boost/algorithm/string.hpp"


WeeklyCourse::WeeklyCourse(unsigned int courseKey, std::string title,
	std::string majorInString, float creditPoints,Poco::DateTime::DaysOfWeek dayOfWeek,
	Poco::Data::Time startTime,Poco::Data::Time endTime):Course(courseKey,title,
	majorInString,creditPoints),dayOfWeek(dayOfWeek),startTime(startTime),endTime(endTime)
{

}

void WeeklyCourse::write(std::ostream &out) const
{
	/*Populating the outstream*/
	out <<"W;";
	Course::write(out);
	out<<std::to_string(dayOfWeek)+";";
	out<<std::to_string(startTime.hour())+":"+std::to_string(startTime.minute())+";";
	out<<std::to_string(endTime.hour())+":"+std::to_string(endTime.minute());
	out<<"\n";
}

void WeeklyCourse::read(std::istream &in)
{
	std::string inputString;
	std::getline(in,inputString);
	std::istringstream inputStream(inputString);

	/**Calling the base class Read function by sending the string stream*/
	Course::read(inputStream);

	/**Extracting the Weekly Course Info*/
	std::vector<std::string> weeklyCourseData;
	boost::split(weeklyCourseData,inputString,boost::is_any_of(";"));

	/**Extracting the Day of the week info*/
	switch (std::stoi(weeklyCourseData[4])) {
		case 1: dayOfWeek = Poco::DateTime::DaysOfWeek::MONDAY; break;
		case 2: dayOfWeek = Poco::DateTime::DaysOfWeek::TUESDAY; break;
		case 3: dayOfWeek = Poco::DateTime::DaysOfWeek::WEDNESDAY; break;
		case 4: dayOfWeek = Poco::DateTime::DaysOfWeek::THURSDAY; break;
		case 5: dayOfWeek = Poco::DateTime::DaysOfWeek::FRIDAY; break;
		case 6: dayOfWeek = Poco::DateTime::DaysOfWeek::SATURDAY; break;
		case 7: dayOfWeek = Poco::DateTime::DaysOfWeek::SUNDAY; break;
		default: dayOfWeek = Poco::DateTime::DaysOfWeek::SUNDAY; break;
	}

	/**Read and parse start time*/
	std::vector<std::string> startTimeVec;
	boost::split(startTimeVec,weeklyCourseData[5],boost::is_any_of(":"));
	int startHours=std::stoi(startTimeVec[0]);		/*Splitting Hour*/
	int startMinutes=std::stoi(startTimeVec[1]);	/*Splitting Minute*/

	startTime = Poco::Data::Time(startHours,startMinutes,0);

	/**Read and parse end time*/
	std::vector<std::string> endTimeVec;
	boost::split(endTimeVec,weeklyCourseData[6],boost::is_any_of(":"));
	int endHours=std::stoi(endTimeVec[0]);			/*Splitting Hour*/
	int endMinutes=std::stoi(endTimeVec[1]);		/*Splitting Minute*/

	endTime = Poco::Data::Time(endHours,endMinutes,0);
}


WeeklyCourse::WeeklyCourse(std::istream &in)
{
	/**Calling the read function of the course class*/
	read(in);
}

