#include "Message.h"

Message::Message(const MyString& from, const MyString& content, const MyString& bankName) : from(from), content(content), bankName(bankName) {

}

void Message::setFrom(const MyString& from) {
	this->from = from;
}

void Message::setContent(const MyString& content) {
	this->content = content;
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

void Message::printMessage() const {
	std::cout << getContent() << "! Message from:" << getFrom() << std::endl;
}