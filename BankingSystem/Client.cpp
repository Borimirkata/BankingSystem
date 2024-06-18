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

Client::Client(const MyString& firstName, const MyString& secondName, const MyString& egn, size_t age, const MyString& role, const MyString& password, const MyString& address) :User(firstName, secondName, egn, age, role, password) {
	this->address = address;
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

	currentB->sendRequestToEmployee(Request(type1, this));
}

void Client::close(const MyString& bankName, size_t accountNumber) {
	int index = getBankIndex(bankName);
	if (index == -1) {
		throw std::exception("There is no bank with such name!");
	}
	Bank* currentB = banks[index];

	currentB->sendRequestToEmployee(Request(type2, this, accountNumber));
}

void Client::change(const MyString& newBankName, const MyString& currentBankName, size_t accountNumber) {
	int indexCurrent = getBankIndex(currentBankName);
	int indexNew = getBankIndex(newBankName);

	if (indexCurrent == -1 || indexNew == -1) {
		throw std::exception("Incorrect bank names!");
	}
	Bank* currentB = banks[indexCurrent];
	Bank* newB = banks[indexNew];

	newB->sendRequestToEmployee(Request(type3, this, accountNumber, currentB->getBankName()));
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

	int count = message.getSize();
	for (int i = 0; i < count; i++) {
		std::cout << "[" << (i+1) << "] ";
		message[i].printMessage();
	}
}

void Client::whoami() const {
	std::cout << "You are: " << getFirstName() << " " << getSecondName() << std::endl;
	std::cout << "Your role is: " << getRole() << std::endl;
	std::cout << "You are " << getAge() << " years old." << std::endl;
	std::cout << "Your EGN is: " << getEgn() << std::endl;
	std::cout << "Your password is: " << getPassword() << std::endl;
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

void Client::addBank(Bank* bank) {
	banks.push_back(bank);
	bank->addClient(this);

}

void Client::addMessage(const Message& mess) {
	message.push_back(mess);
}

void Client::addCheck(const Check& check) {
	checks.push_back(check);
}

void Client::receiveCheck(const Check& check) {
	addCheck(check);
}

Bank* Client::getBank(const MyString& bankName) {
	int index = getBankIndex(bankName);

	if (index == -1) {
		throw std::exception("Incorrect bank name");
	}
	return banks[index];
}

Message* Client::getMessageAtIndex(size_t index) {
	return &message[index];
}

void Client::exit() const {
	std::cout << getRole() << ": " << getFirstName() << " " << getSecondName() << " exited!" << std::endl;
}

