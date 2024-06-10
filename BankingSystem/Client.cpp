#include "Client.h"

int Client::getAccountIndex(const MyString& bankName, size_t accountNumber) const {
	int index = -1;
	size_t accountsCount = accounts.getSize();

	for (size_t i = 0; i < accountsCount; i++) {
		if ((accounts[i].getBankName() == bankName) && (accounts[i].getAccountNumber() == accountNumber)) {
			return i;
		}
	}
	return -1;
}

int Client::getBankIndex(const MyString& bankName) const{
	int index = -1;
	size_t accountsCount = accounts.getSize();

	for (size_t i = 0; i < accountsCount; i++) {
		if ((accounts[i].getBankName() == bankName)) {
			return i;
		}
	}
	return -1;
}

Client::Client(const MyString& firstName, const MyString& secondName, const MyString& egn, size_t age, const MyString& role, const MyString& password, const MyString& address):User(firstName,secondName,egn,age,role,password){
	this->address = address;
}

void Client::check_avl(const MyString& bankName, size_t accountNumber) const {
	int index = getAccountIndex(bankName, accountNumber);
	if (index == -1) {
		throw std::exception("Either the bank name is incorrect,or the accountNumber is incorrect");
	}
	std::cout << "Balance: " << accounts[index].getBalance() << "$" << std::endl;
}

void Client::list(const MyString& bankName) const {
	int index = getBankIndex(bankName);
	if (index == -1) {
		throw std::exception("Bank name is incorrect!");
	}

	size_t accountsSize = accounts.getSize();
	for (size_t i = 0; i < accountsSize; i++) {
		if (accounts[i].getBankName() == bankName) {
			std::cout << "* " << accounts[i].getAccountNumber()<<std::endl;
		}
	}
}

void Client::messages() const {
	if (message.empty()) {
		std::cout << "No messages to show" << std::endl;
	}

	size_t messagesSize = message.getSize();
	for (size_t i = 0; i < messagesSize; i++) {
		std::cout << "[" << (i + 1) << "] " << message[i].getContent() << std::endl;
	}
}

