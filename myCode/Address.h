/*
 * Address.h
 *
 * Author: devma
 */

#ifndef ADDRESS_H_
#define ADDRESS_H_

#include <string>

using std::string;

/**
 * @class Address
 * @brief Represents a student's Address.
 */
class Address
{
private:

	/**@brief street Name of the street*/
	std::string street;

	/**@brief postalCode Postal Code of the area*/
	unsigned short postalCode;

	/**@brief cityName Name of the city*/
	std::string cityName;

	/**@brief additionalInfo Any additional Information*/
	std::string additionalInfo;

public:

	/**
	 * @fn Address(string street,unsigned short postalCode,string cityName,
			string additionalInfo)
	 * @brief Constructor for Address class
	 *
	 * @param street Name of the street
	 * @param postalCode Postal Code of the area
	 * @param cityName Name of the city
	 * @param additionalInfo Any additional Information (optional)
	 */
	Address(string street,unsigned short postalCode,string cityName,
			string additionalInfo);

	/**
	 * @fn Address(string street,unsigned short postalCode,string cityName,
			string additionalInfo)
	 * @brief Constructor for Address class
	 *
	 * @param street Name of the street
	 * @param postalCode Postal Code of the area
	 * @param cityName Name of the city
	 */
	Address(string street,unsigned short postalCode,string cityName);

	/**
	* @fn const string& getAdditionalInfo() const
	* @brief Gets any additional information about the address
	*
	* @return The additionalInfo of the address
	*/
	const string& getAdditionalInfo() const;

	/**
	* @fn const string& getCityName() const
	* @brief Gets the name of the city
	*
	* @return The name of the city
	*/
	const string& getCityName() const;

	/**
	* @fn unsigned short getPostalCode() const
	* @brief Gets the postal code of the area
	*
	* @return The postalCode of the address
	*/
	unsigned short getPostalCode() const;

	/**
	* @fn const std::string& getStreet() const
	* @brief Gets the street number in the address
	*
	* @return The streetNumber in the address
	*/
	const std::string& getStreet() const;

	/**
	 * @brief Write information of Student's Address to an output stream.
	 * @param out The output stream.
	 */
	void write(std::ostream &out) const;

    /**
     * @brief Destructor for the Address class.
     */
	Address();

};

#endif /* ADDRESS_H_ */
