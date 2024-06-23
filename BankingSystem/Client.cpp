#include "Client.h"

int Client::getBankIndex(const MyString& bankName) const {
	size_t banksCount = banks.getSize();

	for (size_t i = 0; i < banksCount; i++) {
		if ((banks[i]->getBankName() == bankName)) {
			return i;
		}
	}
	return -1;
}

int Client::getCheckIndex(const MyString& code) const {
	size_t checksCount = checks.getSize();

	for (size_t i = 0; i < checksCount; i++) {
		if ((checks[i].getCode() == code)) {
			return i;
		}
	}
	return -1;
}

void Client::addCheck(const Check& check) {
	checks.push_back(check);
}

Client::Client(const MyString& firstName, const MyString& secondName, const MyString& egn, size_t age, const MyString& role, const MyString& password, const MyString& address) :User(firstName, secondName, egn, age, role, password) {
	this->address = address;
}

Bank* Client::getBank(const MyString& bankName) {
	int index = getBankIndex(bankName);

	if (index == -1) {
		throw std::exception("Incorrect bank name");
	}
	return banks[index];
}

void Client::addMessage(const Message& mess) {
	message.push_back(mess);
}

Message* Client::getMessageAtIndex(size_t index) {
	return &message[index];
}

void Client::receiveCheck(const Check& check) {
	addCheck(check);
}

void Client::addBank(Bank* bank) {
	banks.push_back(bank);
	bank->addClient(this);
}

void Client::check_avl(const MyString& bankName, size_t accountNumber) const {
	int index = getBankIndex(bankName);
	if (index == -1) {
		throw std::exception("There is no bank with such name!");
	}
	Bank* currentBank = banks[index];
	std::cout << "Balance: " << currentBank->getAccountBalance(accountNumber) << " $" << std::endl;
}

void Client::open(const MyString& bankName) {

	Bank* currentB = getBank(bankName);

	currentB->sendRequestToEmployee(Request(ClientData::type1, this));
}

void Client::close(const MyString& bankName, size_t accountNumber) {
	int index = getBankIndex(bankName);
	if (index == -1) {
		throw std::exception("There is no bank with such name!");
	}
	Bank* currentB = banks[index];

	currentB->sendRequestToEmployee(Request(ClientData::type2, this, accountNumber));
}

void Client::redeem(const MyString& bankName, size_t accountNumber, const MyString& verificationCode) {
	int bankIndex = getBankIndex(bankName);

	if (bankIndex == -1) {
		throw std::exception("Incorrect bankName");
	}
	int checkIndex = getCheckIndex(verificationCode);

	if (checkIndex == -1) {
		throw std::exception("Invalid code");
	}

	Bank* currentBank = banks[bankIndex];
	Account* currentAccount = currentBank->getAccount(accountNumber);
	double currentBalance = currentAccount->getBalance();
	double sumCheck = checks[checkIndex].getSum();

	double newBalance = currentBalance + sumCheck;
	currentAccount->setBalance(newBalance);
}

void Client::change(const MyString& newBankName, const MyString& currentBankName, size_t accountNumber) {
	int indexCurrent = getBankIndex(currentBankName);
	int indexNew = getBankIndex(newBankName);

	if (indexCurrent == -1 || indexNew == -1) {
		throw std::exception("Incorrect bank names!");
	}
	Bank* currentB = banks[indexCurrent];
	Bank* newB = banks[indexNew];

	newB->sendRequestToEmployee(Request(ClientData::type3, this, accountNumber, currentB->getBankName()));
}

void Client::list(const MyString& bankName) const {
	int index = getBankIndex(bankName);
	if (index == -1) {
		throw std::exception("bank name is incorrect!");
	}

	banks[index]->printAccounts();

}

void Client::messages() const {
	if (message.empty()) {
		std::cout << "No messages to show" << std::endl;
	}

	size_t count = message.getSize();
	for (size_t i = 0; i < count; i++) {
		std::cout << "[" << (i+1) << "] ";
		message[i].printMessage();
	}
}

void Client::help() const {
	std::cout << "The commands that you can use are:" << std::endl;
	std::cout << "-check_avl [bank_name] [account_number] " << std::endl;
	std::cout << "-open [bank_name] " << std::endl;
	std::cout << "-close [bank_name] [account_number]  " << std::endl;
	std::cout << "-redeem [bank_name] [account_number] [verification_code]  " << std::endl;
	std::cout << "-change [new_bank_name] [current_bank_name] [account_number] " << std::endl;
	std::cout << "-list [bank_name] " << std::endl;
	std::cout << "-messages " << std::endl;
	std::cout << "-whoami " << std::endl;
	std::cout << "-exit " << std::endl;
}

void Client::whoami() const {
	std::cout << "You are: " << getFirstName() << " " << getSecondName() << std::endl;
	std::cout << "Your role is: " << getRole() << std::endl;
	std::cout << "You are " << getAge() << " years old." << std::endl;
	std::cout << "Your EGN is: " << getEgn() << std::endl;
	std::cout << "Your password is: " << getPassword() << std::endl;
}

void Client::exit() const {
	std::cout << getRole() << ": " << getFirstName() << " " << getSecondName() << " exited!" << std::endl;
}

void Client::writeToFile(std::ofstream& ofs) const {
	User::writeToFile(ofs);

	writeStringToFile(ofs,address);

	size_t count = checks.getSize();
	ofs.write((const char*)&count, sizeof(size_t));

	for (size_t i = 0; i < count; i++) {
		checks[i].writeToFile(ofs);
	}

	size_t countMessage = message.getSize();
	ofs.write((const char*)&countMessage, sizeof(size_t));

	for (size_t i = 0; i < countMessage; i++) {
		message[i].writeToFile(ofs);
	}
}

void Client::readFromFile(std::ifstream& ifs) {
	User::readFromFile(ifs);

	address = readStringFromFile(ifs);

	size_t checksCount=0;
	ifs.read((char*)&checksCount, sizeof(size_t));

	for (size_t i = 0; i < checksCount; i++) {
		Check checkToRead;
		checkToRead.readFromFile(ifs);
		checks.push_back(checkToRead);
	}

	size_t messageCount = 0;
	ifs.read((char*)&messageCount, sizeof(size_t));

	for (size_t i = 0; i < messageCount; i++) {
		Message messageToRead;
		messageToRead.readFromFile(ifs);
		message.push_back(messageToRead);
	}
}

Client::~Client() {
	size_t banksCount = banks.getSize();
	for (size_t i = 0; i < banksCount; i++) {
		banks[i] = nullptr;
	}
}
