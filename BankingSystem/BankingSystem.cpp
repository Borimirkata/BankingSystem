#include "BankingSystem.h"

bool BankingSystem::isUniquePerson(const MyString& firstName, const MyString& secondName, const MyString& egn) const {
	size_t clientsCount = clients.getSize();
	for (size_t i = 0; i < clientsCount; i++) {
		if ((clients[i].getFirstName() == firstName && clients[i].getSecondName() == secondName) || (clients[i].getEgn() == egn)) {
			return false;
		}
	}

	size_t employeesCount = employees.getSize();
	for (size_t i = 0; i < employeesCount; i++) {
		if ((employees[i].getFirstName() == firstName && employees[i].getSecondName() == secondName) || (employees[i].getEgn() == egn)) {
			return false;
		}
	}

	size_t thirdPartyCount = thirdPartyEmployees.getSize();
	for (size_t i = 0; i < thirdPartyCount; i++) {
		if ((thirdPartyEmployees[i].getFirstName() == firstName && thirdPartyEmployees[i].getSecondName() == secondName) || (thirdPartyEmployees[i].getEgn() == egn)) {
			return false;
		}
	}

	return true;
}

bool BankingSystem::validateClient(const MyString& firstName, const MyString& secondName, const MyString& password, int& index) const {
	size_t clientsCount = clients.getSize();
	for (size_t i = 0; i < clientsCount; i++) {
		if (clients[i].getFirstName() == firstName && clients[i].getSecondName() == secondName && clients[i].getPassword() == password) {
			index = i;
			return true;
		}
	}
	return false;
}

bool BankingSystem::validateEmployee(const MyString& firstName, const MyString& secondName, const MyString& password, int& index) const {
	size_t employeeCount = employees.getSize();
	for (size_t i = 0; i < employeeCount; i++) {
		if (employees[i].getFirstName() == firstName && employees[i].getSecondName() == secondName && employees[i].getPassword() == password) {
			index = i;
			return true;
		}
	}
	return false;
}

bool BankingSystem::validateThirdPartyEmployee(const MyString& firstName, const MyString& secondName, const MyString& password, int& index) const {
	size_t thirdPartyEmployeeCount = thirdPartyEmployees.getSize();
	for (size_t i = 0; i < thirdPartyEmployeeCount; i++) {
		if (thirdPartyEmployees[i].getFirstName() == firstName && thirdPartyEmployees[i].getSecondName() == secondName && thirdPartyEmployees[i].getPassword() == password) {
			index = i;
			return true;
		}
	}
	return false;
}

const MyString& BankingSystem::getType(const MyString& firstName, const MyString& secondName, const MyString& password, int& index) const {
	if (validateClient(firstName, secondName, password, index)) {
		return Roles::client;
	}
	else if (validateEmployee(firstName, secondName, password, index)) {
		return Roles::employee;
	}
	else if (validateThirdPartyEmployee(firstName, secondName, password, index)) {
		return Roles::thirdParty;
	}
	else {
		throw std::exception("User not found");
	}
}

