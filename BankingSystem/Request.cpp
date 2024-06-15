#include "Request.h"

Request::Request(const MyString& type, Client* client) {
	this->type = type;
	this->client = client;
	this->accountNum = DEF_VALUE;
}

Request::Request(const MyString& type, Client* client, int accountNum) {
	this->type = type;
	this->client = client;
	this->accountNum = accountNum;
}

const MyString& Request::getType() const {
	return type;
}

const MyString& Request::getFirstName() const {
	return client->getFirstName();
}

const MyString& Request::getSecondName() const {
	return client->getSecondName();
}

const MyString& Request::getEgn() const {
	return client->getEgn();
}

size_t Request::getAge() const {
	return client->getAge();
}

void Request::printRequest() const {
	if (getType() == type1) {
		std::cout <<getType()<<" - "<< getFirstName() << " " << getSecondName() << "wants to create an account!" << std::endl;
	}
	else if (getType() == type2) {
		std::cout <<getType()<<" - "<< getFirstName() << " " << getSecondName() << "wants to close an account!" << std::endl;
	}
	else if (getType() == type3) {
		//to do
	}
}

Client* Request::getClient() const {
	return client;
}

int Request::getAccountNum() const {
	return accountNum;
}