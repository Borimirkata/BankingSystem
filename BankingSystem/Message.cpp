#include "Message.h"

Message::Message(const MyString& from, const MyString& content, const MyString& bankName) : from(from), content(content), bankName(bankName) {
	this->accNumber = MessageData::VALUE;
}

Message::Message(const MyString& from, const MyString& content, const MyString& bankName,const MyString& code) : from(from), content(content), bankName(bankName),code(code) {
	this->accNumber = MessageData::VALUE;
}

Message::Message(const MyString& from, const MyString& content, const MyString& bankName, int number) :from(from), content(content), bankName(bankName) {
	this->accNumber = number;
}

const MyString& Message::getFrom() const {
	return from;
}

const MyString& Message::getContent() const {
	return content;
}

const MyString& Message::getBankName() const {
	return bankName;
}

const MyString& Message::getCode() const {
	return code;
}

int Message::getAccNumber() const {
	return accNumber;
}

void Message::printMessage() const {
	if (isSubstring(getContent(), "opened")) {
		std::cout << getContent() << getBankName() << "! Message from: " << getFrom() << std::endl;
		std::cout << "Your account id is: " << getAccNumber() << std::endl;
	}
	else if (isSubstring(getContent(), "closed")) {
		std::cout << "You closed an account in: " << getBankName() << std::endl;
	}
	else if (isSubstring(getContent(), "check")) {
		std::cout << getContent() <<" "<<getFrom() << "! Your verification code is: " << getCode() << std::endl;
	}
	else if (isSubstring(getContent(), "Reason")) {
		std::cout << "Your request has been disapproved from " << getFrom() << "." << getContent() << std::endl;
	}
	else if (isSubstring(getContent(), "changed")) {
		std::cout << "You changed your account to " << getBankName() << ". New account id is:" << getAccNumber() << std::endl;
	}
}

void Message::writeToFile(std::ofstream& ofs) const {
	writeStringToFile(ofs, from);
	writeStringToFile(ofs, content);
	writeStringToFile(ofs, bankName);
	writeStringToFile(ofs, code);
	ofs.write((const char*)&accNumber, sizeof(int));
}

void Message::readFromFile(std::ifstream& ifs) {
	from = readStringFromFile(ifs);
	content = readStringFromFile(ifs);
	bankName = readStringFromFile(ifs);
	code = readStringFromFile(ifs);
	ifs.read((char*)&accNumber, sizeof(int));
}