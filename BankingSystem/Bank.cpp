#include "Bank.h"

int Bank::getAccountIdx(size_t accountNumber) const{
	size_t count = accounts.getSize();
	
	for (size_t i = 0; i < count; i++) {
		if (accounts[i].getAccountNumber() == accountNumber) {
			return i;
		}
	}

	return -1;
}

int Bank::getRequestIdx(const MyString& first, const MyString& second,const MyString& egn,size_t age) {
	size_t count = requests.getSize();

	for (size_t i = 0; i < count; i++) {
		if ((requests[i].getFirstName()==first) && (requests[i].getSecondName() == second) && (requests[i].getEgn()==egn) && (requests[i].getAge()==age)) {
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

void Bank::addAccount(size_t accountNumber, double balance) {
	accounts.push_back(Account(accountNumber, balance));
}

void Bank::addRequests(const MyString& role, const MyString& firstName, const MyString& secondName, const MyString& egn, size_t age) {
	requests.push_back(Request(role, firstName, secondName, egn, age));
}

void Bank::getCurrentAccount(size_t accountNumber, Account*& currentAcc) {
	int index = getAccountIdx(accountNumber);
	
	if (index == -1) {
		throw std::exception("No such account exists");
	}

	currentAcc = &accounts[index];
}

void Bank::getCurrentRequest(const MyString& firstName, const MyString& secondName, const MyString& egn, size_t age, Request*& currentReq) {
	int index = getRequestIdx(firstName, secondName, egn, age);
	
	if (index == -1) {
		throw std::exception("No such request exists");
	}

	currentReq = &requests[index];
}

void Bank::printAccounts() const {
	size_t count = accounts.getSize();

	for (size_t i = 0; i < count; i++) {
		accounts[i].printAccount();
	}
}