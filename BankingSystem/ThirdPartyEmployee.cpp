#include "ThirdPartyEmployee.h"

ThirdPartyEmployee::ThirdPartyEmployee(const MyString& firstName, const MyString& secondName, const MyString& egn, size_t age, const MyString& role, const MyString& password) :User(firstName,secondName,egn,age,role,password) {
	
}

int ThirdPartyEmployee::getBankIndex(const MyString& bankName) const {
	size_t banksCount = banks.getSize();

	for (size_t i = 0; i < banksCount; i++) {
		if ((banks[i]->getBankName() == bankName)) {
			return i;
		}
	}
	return -1;
}

Client* ThirdPartyEmployee::getClient(const MyString& bankName, const MyString& egn) const {
	int index = getBankIndex(bankName);
	Bank* currBank = banks[index];
	Client* currClient = currBank->getClient(egn);
	return currClient;
}

bool ThirdPartyEmployee::validateCode(const MyString& code) const {
	size_t length = code.length();

	if (length != ThirdPartyData::SIZE) {
		throw std::exception("Code's length has to be 3");
	}
	
	for (size_t i = 0; i < length; i++) {
		if ((!isDigit(code[i])) && (!isLowerCase(code[i])) && (!isUpperCase(code[i]))) {
			return false;
		}
	}
	return true;
}

void ThirdPartyEmployee::addBank(Bank* bank) {
	banks.push_back(bank);
}

void ThirdPartyEmployee::send_check(double sum, const MyString& bankName,const MyString& code, const MyString& egn) {
	if (sum <= 0) {
		throw std::exception("Invalid sum");
	}

	Client* currentClient = getClient(bankName, egn);

	int bankIndex = getBankIndex(bankName);

	if (bankIndex == -1) {
		throw std::exception("There is no bank with that name");
	}

	if (!validateCode(code)) {
		throw std::exception("Invalid code");
	}
	Bank* currentBank = banks[bankIndex];
	currentClient->addMessage(Message(this->getFirstName(), "You have a check assigned by", currentBank->getBankName(),code));
	currentClient->receiveCheck(Check(code, sum));

}

void ThirdPartyEmployee::help() const {
	std::cout << "The commands that you can use are:" << std::endl;
	std::cout << "-send_check" << std::endl;
	std::cout << "-whoami" << std::endl;
	std::cout << "-exit" << std::endl;
}

void ThirdPartyEmployee::whoami() const {
	std::cout << "You are: " << getFirstName() << " " << getSecondName() << std::endl;
	std::cout << "Your role is: " << getRole() << std::endl;
	std::cout << "You are " << getAge() << " years old." << std::endl;
	std::cout << "Your EGN is: " << getEgn() << std::endl;
	std::cout << "Your password is: " << getPassword() << std::endl;
}

void ThirdPartyEmployee::exit() const {
	std::cout << getRole() << ": " << getFirstName() << " " << getSecondName() << " exited!" << std::endl;
}

void ThirdPartyEmployee::writeToFile(std::ofstream& ofs) const {
	User::writeToFile(ofs);

}

void ThirdPartyEmployee::readFromFile(std::ifstream& ifs) {
	User::readFromFile(ifs);
}

ThirdPartyEmployee::~ThirdPartyEmployee() {
	size_t banksCount = banks.getSize();
	for (size_t i = 0; i < banksCount; i++) {
		banks[i] = nullptr;
	}
}