#pragma once

#include "MyString.h"
#include "MyVector.hpp"
#include "Client.h"
#include "Bank.h"
#include "Employee.h"
#include "ThirdPartyEmployee.h"

class Bank;
class Client;
class Employee;
class ThirdPartyEmployee;

class BankingSystem {
private:
	static MyVector<Bank> banks;
	static MyVector<Client> clients;
	static MyVector<Employee> employees;
	static MyVector<ThirdPartyEmployee> thirdPartyEmployees;

	Client* currentClient = nullptr;
	Employee* currentEmployee = nullptr;
	ThirdPartyEmployee* currentThirdParty = nullptr;
public:
	//logic that for sign up and login (we use the nullptr)
	//for the sign up we add to the vectors a new user and we read from the console its information
	//and here we weill have every function for our three types of people and if the current is nullptr we will not execute,because it is not logged in
	//and for the exit function(just put back the pointer to be nullptr

	static void createBank(const MyString& bankName);

	static Bank* getBankByName(const MyString& bankName);

};
