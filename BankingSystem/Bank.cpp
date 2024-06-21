#include "Bank.h"
#include "Client.h"

int Bank::getEmployeeIdx(const MyString& egn) const {
	size_t count = employees.getSize();

	for (size_t i = 0; i < count; i++) {
		if ((employees[i]->getEgn() == egn)) {
			return i;
		}
	}
	return -1;
}

int Bank::getEmployeeWithLeastTasks() const {
	if (employees.empty()) {
		throw std::exception("There are no employees to give out tasks to!");
	}
	int indexToReturn = 0;
	size_t count = employees.getSize();
	size_t minTasks = employees[0]->getTasks().getSize();

	for (int i = 1; i < count; i++) {
		if (employees[i]->getTasks().getSize() < minTasks) {
			indexToReturn = i;
			minTasks = employees[i]->getTasks().getSize();
		}
	}
	return indexToReturn;
}

bool Bank::validateClient(Client* client) const {
	size_t clientCount = clients.getSize();

	for (size_t i = 0; i < clientCount; i++) {
		if (clients[i]->getFirstName() == client->getFirstName() && clients[i]->getSecondName() == client->getSecondName()
			&& clients[i]->getEgn() == client->getEgn() && clients[i]->getAge() == client->getAge()) {
			return true;
		}
	}
	return false;
}

int Bank::getClientIdx(const MyString& egn) const {
	size_t count = clients.getSize();

	for (size_t i = 0; i < count; i++) {
		if ((clients[i]->getEgn() == egn)) {
			return i;
		}
	}
	return -1;
}

int Bank::getAccountIdx(size_t accountNumber) const {
	size_t count = accounts.getSize();

	for (size_t i = 0; i < count; i++) {
		if (accounts[i].getAccountNumber() == accountNumber) {
			return i;
		}
	}

	return -1;
}

int Bank::getRequestIdx(const MyString& egn) const {
	size_t count = requests.getSize();

	for (size_t i = 0; i < count; i++) {
		Client* client = requests[i].getClient();
		if ((client->getEgn() == egn)) {
		return i;
		}
	}
	return -1;
}

Bank::Bank(const MyString& bankName) {
	this->bankName = bankName;
}

void Bank::addClient(Client* client) {
	clients.push_back(client);
}

double Bank::getAccountBalance(size_t number) {

	if (accounts.empty()) {
		throw std::exception("No accounts available!");
	}

	size_t accountsSize = accounts.getSize();

	for (size_t i = 0; i < accountsSize; i++) {
		if ((accounts[i].getAccountNumber() == number)) {
			return accounts[i].getBalance();
		}
	}

	throw std::exception("No account with that number found");
}

void Bank::deleteRequest(size_t index) {
	requests.erase(index);
}

void Bank::sendRequestToEmployee(const Request& request) {

	if (request.getType() == BankData::type1) {
		requests.push_back(Request(request.getType(), request.getClient()));
	}
	else if ((request.getType() == BankData::type2)) {
		requests.push_back(Request(request.getType(), request.getClient(), request.getAccountNum()));
	}
	else if ((request.getType() == BankData::type3) || isSubstring(request.getType(), BankData::type3)) {
		requests.push_back(Request(request.getType(), request.getClient(), request.getAccountNum(), request.getNameOfBank()));
	}
	else {
		throw std::exception("Wrong request type");
	}

	int employeeIndex = getEmployeeWithLeastTasks();
	size_t idx = requests.getSize() - 1;

	employees[employeeIndex]->addTask(&requests[idx]);
}

void Bank::sendAnswerToClient(const Message& message, Client* client)
{
	client->addMessage(message);
}

Account* Bank::getAccount(size_t accountNumber) {
	int index = getAccountIdx(accountNumber);

	if (index == -1) {
		throw std::exception("Incorrect account number!");
	}

	return &accounts[index];
}

void Bank::addAccount(size_t accountNumber, double balance, Client* client) {
	accounts.push_back(Account(accountNumber, balance, client));
}

void Bank::deleteAccount(size_t accountNumber, Client* client) {
	int index = getAccountIdx(accountNumber);

	if (index == -1) {
		throw std::exception("No account with that number exists");
	}

	accounts.erase(index);
}

void Bank::printAccounts() const {
	size_t count = accounts.getSize();

	if (count == 0) {
		std::cout << "No accounts available" << std::endl;
	}

	for (size_t i = 0; i < count; i++) {
		accounts[i].printAccount();
	}
}

void Bank::addEmployee(Employee* employee) {
	employees.push_back(employee);
}

MyVector<Employee*>& Bank::getEmployees() {
	return employees;
}

Client* Bank::getClient(const MyString& egn) {
	int index = getClientIdx(egn);

	return clients[index];
}

bool Bank::checkClient(Client* client) const {
	return validateClient(client);
}

Request* Bank::getRequestByIndex(int task_id) {
	if (task_id >= requests.getSize()) {
		throw std::exception("Index out of bounds");
	}

	return &requests[task_id];
}

const MyString& Bank::getBankName() const {
	return bankName;
}

void Bank::writeToFile(std::ofstream& ofs) const {
	writeStringToFile(ofs, bankName);

	size_t accountsSize = accounts.getSize();
	ofs.write((const char*)&accountsSize, sizeof(size_t));
	for (size_t i = 0; i < accountsSize; i++) {
		accounts[i].writeToFile(ofs);
	}

	size_t requestsSize = requests.getSize();
	ofs.write((const char*)&requestsSize, sizeof(size_t));
	for (size_t i = 0; i < requestsSize; i++) {
		requests[i].writeToFile(ofs);
	}

	size_t clientsSize = clients.getSize();
	ofs.write((const char*)&clientsSize, sizeof(size_t));
	for (size_t i = 0; i < clientsSize; i++) {
		clients[i]->writeToFile(ofs);
	}

	size_t employeesSize = employees.getSize();
	ofs.write((const char*)&employeesSize, sizeof(size_t));
	for (size_t i = 0; i < employeesSize; i++) {
		employees[i]->writeToFile(ofs);
	}

}
void Bank::readFromFile(std::ifstream& ifs) {
	bankName=readStringFromFile(ifs);

	size_t accountsSize=0;
	ifs.read((char*)&accountsSize, sizeof(size_t));
	for (size_t i = 0; i < accountsSize; i++) {
		Account accountToRead;
		accountToRead.readFromFile(ifs);
		accounts.push_back(accountToRead);
	}

	size_t requestsSize =0;
	ifs.read((char*)&requestsSize, sizeof(size_t));
	for (size_t i = 0; i < requestsSize; i++) {
		Request requestToRead;
		requestToRead.readFromFile(ifs);
		requests.push_back(requestToRead);
	}

	size_t clientsSize = 0;
	ifs.read((char*)&clientsSize, sizeof(size_t));
	for (size_t i = 0; i < clientsSize; i++) {
		Client* clientToRead=nullptr;
		clientToRead->readFromFile(ifs);
		clients.push_back(clientToRead);
	}

	size_t employeesSize = 0;
	ifs.read((char*)&employeesSize, sizeof(size_t));
	for (size_t i = 0; i < employeesSize; i++) {
		Employee* employeeToRead = nullptr;
		employeeToRead->readFromFile(ifs);
		employees.push_back(employeeToRead);
	}
}