#include "Bank.h"
#include "Client.h"

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

int Bank::getEmployeeIdx(const MyString& egn) const {
	size_t count = employees.getSize();

	for (size_t i = 0; i < count; i++) {
		if ((employees[i]->getEgn() == egn)) {
			return i;
		}
	}
	return -1;
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

Bank::Bank(const MyString& bankName) {
	setBankName(bankName);
}

void Bank::setBankName(const MyString& bankName) {
	this->bankName = bankName;
}

Request* Bank::getRequestByIndex(int task_id)
{
	if (task_id >= requests.getSize()) {
		throw std::exception("Index out of bounds");
	}

	return &requests[task_id];
}

Employee* Bank::getEmployeeByIndex(int idx)
{
	if (idx >= employees.getSize()) {
		throw std::exception("Index out of bounds");
	}

	return employees[idx];
}

Client* Bank::getClient(const MyString& egn) {
	int index = getClientIdx(egn);

	return clients[index];
}

Account* Bank::getAccount(size_t accountNumber) {
	int index = getAccountIdx(accountNumber);

	if (index == -1) {
		throw std::exception("Incorrect account number!");
	}

	return &accounts[index];
}

const MyString& Bank::getBankName() const {
	return bankName;
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

void Bank::sendRequestToEmployee(const Request& request) {

	if (request.getType() == type1) {
		requests.push_back(Request(request.getType(), request.getClient()));
	}
	else if ((request.getType() == type2)) {
		requests.push_back(Request(request.getType(), request.getClient(), request.getAccountNum()));
	}
	else if ((request.getType() == type3) || isSubstring(request.getType(), type3)){
		requests.push_back(Request(request.getType(), request.getClient(), request.getAccountNum(),request.getNameOfBank()));
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

void Bank::printAccounts() const {
	size_t count = accounts.getSize();

	if (count == 0) {
		std::cout << "No accounts available" << std::endl;
	}

	for (size_t i = 0; i < count; i++) {
		accounts[i].printAccount();
	}
}

MyVector<Employee*>& Bank::getEmployees()
{
	return employees;
}

int Bank::getEmployeeWithLeastTasks() const {
	if (employees.empty()) {
		throw std::exception("There are no employees to give out tasks to!");
	}
	int indexToReturn = 0;
	int count = employees.getSize();
	int minTasks = employees[0]->getTasks().getSize();

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

	for (int i = 0; i < clientCount; i++) {
		if (clients[i]->getFirstName() == client->getFirstName() && clients[i]->getSecondName() == client->getSecondName()
			&& clients[i]->getEgn() == client->getEgn() && clients[i]->getAge() == client->getAge()) {
			return true;
		}
	}
	return false;
}

bool Bank::checkClient(Client* client) const {
	return validateClient(client);
}

void Bank::addClient(Client* client) {
	clients.push_back(client);
}

void Bank::addEmployee(Employee* employee) {
	employees.push_back(employee);
}

void Bank::deleteRequest(size_t index) {
	requests.erase(index);
}