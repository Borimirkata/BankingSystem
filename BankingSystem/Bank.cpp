#include "Bank.h"

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

void Bank::pushTask(const MyString& task) {
	tasks.push_back(task);
}

const MyString& Bank::getTaskAtIndex(size_t index) const {
	/*if (index >=tasks.getSize()) {
		throw std::exception("Index out of range!");
	}*/
	return tasks[index];
}

void Bank::printAccounts() const {
	size_t accountsSize = accounts.getSize();
	if (accountsSize == 0) {
		throw std::exception("There are no accounts in this Bank!");
	}

	for (size_t i = 0; i < accountsSize; i++) {
		std::cout << "* " << accounts[i].getAccountNumber() << std::endl;
	}
}