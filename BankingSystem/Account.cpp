#include "Account.h"

Account::Account(size_t accountNumber, double balance, Client* client) {
	setAccountNumber(accountNumber);
	setBalance(balance);
	this->client = client;
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

void Account::writeToFile(std::ofstream& ofs) const {
	ofs.write((const char*)&accountNumber, sizeof(size_t));
	ofs.write((const char*)&balance, sizeof(double));

}

void Account::readFromFile(std::ifstream& ifs) {
	ifs.read((char*)&accountNumber, sizeof(size_t));
	ifs.read((char*)&balance, sizeof(double));
}

Account::~Account() {
	client = nullptr;
}