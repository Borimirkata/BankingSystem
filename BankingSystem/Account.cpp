#include "Account.h"

Account::Account(const MyString& bankName, size_t accountNumber, double balance) {
	setBankName(bankName);
	setAccountNumber(accountNumber);
	setBalance(balance);
}

const MyString& Account::getBankName() const {
	return bankName;
}

size_t Account::getAccountNumber() const {
	return accountNumber;
}

double Account::getBalance() const {
	return balance;
}

void Account::setBankName(const MyString& bankName) {
	if (bankName == nullptr) {
		throw std::exception("Nullptr given");
	}
	this->bankName = bankName;
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