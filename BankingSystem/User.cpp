#include "User.h"

bool User::validateAge(uint16_t age) const{
	if (age<Constants::MIN_AGE || age>Constants::MAX_AGE) {
		return false;
	}
	return true;
}

User::User(const MyString& name, const MyString& egn, size_t age, const MyString& role, const MyString& password):name(name),egn(egn),role(role),password(password){
	if (validateAge(age)) {
		this->age = age;
	}
	else {
		std::cout << "Incorrect age range.The current age will be 18." << std::endl;
		this->age = Constants::MIN_AGE;
	}
}

const MyString& User::getName() const {
	return name;
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