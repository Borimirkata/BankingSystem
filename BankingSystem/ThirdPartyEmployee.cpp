#include "ThirdPartyEmployee.h"

ThirdPartyEmployee::ThirdPartyEmployee(const MyString& firstName, const MyString& secondName, const MyString& egn, size_t age, const MyString& role, const MyString& password) :User(firstName,secondName,egn,age,role,password) {
	
}

bool ThirdPartyEmployee::validateCode(const MyString& code) const {
	int length = code.length();

	if (length != ThirdPartyData::SIZE) {
		throw std::exception("Code's length has to be 3");
	}

	//to do
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

int ThirdPartyEmployee::getClientIndex(const MyString& egn) const {
	size_t clientsCount = clients.getSize();

	for (size_t i = 0; i < clientsCount; i++) {
		if (clients[i]->getEgn() == egn) {
			return i;
		}
	}
	return -1;
}

void ThirdPartyEmployee::send_check(double sum, const MyString& bankName, const MyString& egn) {
	//to do
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