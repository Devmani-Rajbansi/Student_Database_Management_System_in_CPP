/*
* BlockCourse.cpp
*
* Author: devma
*/

#include<iostream>
#include<memory>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<limits>
#include<boost/asio.hpp>
#include "Poco/Exception.h"

#include "SimpleUI.h"
#include "Enrollment.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

/**
 * @brief Template function to safely get input of a specific type from the user.
 *
 * This function prompts the user with a message and keeps asking for a valid
 * input and avoiding infinite loop
 *
 * @tparam T The type of input to be received (e.g., int, float,string etc).
 * @param message The message to display when prompting the user.
 * @return The valid input of type T.
 */
template <typename T>
T getInput(const std::string& message){
	T input;
	while(true){
		cout<<message;
		if(cin>>input){
			cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
			break;
		}
		else{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
			cout<<"!! Invalid input ";
		}
	}
	return input;
}

SimpleUI::SimpleUI(StudentDb* db):db(db){

}

void SimpleUI::run()
{
cout<<"!!! Welcome to Student Database !!!"<<endl;
unsigned int userInput;
do{
	cout<<"\n!! User Commands !!"<<endl
	<<"0. To close the UI and end session: " << std::endl
	<<"1. Add a new Course: " << std::endl
	<<"2. List of Courses: "<< std::endl
	<<"3. Add a new Student: "<< std::endl
	<<"4. Add an enrollment: " << std::endl
	<<"5. Print student details: "  << std::endl
	<<"6. Search student: " << std::endl
	<<"7. Update student details: " << std::endl
	<<"8. Write Database content to a file" << std::endl
	<<"9. Read from a file and update the database " << std::endl
	<<"10. Read student data from a server and update the database " << std::endl;
	userInput=getInput<unsigned int>("\n*Choose an option from above (0-10)* ");
	cout<<std::endl;

	switch (userInput){
	case 1:{
		try{
			unsigned int courseKey,dayOfWeek;
			string title,major;
			float creditPoints;
			int startTimeHour=0,endTimeHour=0;
			int startTimeMinute=0,endTimeMinute=0;
			int startDateDay=0,startDateMonth=0,startDateYear=0;
			int endDateDay=0,endDateMonth=0,endDateYear=0;
			Poco::DateTime::DaysOfWeek daysOfWeek;
			bool courseType;

			courseKey=getInput<unsigned int>("Enter a Course key ");
			cout<<"Enter a course Title (eg. State Space) "<<std::flush;
			getline(cin,title);
			cout<<"Enter the Major (Automation/Power/Embedded/Communication) "<<endl;
			getline(cin,major);
			creditPoints=getInput<float>("Enter the Credit Points (e.g 5.0) ");
			courseType=getInput<bool>("Enter course type (0. Weekly Course : 1. Block Course) ");

			/*Weekly Course selection*/
			if(courseType==0){
				dayOfWeek=getInput<unsigned int>("Enter the day of the week "
						"( 1: Monday...5:Friday) ");
				switch (dayOfWeek) {
					case 1: daysOfWeek = Poco::DateTime::DaysOfWeek::MONDAY; break;
					case 2: daysOfWeek = Poco::DateTime::DaysOfWeek::TUESDAY; break;
					case 3: daysOfWeek = Poco::DateTime::DaysOfWeek::WEDNESDAY; break;
					case 4: daysOfWeek = Poco::DateTime::DaysOfWeek::THURSDAY; break;
					case 5: daysOfWeek = Poco::DateTime::DaysOfWeek::FRIDAY; break;
					case 6: daysOfWeek = Poco::DateTime::DaysOfWeek::SATURDAY; break;
					case 7: daysOfWeek = Poco::DateTime::DaysOfWeek::SUNDAY; break;
					default: daysOfWeek = Poco::DateTime::DaysOfWeek::SUNDAY; break;
				}
			}

			/*Block Course selection*/
			else if(courseType==1){
				cout<<"Enter the start date (in Day Month Year format) "<<std::flush;
				cin>> startDateDay >> startDateMonth >> startDateYear;
				cout<<"Enter the end date (in Day Month Year format) "<<std::flush;
				cin>> endDateDay >> endDateMonth >> endDateYear;
			}

			std::cout << "Enter the start time (eg. 10 30) "<<std::flush;
			std::cin >> startTimeHour >> startTimeMinute;
			std::cout << "Enter the end Time (eg. 12 00) "<<std::flush;
			std::cin >> endTimeHour >> endTimeMinute;
			if(courseType==0){
				std::unique_ptr<Course> course(new WeeklyCourse(courseKey, title,
				major, creditPoints, daysOfWeek,Poco::Data::Time(startTimeHour,startTimeMinute,0),
				Poco::Data::Time(endTimeHour,endTimeMinute,0)));

				/**Adding the course in the courses map*/
				db->addCourse(course);
			}
			else if(courseType==1){
				std::unique_ptr<Course> course(new BlockCourse(courseKey, title, major, creditPoints,
						Poco::Data::Date(startDateYear, startDateMonth, startDateDay),
						Poco::Data::Date(endDateYear, endDateMonth, endDateDay),
						Poco::Data::Time(startTimeHour,startTimeMinute,0),
						Poco::Data::Time(endTimeHour,endTimeMinute,0))) ;

				/**Adding the course in the courses map*/
				db->addCourse(course);
			}
		}catch(const Poco::Exception& e){
			std::cerr<<"The Poco exception is "<<e.displayText()<<std::endl;
		}
		catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
		}
		break;
	}

	/*Command 2 : List the Courses*/
	case 2:{
		/*Printing the list of course using the cout ostream object*/
		cout<<"The list of Courses"<<endl;
		for(const auto& itr : db->getCourses()){
			itr.second->write(std::cout);
		}
		break;
	}

	/*Command 3 : Add a new student*/
	case 3:{
		try{
		string firstName,lastName;
		int dOBYear,dOBMonth,dOBDay;
		unsigned short postalCode;
		string street,cityName,additionalInfo;
		cout << "Enter the student's first name: " << std::flush;
		getline(cin,firstName);
		cout << "Enter the student's last name: " << std::flush;
		getline(cin,lastName);
		cout << "Enter the student's Date of Birth ( eg 21 07 1995 ): "<< std::flush;
		cin >> dOBDay >> dOBMonth >>dOBYear ;cin.ignore();

		cout << "Enter the student's address (street) " << std::flush;
		getline(cin,street);
		postalCode=getInput<unsigned short>("Enter the student's address (postal code)  ");
		cout << "Enter the student's address (city Name) " << std::flush;
		getline(cin,cityName);
		cout << "Enter the student's address (Additional Info) " << std::flush;
		getline(cin,additionalInfo);

		/*Creating a student object and adding in the students map*/
		db->addStudent(Student(firstName,lastName,Poco::Data::Date(dOBYear,
			dOBMonth,dOBDay),street,postalCode,cityName,additionalInfo));
		}catch(const Poco::Exception& e){
			std::cerr<<"The Poco exception is "<<e.displayText()<<std::endl;
		}
		catch (std::exception& e) {
			std::cerr << "Exception: " << e.what() << std::endl;
			}
		break;
	}

	/*Command 4 : Add an Enrollment*/
	case 4:{
	unsigned int matrikelNum,courseId;
	string semester;
	matrikelNum=getInput<unsigned int>("Enter the Student's Matriculation Number ");
	courseId=getInput<unsigned int>("Enter the Course Key ");
	semester=getInput<std::string>("Enter the semester ");

		/*Calling addEnrollment function and generating warning*/
		int errorCode=db->addEnrollment(matrikelNum,courseId,semester);
		switch(errorCode){
		case 0: cout<<"!!! Student enrolled successfully"<<endl;break;
		case 1: cout<<"!!! The enrollment already exsist"<<endl;break;
		case 2: cout<<"!!! The entered course dosent exsist"<<endl;break;
		case 3: cout<<"!!! The entered student dosent exsist"<<endl;break;
		default:cout<<"!!! Invalid"<<endl;break;
		}
	break;
	}

	/*Command 5 : Print Students*/
	case 5:{
	unsigned int matrikelNum;
	matrikelNum=getInput<unsigned int>("Enter the Student's Matriculation Number ");

	auto it = db->getStudents().find(matrikelNum);
	if(it!=db->getStudents().end()){
		const Student& student = db->getStudents().at(matrikelNum);
		cout<<"\nThe Details of the Student :"<<endl;
			student.write(std::cout);
			for(const auto& it : student.getEnrollments()){
				cout<<student.getMatrikelNumber()<<";";
				it.write(cout);
			}
		}
	else{
		cout<<"Student with Matrikel Number "<<matrikelNum<<" dosen't exsist"<<endl;
		}
	break;
	}

	/*Command 6 : Search Students*/
	case 6:{
	std::string nameSubString;
	nameSubString=getInput<std::string>("Enter a substring to search the student ");

	/*Calling search student function with cout ostream as parameter*/
	if(!(db->searchStudents(nameSubString,std::cout))){
		cout<<"!!! No matches found "<<endl;
		}
	break;
	}

	/*Command 7 : Update Students*/
	case 7:{
	try{
	unsigned int matrikelNum;
	std::string dataToUpdate="";
	matrikelNum=getInput<unsigned int>("Enter the Student's Matriculation Number ");
	unsigned short userInputSel=0;

	auto it = db->getStudents().find(matrikelNum);
	if(it!=db->getStudents().end()){
		do{
			cout<<"1 : Update the student's Identity"<<endl;
			cout<<"2 : Update the student's Address"<<endl;
			cout<<"3 : Update the student Enrollment"<<endl;
			cout<<"0 : To exit Update"<<endl;
			userInputSel=getInput<unsigned short>("*Choose an option to update* ");

			switch(userInputSel){
			case 1:{ 		/*Updating student identity details*/
				unsigned short option;
				do{
				cout<<endl;
				cout<<"   1 : Update the student's First Name"<<endl;
				cout<<"   2 : Update the student's Last Name"<<endl;
				cout<<"   3 : Update the student's D.O.B"<<endl;
				cout<<"   0 : To exit Student ID update"<<endl;
				option=getInput<unsigned short>("   *Choose an option to update Student ID* ");

				if(option==3){
					unsigned short date,month,year;
					cout<<"   Enter the Date of birth : eg 21 9 1994 "<<std::flush;
					cin>> date >> month >> year;cin.ignore();

					std::ostringstream out;
					out<<date<<"."<<month<<"."<<year;
					db->updateStudentID(matrikelNum,10+option,out.str());
				}
				if(option==1 || option==2){
					cout<<"   Enter a data to update "<<std::flush;
					std::getline(cin,dataToUpdate);

					/*Call to Update function in StudentDb with option code*/
					db->updateStudentID(matrikelNum,10+option,dataToUpdate);
					}
				else{break;}
				}while(option!=0);
				break;
			}

			case 2:{		/*Updating student's Address details*/
				unsigned short option;
				do{
				cout<<endl;
				cout<<"   1 : Update Street name"<<endl;
				cout<<"   2 : Update Postal code"<<endl;
				cout<<"   3 : Update City name"<<endl;
				cout<<"   4 : Update Additional Info"<<endl;
				cout<<"   0 : To exit Address update"<<endl;
				option=getInput<unsigned short>("   *Choose an option to update Address* ");
				if(option==0){break;}
				/**For updating pin code*/
					if(option==2){
						unsigned short pincode;
						do{
							cout<<"\n   Enter Pincode : it must be 5 digit "<<std::flush;
							cin.clear();
							cin>>pincode;
						}while(pincode<=0 || pincode>100000);
						dataToUpdate=std::to_string(pincode);
					}
					else{
						cout<<"   Enter a data to update "<<std::flush;
						std::getline(cin,dataToUpdate);
					}
					/*Call to Update function in StudentDb with option code*/
				db->updateStudentID(matrikelNum,(20+option),dataToUpdate);
				}while(option!=0);
				break;
			}

			case 3:{ 		/*Updating student's Enrollment details*/
				unsigned short option;
				do{
				cout<<endl;
				cout<<"   1 : Grade an enrollment"<<endl;
				cout<<"   2 : Remove an enrollment"<<endl;
				cout<<"   0 : To exit Address update"<<endl;

				option=getInput<unsigned short>("   *Choose an option to update Enrollment* ");
				if(option==0){break;}

				float updateGrade;
				bool isRemove=false;
				unsigned int findCourseKey;
				findCourseKey=getInput<unsigned int>("   Enter a course key ");

				auto itr = db->getCourses().find(findCourseKey);
				if (itr!=db->getCourses().end()){
					if(option==1){
					do{
						updateGrade=getInput<float>("   Enter a grade between 1-5 ");
					}while(updateGrade<=0 || updateGrade>5);
					isRemove=false;
					db->updateStudentEnrollment(matrikelNum,findCourseKey,updateGrade,isRemove);
					}
					if(option==2){
					isRemove=true;

					/*Call to Update Enrollment in StudentDb with option code*/
					db->updateStudentEnrollment(matrikelNum,findCourseKey,0,isRemove);
					}
				}
				else{
					cout<<"   This course dosen't exist in the database"<<endl;
				}
				}while(option!=0);
				break;
			}
			default:{
				break;
			}
			}
		}while(userInputSel!=0);
	}
	else{cout<<"Student with Matrikel Number "<<matrikelNum<<" dosen't exsist"<<endl;
	}
	}catch(const Poco::Exception& e){
		std::cerr<<"The Poco exception is "<<e.displayText()<<std::endl;
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}
	break;
	}

	/*Command 8 : Writing in a File from the Database*/
	case 8:{
		/**Declaring file to write and output stream*/
		std::ofstream writeFile;
		std::string fileName;
		fileName=getInput<string>("Enter the file name in .txt format ");
		if(fileName.find(".txt")==std::string::npos){
			fileName.append(".txt");
		}
		/*Opening the file and overwrites it if any data present*/
		writeFile.open(fileName, std::ios::out | std::ios::trunc);
		if(writeFile.is_open()){
			db->write(writeFile);
			cout<<"Successfully written in the file"<<endl;
		}
		else{
			cout<<"Error in writing data to file"<<endl;
		}
		writeFile.close();
	break;
	}

	/*Command 9 : Reading from a File and updating the database*/
	case 9:{
		/**Declaring file to read and input stream*/
		std::ifstream readFile;
		std::string fileName;
		fileName=getInput<string>("Enter the file name in .txt format ");
		if(fileName.find(".txt")==std::string::npos){
			fileName.append(".txt");
		}
		readFile.open(fileName,std::ios::in); /*Opening the file*/
		if(readFile.is_open()){
			cout<<"File opened successfully"<<endl;
			db->read(readFile);
		}
		else{
			cout<<"The file "<<fileName<<" dosen't exsist in this working directory"<<endl;
		}
		readFile.close(); /*Closing the file*/
		break;
	}

	case 10:{
		try {
			std::string domainName = "www.hhs.users.h-da.cloud";
			std::string portNum = "4242";
			boost::asio::ip::tcp::iostream stream;
			stream.connect(domainName,portNum);

			if(!stream){
				std::cerr<<"Connection failed"<<std::endl;
			}
			else{
			cout<<"Server connection done successfully"<<std::endl;
			}
			unsigned int numOfEntries,countOfEntries=0;
			numOfEntries=getInput<unsigned int>("Enter the number of entries to "
					"be downloaded from the server ");

			while(countOfEntries<numOfEntries){
				/*Sending generate command to the server*/
				std::string command = "generate";
				std::string jsonDataString;
				stream<<command<<endl;

				getline(stream,jsonDataString);
				cout<<jsonDataString<<endl;

				getline(stream,jsonDataString);
				cout<<jsonDataString<<endl;
				stream.flush();

				db->readFromServer(jsonDataString);
				++countOfEntries;

				getline(stream,jsonDataString);
				cout<<jsonDataString<<endl;
				stream.flush();
			}

			std::string command = "quit";
			stream<<command<<endl; /*Sending quit command to the server*/
			std::string response;
			getline(stream,response);
			cout<<response<<endl;
			stream.flush();
		} catch (std::exception& e) {
			std::cerr << "Exception: " << e.what() << std::endl;
		}
		break;
	}
	}
}while(userInput!=0);
}

SimpleUI::~SimpleUI(){

}


