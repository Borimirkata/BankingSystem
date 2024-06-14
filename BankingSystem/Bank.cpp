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
		if ((requests[i].getEgn() == egn)) {
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

void Bank::sendRequestToEmployee(const MyString& role, Client* client) {
	requests.push_back(Request(role, client));

	int employeeIndex = getEmployeeWithLeastTasks();
	size_t idx = requests.getSize() - 1;

	employees[employeeIndex]->addTask(&requests[idx]);

	//employees[0]->approve(idx);
}

void Bank::sendAnswerToClient(const Message& message, Client* client)
{
	// check for approved open

	client->addMessage(message);
}

void Bank::getCurrentAccount(size_t accountNumber, Account& _currentAcc) {
	int index = getAccountIdx(accountNumber);

	if (index == -1) {
		throw std::exception("No such account exists");
	}

	_currentAcc = accounts[index];
}

void Bank::getCurrentRequest(const MyString& egn, Request& _currentReq) {
	int index = getRequestIdx(egn);

	if (index == -1) {
		throw std::exception("No such request exists");
	}

	_currentReq = requests[index];
}

void Bank::printAccounts() const {
	size_t count = accounts.getSize();

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