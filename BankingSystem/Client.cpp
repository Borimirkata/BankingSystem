#include "Client.h"

int Client::getBankIndex(const MyString& bankName) const {
	int index = -1;
	size_t banksCount = banks.getSize();

	for (size_t i = 0; i < banksCount; i++) {
		if ((banks[i].getBankName() == bankName)) {
			return i;
		}
	}
	return -1;
}

Client::Client(const MyString& firstName, const MyString& secondName, const MyString& egn, size_t age, const MyString& role, const MyString& password, const MyString& address):User(firstName,secondName,egn,age,role,password){
	this->address = address;
}

void Client::check_avl(const MyString& bankName, size_t accountNumber) const {
	int index = getBankIndex(bankName);
	if (index == -1) {
		throw std::exception("There is no bank with such name!");
	}
	Bank currentBank = banks[index];
	std::cout << "Balance: " << currentBank.getAccountBalance(accountNumber) << " $" << std::endl;
}

void Client::open(const MyString& bankName) {
	int index = getBankIndex(bankName);
	if (index == -1) {
		throw std::exception("There is no bank with such name!");
	}
	Bank currentBank = banks[index];
	MyString string = "Open task";
	currentBank.pushTask(string);
}

void Client::close(const MyString& bankName,size_t accountNumber) {
	int index = getBankIndex(bankName);
	if (index == -1) {
		throw std::exception("There is no bank with such name!");
	}
	Bank currentBank = banks[index];
	//create a function that converts number into string and the oposite!
	MyString string = "Close task";
	currentBank.pushTask(string);
}

void Client::change(const MyString& newBankName, const MyString& currentBankName, size_t accountNumber) {
	int indexCurrent = getBankIndex(currentBankName);
	int indexNew = getBankIndex(newBankName);
	if (indexCurrent == -1 || indexNew == -1) {
		throw std::exception("Incorrect bank names!");
	}
	Bank currentBank = banks[indexCurrent];

	MyString string = "Change task";
	currentBank.pushTask(string);
}

void Client::list(const MyString& bankName) const {
	int index = getBankIndex(bankName);
	if (index == -1) {
		throw std::exception("bank name is incorrect!");
	}

	Bank currentBank = banks[index];
	currentBank.printAccounts();
}

void Client::messages() const {
	if (message.empty()) {
		std::cout << "No messages to show" << std::endl;
	}

	size_t messagesSize = message.getSize();
	for (size_t i = 0; i < messagesSize; i++) {
		std::cout << "[" << (i + 1) << "] " << message[i].getContent() <<"! Message from:"<<message[i].getFrom()<< std::endl;
	}
}

void Client::whoami() const {
	std::cout << "You are: " << getFirstName() << " " << getSecondName() << std::endl;
	std::cout << "Your role is: " << getRole() << std::endl;
	std::cout << "You are " << getAge() << " years old." << std::endl;
	std::cout << "Your EGN is: " << getEgn() << std::endl;
	std::cout << "Your password is: " << getPassword() << std::endl;
}

void Client::help() const {
	std::cout << "The commands that you can use are:" << std::endl;
	std::cout << "-check_avl [bank_name] [account_number] " << std::endl;
	std::cout << "-open [bank_name] " << std::endl;
	std::cout << "-close [bank_name] [account_number]  " << std::endl;
	std::cout << "-redeem [bank_name] [account_number] [verification_code]  " << std::endl;
	std::cout << "-change [new_bank_name] [current_bank_name] [account_number] " << std::endl;
	std::cout << "-list [bank_name] " << std::endl;
	std::cout << "-messages " << std::endl;
	std::cout << "-whoami " << std::endl;
	std::cout << "-exit " << std::endl;
}

void Client::pushBank(const Bank& bank) {
	banks.push_back(bank);
}

void Client::pushMessage(const Message& mess) {
	message.push_back(mess);
}

int main() {
	Client c1("Borimir", "Aleksiev", "*.............*", 19, "Client", "*","Vidima");
	Bank b("Fibank");
	c1.pushBank(b);
	c1.messages();
	c1.open("Fibank");
}

