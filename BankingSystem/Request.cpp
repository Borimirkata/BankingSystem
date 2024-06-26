#include "Request.h"

Request::Request(const MyString& type, Client* client) {
	this->type = type;
	this->client = client;
	this->accountNum = RequestData::DEF_VALUE;
	this->money = RequestData::DEF_VALUE;
}

Request::Request(const MyString& type, Client* client, int accountNum) {
	this->type = type;
	this->client = client;
	this->accountNum = accountNum;
	this->money = RequestData::DEF_VALUE;
}

Request::Request(const MyString& type, Client* client, int accountNum, const MyString& nameBank) {
	this->type = type;
	this->client = client;
	this->accountNum = accountNum;
	this->nameBank = nameBank;
	this->money = RequestData::DEF_VALUE;
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

int Request::getAccountNum() const {
	return accountNum;
}

double Request::getMoney() const {
	return money;
}

void Request::setMoney(double money) {
	this->money = money;
}

void Request::printRequest() const {
	if (getType() == RequestData::type1) {
		std::cout <<getType()<<" - "<< client->getFirstName() << " " << client->getSecondName() << " wants to create an account!" << std::endl;
	}
	else if (getType() == RequestData::type2) {
		std::cout <<getType()<<" - "<< client->getFirstName() << " " << client->getSecondName() << " wants to close an account with id:"<<getAccountNum() << std::endl;
	}
	else if (getType() == RequestData::type3 || isSubstring(getType(),RequestData::approvedChange)) {
		std::cout << getType() << " - " << client->getFirstName() << " " << client->getSecondName() << " wants to join your bank!"<<std::endl;
	}
}

Client* Request::getClient() const {
	return client;
}

void Request::writeToFile(std::ofstream& ofs) const {
	writeStringToFile(ofs, type);
	writeStringToFile(ofs, nameBank);
	ofs.write((const char*)&accountNum, sizeof(int));
	ofs.write((const char*)&money, sizeof(double));
}

void Request::readFromFile(std::ifstream& ifs) {
	type = readStringFromFile(ifs);
	nameBank = readStringFromFile(ifs);
	ifs.read((char*)&accountNum, sizeof(int));
	ifs.read((char*)&money, sizeof(double));
}

Request::~Request() {
	client = nullptr;
}