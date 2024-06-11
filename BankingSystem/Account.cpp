#include "Account.h"

Account::Account(size_t accountNumber, double balance) {
	setAccountNumber(accountNumber);
	setBalance(balance);
}

size_t Account::getAccountNumber() const {
	return accountNumber;
}

double Account::getBalance() const {
	return balance;
}

void Account::setAccountNumber(size_t accountNumber) {
	if (accountNumber < NULL_VALUE) {
		throw std::out_of_range("Account Number cannot be bellow zero");
	}
	this->accountNumber = accountNumber;
}

void Account::setBalance(double balance) {
	if (balance < NULL_VALUE) {
		throw std::out_of_range("Balance cannot be bellow zero");
	}
	this->balance = balance;
}

void Account::printAccount() const {
	std::cout << "* " << accountNumber << std::endl;
}