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