void BankingSystem::signup(const MyString& firstName, const MyString& secondName, const MyString& egn, int age, const MyString& role, const MyString& password, const MyString& bankName, const MyString& address) {
	if (!isUniquePerson(firstName, secondName, egn)) {
		throw std::exception("Person with this egn or these names already exists.");
	}

	if (role == Roles::client) {
		clients.push_back(Client(firstName, secondName, egn, age, role, password, address));
		int index = clients.getSize() - 1;
		Client* currClient = &clients[index];
		for (int i = 0; i < banks.getSize(); i++) {
			currClient->addBank(this->getBankByName(banks[i].getBankName()));
		}
	}
	else if (role == Roles::employee) {
		employees.push_back(Employee(firstName, secondName, egn, age, role, password, bankName));
		size_t index = employees.getSize() - 1;
		Bank* bank = this->getBankByName(bankName);

		if (bank == nullptr) {
			throw std::exception("No bank with such name exists");
		}

		employees[index].setBank(bank);
		Employee* employee = &employees[index];
		bank->addEmployee(employee);
	}
	else if (role == Roles::thirdParty) {
		thirdPartyEmployees.push_back(ThirdPartyEmployee(firstName, secondName, egn, age, role, password));
		size_t index = thirdPartyEmployees.getSize() - 1;
		ThirdPartyEmployee* currEmployee = &thirdPartyEmployees[index];
		for (int i = 0; i < banks.getSize(); i++) {
			currEmployee->addBank(this->getBankByName(banks[i].getBankName()));
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
	int index = -1;
	MyString type = getType(firstName, secondName, password, index);

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

void BankingSystem::clientCheckAvl(const MyString& bankName, size_t accountNumber) const {
	if (currentClient == nullptr) {
		throw std::exception("Not logged in");
	}
	currentClient->check_avl(bankName, accountNumber);
}

void BankingSystem::clientOpen(const MyString& bankName) {
	if (currentClient == nullptr) {
		throw std::exception("Not logged in");
	}
	currentClient->open(bankName);
}

void BankingSystem::clientClose(const MyString& bankName, size_t accountNumber) {
	if (currentClient == nullptr) {
		throw std::exception("Not logged in");
	}
	currentClient->close(bankName, accountNumber);
}

void BankingSystem::clientRedeem(const MyString& bankName, size_t accountNumber, const MyString& verificationCode) {
	if (currentClient == nullptr) {
		throw std::exception("Not logged in");
	}
	currentClient->redeem(bankName, accountNumber, verificationCode);
}

void BankingSystem::clientChange(const MyString& newBankName, const MyString& currentBankName, size_t accountNumber) {
	if (currentClient == nullptr) {
		throw std::exception("Not logged in");
	}
	currentClient->change(newBankName, currentBankName, accountNumber);
}

void BankingSystem::clientList(const MyString& bankName) const {
	if (currentClient == nullptr) {
		throw std::exception("Not logged in");
	}
	currentClient->list(bankName);
}

void BankingSystem::clientMessages() const {
	if (currentClient == nullptr) {
		throw std::exception("Not logged in");
	}
	currentClient->messages();
}

void BankingSystem::employeePrintTasks() const {
	if (currentEmployee == nullptr) {
		throw std::exception("Not logged in");
	}
	currentEmployee->printTasks();
}

void BankingSystem::employeeView(size_t idx) const {
	if (currentEmployee == nullptr) {
		throw std::exception("Not logged in");
	}
	currentEmployee->view(idx);
}

void BankingSystem::employeeApprove(size_t idx) {
	if (currentEmployee == nullptr) {
		throw std::exception("Not logged in");
	}
	currentEmployee->approve(idx);
}

void BankingSystem::employeeDisapprove(size_t idx, const MyString& message) {
	if (currentEmployee == nullptr) {
		throw std::exception("Not logged in");
	}
	currentEmployee->disapprove(idx, message);
}

void BankingSystem::employeeValidate(size_t idx) {
	if (currentEmployee == nullptr) {
		throw std::exception("Not logged in");
	}
	currentEmployee->validate(idx);
}

void BankingSystem::thirdPartySendCheck(double sum, const MyString& bankName, const MyString& code, const MyString& egn) {
	if (currentThirdParty == nullptr) {
		throw std::exception("Not logged in");
	}
	currentThirdParty->send_check(sum, bankName, code, egn);
}

void BankingSystem::userHelp() const {
	if (currentClient != nullptr) {
		currentClient->help();
	}
	else if (currentEmployee != nullptr) {
		currentEmployee->help();
	}
	else if (currentThirdParty != nullptr) {
		currentThirdParty->help();
	}
	else {
		throw std::exception("Not logged in");
	}
}

void BankingSystem::userWhoami() const {
	if (currentClient != nullptr) {
		currentClient->whoami();
	}
	else if (currentEmployee != nullptr) {
		currentEmployee->whoami();
	}
	else if (currentThirdParty != nullptr) {
		currentThirdParty->whoami();
	}
	else {
		throw std::exception("Not logged in");
	}
}

void BankingSystem::exit() {
	if (currentClient != nullptr) {
		currentClient->exit();
		currentClient = nullptr;
	}
	else if (currentEmployee != nullptr) {
		currentEmployee->exit();
		currentEmployee = nullptr;
	}
	else if (currentThirdParty != nullptr) {
		currentThirdParty->exit();
		currentThirdParty = nullptr;
	}
	else {
		throw std::exception("No one was logged in!");
	}
}

void BankingSystem::quit() {
	currentClient = nullptr;
	currentEmployee = nullptr;
	currentThirdParty = nullptr;
}

void BankingSystem::writeToFile() const {
	std::ofstream ofs("Data.dat", std::ios::out | std::ios::binary);
	if (!ofs.is_open()) {
		throw std::exception("Not opened");
	}

	size_t banksCount = banks.getSize();
	ofs.write((const char*)&banksCount, sizeof(size_t));
	for (size_t i = 0; i < banksCount; i++) {
		banks[i].writeToFile(ofs);
	}

	size_t clientsCount = clients.getSize();
	ofs.write((const char*)&clientsCount, sizeof(size_t));
	for (size_t i = 0; i < clientsCount; i++) {
		clients[i].writeToFile(ofs);
	}

	size_t employeesCount = employees.getSize();
	ofs.write((const char*)&employeesCount, sizeof(size_t));
	for (size_t i = 0; i < employeesCount; i++) {
		employees[i].writeToFile(ofs);
	}

	size_t thirdPartyCount = thirdPartyEmployees.getSize();
	ofs.write((const char*)&thirdPartyCount, sizeof(size_t));
	for (size_t i = 0; i < thirdPartyCount; i++) {
		thirdPartyEmployees[i].writeToFile(ofs);
	}

	ofs.clear();
	ofs.close();
}

void BankingSystem::readFromFile() {
	std::ifstream ifs("Data.dat", std::ios::in | std::ios::binary);
	if (!ifs.is_open()) {
		throw std::exception("Not opened");
	}

	size_t banksCount = 0;
	ifs.read((char*)&banksCount, sizeof(size_t));
	for (size_t i = 0; i < banksCount; i++) {
		Bank bankToRead;
		bankToRead.readFromFile(ifs);
		banks.push_back(bankToRead);
	}

	size_t clientsCount = 0;
	ifs.read((char*)&clientsCount, sizeof(size_t));
	for (size_t i = 0; i < clientsCount; i++) {
		Client clientToRead;
		clientToRead.readFromFile(ifs);
		clients.push_back(clientToRead);
	}

	size_t employeesCount = 0;
	ifs.read((char*)&employeesCount, sizeof(size_t));
	for (size_t i = 0; i < employeesCount; i++) {
		Employee employeeToRead;
		employeeToRead.readFromFile(ifs);
		employees.push_back(employeeToRead);
	}

	size_t thirdPartyCount = 0;
	ifs.read((char*)&thirdPartyCount, sizeof(size_t));
	for (size_t i = 0; i < thirdPartyCount; i++) {
		ThirdPartyEmployee toRead;
		toRead.readFromFile(ifs);
		thirdPartyEmployees.push_back(toRead);
	}

	ifs.clear();
	ifs.close();
}

BankingSystem::~BankingSystem() {
	writeToFile();

	banks.clear();
	clients.clear();
	employees.clear();
	thirdPartyEmployees.clear();

	delete currentClient;
	delete currentEmployee;
	delete currentThirdParty;

	currentClient= nullptr;
	currentEmployee = nullptr;
	currentThirdParty = nullptr;
}