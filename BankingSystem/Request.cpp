#include "Request.h"

Request::Request(const MyString& type, Client* client) {
	this->type = type;
	this->client = client;
	this->accountNum = ClientData::DEF_VALUE;
}

Request::Request(const MyString& type, Client* client, int accountNum) {
	this->type = type;
	this->client = client;
	this->accountNum = accountNum;
}

Request::Request(const MyString& type, Client* client, int accountNum, const MyString& nameBank) {
	this->type = type;
	this->client = client;
	this->accountNum = accountNum;
	this->nameBank = nameBank;
}

Request::Request(const MyString& type, Client* client, int accountNum, const MyString& nameBank,double money) {
	this->type = type;
	this->client = client;
	this->accountNum = accountNum;
	this->nameBank = nameBank;
	this->money = money;
}

const MyString& Request::getType() const {
	return type;
}

void Request::setType(const MyString& type) {
	this->type = type;
}

const MyString& Request::getNameOfBank() const {
	return nameBank;
}

void Request::printRequest() const {
	if (getType() == type1) {
		std::cout <<getType()<<" - "<< client->getFirstName() << " " << client->getSecondName() << "wants to create an account!" << std::endl;
	}
	else if (getType() == type2) {
		std::cout <<getType()<<" - "<< client->getFirstName() << " " << client->getSecondName() << "wants to close an account with id:"<<getAccountNum() << std::endl;
	}
	else if (getType() == type3 || isSubstring(getType(),approvedChange)) {
		std::cout << getType() << " - " << client->getFirstName() << " " << client->getSecondName() << "wants to join "<<getNameOfBank()<<std::endl;
	}
	else if (isSubstring(getType(), askedChange)) {
		std::cout <<getType()<<" - "<< getNameOfBank() << " asks if " << client->getFirstName() << " is a real user!" << std::endl;
	}
}

Client* Request::getClient() const {
	return client;
}

int Request::getAccountNum() const {
	return accountNum;
}

double Request::getMoney() const {
	return money;
}

Request::~Request() {
	client = nullptr;
}