#include "BankingSystem.h"

MyVector<Bank> BankingSystem::banks;

int BankingSystem::getClientIndex(const MyString& egn) const {
	int count = clients.getSize();

	for (int i = 0; i < count; i++) {
		if (clients[i].getEgn() == egn) {
			return i;
		}
	}
	return -1;
}

int BankingSystem::getEmployeeIndex(const MyString& egn) const {
	int count = employees.getSize();

	for (int i = 0; i < count; i++) {
		if (employees[i].getEgn() == egn) {
			return i;
		}
	}
	return -1;
}

int BankingSystem::getThirdEmployeeIndex(const MyString& egn) const {
	int count = thirdPartyEmployees.getSize();

	for (int i = 0; i < count; i++) {
		if (thirdPartyEmployees[i].getEgn() == egn) {
			return i;
		}
	}
	return -1;
}

int BankingSystem::getBankIndex(const MyString& bankName) const {
	int count = banks.getSize();

	for (int i = 0; i < count; i++) {
		if (banks[i].getBankName() == bankName) {
			return i;
		}
	}
	return -1;
}

void BankingSystem::createBank(const MyString& bankName) {
	banks.push_back(Bank(bankName));
}

Bank* BankingSystem::getBankByName(const MyString& bankName)
{
	int index = -1;
	size_t banksCount = banks.getSize();

	for (size_t i = 0; i < banksCount; i++) {
		if ((banks[i].getBankName() == bankName)) {
			return &banks[i];
		}
	}
	return nullptr;
}

bool BankingSystem::validateClient(const MyString& firstName, const MyString& secondName, const MyString& password,int& index) const{
	int clientsCount = clients.getSize();
	for (int i = 0; i < clientsCount; i++) {
		if (clients[i].getFirstName() == firstName && clients[i].getSecondName() == secondName && clients[i].getPassword() == password) {
			index = i;
			return true;
		}
	}
	return false;
}

bool BankingSystem::validateEmployee(const MyString& firstName, const MyString& secondName, const MyString& password,int& index) const{
	int employeeCount = employees.getSize();
	for (int i = 0; i < employeeCount; i++) {
		if (employees[i].getFirstName() == firstName && employees[i].getSecondName() == secondName && employees[i].getPassword() == password) {
			index = i;
			return true;
		}
	}
	return false;
}

bool BankingSystem::validateThirdPartyEmployee(const MyString& firstName, const MyString& secondName, const MyString& password,int& index) const{
	int thirdPartyEmployeeCount = thirdPartyEmployees.getSize();
	for (int i = 0; i < thirdPartyEmployeeCount; i++) {
		if (thirdPartyEmployees[i].getFirstName() == firstName && thirdPartyEmployees[i].getSecondName() == secondName && thirdPartyEmployees[i].getPassword() == password) {
			index = i;
			return true;
		}
	}
	return false;
}

const MyString& BankingSystem::getType(const MyString& firstName, const MyString& secondName, const MyString& password,int& index) const {
	if (validateClient(firstName, secondName, password,index)) {
		return Roles::client;
	}
	else if (validateEmployee(firstName, secondName, password,index)) {
		return Roles::employee;
	}
	else if (validateThirdPartyEmployee(firstName, secondName, password,index)) {
		return Roles::thirdParty;
	}
	else {
		throw std::exception("User not found");
	}
}

void BankingSystem::signup(const MyString& firstName, const MyString& secondName, const MyString& egn, int age, const MyString& role, const MyString& password, const MyString& bankName,const MyString& address) {
	if (role == Roles::client) {
		clients.push_back(Client(firstName, secondName, egn, age, role, password,address));
		int index = clients.getSize() - 1;
		for (int i = 0; i < banks.getSize(); i++) {
			clients[index].addBank(banks[i].getBankName());
		}
	}
	else if (role == Roles::employee) {
		employees.push_back(Employee(firstName, secondName, egn, age, role, password, bankName));
	}
	else if (role == Roles::thirdParty) {
		thirdPartyEmployees.push_back(ThirdPartyEmployee(firstName, secondName, egn, age, role, password));
		int index = thirdPartyEmployees.getSize() - 1;
		for (int i = 0; i < banks.getSize(); i++) {
			thirdPartyEmployees[index].addBank(banks[i].getBankName());
		}
	}
	else {
		throw std::exception("Invalid role");
	}
}

void BankingSystem::login(const MyString& firstName, const MyString& secondName, const MyString& password) {

	if (currentClient != nullptr || currentEmployee != nullptr || currentThirdParty != nullptr) {
		throw std::exception("Can only have one logged person at a time");
	}
	int index=-1;
	MyString type = getType(firstName, secondName, password,index);

	if (type == Roles::client) {
		currentClient = &clients[index];
	}
	else if (type == Roles::employee) {
		currentEmployee = &employees[index];
	}
	else if (type == Roles::thirdParty) {
		currentThirdParty = &thirdPartyEmployees[index];
	}
}

void BankingSystem::exit() {
	if (currentClient != nullptr) {
		currentClient = nullptr;
	}
	else if (currentEmployee != nullptr) {
		currentEmployee = nullptr;
	}
	else if (currentThirdParty != nullptr) {
		currentThirdParty = nullptr;
	}
	else {
		throw std::exception("No one was logged in!");
	}
}

void BankingSystem::quit() {
	currentBank = nullptr;
	currentClient = nullptr;
	currentEmployee = nullptr;
	currentThirdParty = nullptr;
}