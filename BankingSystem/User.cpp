#include "User.h"

User::User(const MyString& firstName, const MyString& secondName, const MyString& egn, size_t age, const MyString& role, const MyString& password) :firstName(firstName), secondName(secondName), egn(egn), role(role), password(password) {
	if (age<UserData::MIN_AGE || age>UserData::MAX_AGE) {
		throw std::exception("Incorrect age");
	}
	this->age = age;
}

const MyString& User::getFirstName() const {
	return firstName;
}

const MyString& User::getSecondName() const {
	return secondName;
}

const MyString& User::getEgn() const {
	return egn;
}

size_t User::getAge() const {
	return age;
}

const MyString& User::getRole() const {
	return role;
}

const MyString& User::getPassword() const {
	return password;
}

void User::writeToFile(std::ofstream& ofs) const {
	writeStringToFile(ofs,firstName);
	writeStringToFile(ofs, secondName);
	writeStringToFile(ofs, egn);
	ofs.write((const char*)&age, sizeof(size_t));
	writeStringToFile(ofs, role);
	writeStringToFile(ofs, password);
}

void User::readFromFile(std::ifstream& ifs) {
	firstName = readStringFromFile(ifs);
	secondName = readStringFromFile(ifs);
	egn = readStringFromFile(ifs);
	ifs.read((char*)&age, sizeof(size_t));
	role = readStringFromFile(ifs);
	password = readStringFromFile(ifs);
}