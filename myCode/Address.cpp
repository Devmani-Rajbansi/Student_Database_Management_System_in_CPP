/*
 * Address.cpp
 *
 * Author: devma
 */
#include<iostream>
#include <string>

#include "Address.h"

Address::Address(string street,unsigned short postalCode,string cityName,
		string additionalInfo):street(street),postalCode(postalCode),
		cityName(cityName),additionalInfo(additionalInfo)
{

}

Address::Address(string street, unsigned short postalCode, string cityName)
:street(street),postalCode(postalCode),cityName(cityName){

}

const string& Address::getAdditionalInfo() const
{
	return additionalInfo;
}

const string& Address::getCityName() const
{
	return cityName;
}

unsigned short Address::getPostalCode() const
{
	return postalCode;
}

const std::string& Address::getStreet() const
{
	return street;
}

void Address::write(std::ostream &out) const
{
	/*Populating the outstream*/
	out<<street+";";
	out<<std::to_string(postalCode)+";";
	out<<cityName+";";
	if(this->getAdditionalInfo()!=""){
		out<<additionalInfo;
	}
}



Address::Address()
{

}

