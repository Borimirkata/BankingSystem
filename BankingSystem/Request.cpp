#include "Request.h"

Request::Request(const MyString& type, const MyString& firstName, const MyString& secondName, const MyString& egn, size_t age) :type(type), firstName(firstName), secondName(secondName), egn(egn) {
	if (age < MIN_AGE_ || age>MAX_AGE_) {
		throw std::exception("Incorrect age");
	}
	this->age = age;
}

const MyString& Request::getType() const {
	return type;
}

const MyString& Request::getFirstName() const {
	return firstName;
}

const MyString& Request::getSecondName() const {
	return secondName;
}

const MyString& Request::getEgn() const {
	return egn;
}

size_t Request::getAge() const {
	return age;
}