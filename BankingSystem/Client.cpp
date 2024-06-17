#include "Client.h"

int Client::getBankIndex(const MyString& bankName) const {
	size_t banksCount = banks.getSize();

	for (size_t i = 0; i < banksCount; i++) {
		if ((banks[i]->getBankName() == bankName)) {
			return i;
		}
	}
	return -1;
}

int Client::getCheckIndex(const MyString& code) const {
	size_t checksCount = checks.getSize();

	for (size_t i = 0; i < checksCount; i++) {
		if ((checks[i].getCode() == code)) {
			return i;
		}
	}
	return -1;
}

Client::Client(const MyString& firstName, const MyString& secondName, const MyString& egn, size_t age, const MyString& role, const MyString& password, const MyString& address) :User(firstName, secondName, egn, age, role, password) {
	this->address = address;
}

void Client::check_avl(const MyString& bankName, size_t accountNumber) const {
	int index = getBankIndex(bankName);
	if (index == -1) {
		throw std::exception("There is no bank with such name!");
	}
	Bank* currentBank = banks[index];
	std::cout << "Balance: " << currentBank->getAccountBalance(accountNumber) << " $" << std::endl;
}

void Client::open(const MyString& bankName) {

	Bank* currentB = BankingSystem::getBankByName(bankName);

	currentB->sendRequestToEmployee(Request(type1, this));
}

void Client::close(const MyString& bankName, size_t accountNumber) {
	int index = getBankIndex(bankName);
	if (index == -1) {
		throw std::exception("There is no bank with such name!");
	}
	Bank* currentB = banks[index];

	currentB->sendRequestToEmployee(Request(type2, this, accountNumber));
}

void Client::change(const MyString& newBankName, const MyString& currentBankName, size_t accountNumber) {
	int indexCurrent = getBankIndex(currentBankName);
	int indexNew = getBankIndex(newBankName);
	//right now the indexNew will always be -1,because the newBank is not added in the banks!!!
	if (indexCurrent == -1 || indexNew == -1) {
		throw std::exception("Incorrect bank names!");
	}
	Bank* currentB = banks[indexCurrent];
	Bank* newB = banks[indexNew];

	newB->sendRequestToEmployee(Request(type3, this,accountNumber,currentB->getBankName()));
}

void Client::redeem(const MyString& bankName, size_t accountNumber, const MyString& verificationCode) {
	int bankIndex = getBankIndex(bankName);

	if (bankIndex == -1) {
		throw std::exception("Incorrect bankName");
	}
	int checkIndex = getCheckIndex(verificationCode);

	if (checkIndex == -1) {
		throw std::exception("Invalid code");
	}

	Bank* currentBank = banks[bankIndex];
	Account* currentAccount = currentBank->getAccount(accountNumber);
	double currentBalance = currentAccount->getBalance();
	double sumCheck = checks[checkIndex].getSum();

	double newBalance = currentBalance + sumCheck;
	currentAccount->setBalance(newBalance);
}

void Client::list(const MyString& bankName) const {
	int index = getBankIndex(bankName);
	if (index == -1) {
		throw std::exception("bank name is incorrect!");
	}

	banks[index]->printAccounts();

}

void Client::messages() const {
	if (message.empty()) {
		std::cout << "No messages to show" << std::endl;
	}

	int count = message.getSize();
	for (int i = 0; i < count; i++) {
		std::cout << "[" << (i) << "] ";
		message[i].printMessage();
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

void Client::addBank(const MyString& bankName) {
	banks.push_back(BankingSystem::getBankByName(bankName));
	Bank* bank = getBank(bankName);
	bank->addClient(this);

}

void Client::addMessage(const Message& mess) {
	message.push_back(mess);
	int index = getBankIndex(mess.getBankName());

	if (isSubstring(mess.getContent(), "opened") && index==-1) {
		this->addBank(mess.getBankName());
	}
}

void Client::addCheck(const Check& check) {
	checks.push_back(check);
}

void Client::receiveCheck(const Check& check) {
	addCheck(check);
}

Bank* Client::getBank(const MyString& bankName) {
	int index = getBankIndex(bankName);

	if (index == -1) {
		throw std::exception("Incorrect bank name");
	}
	return banks[index];
}

Message* Client::getMessageAtIndex(size_t index) {
	return &message[index];
}

void Client::exit() const {
	std::cout << getRole() << ": " << getFirstName() << " " << getSecondName() << " exited!" << std::endl;
}

int main() {
	BankingSystem system;
	Client c1("Borimir", "Aleksiev", "0xxxxxxxx1", 19, "Client", "*", "Vidima");
	system.createBank("Fibank");
	system.createBank("DSK");
	c1.addBank("DSK");
	Employee e1("FirstPerson", "Hristov", "0xxxxxxxx2", 20, "Employee", "*#", "Fibank");
	Employee e2("SecondPerson", "Nenkov", "0xxxxxxxx3", 24, "Employee", "**", "DSK");
	ThirdPartyEmployee tp1("ThirdParty", "Employer", "0xxxxxxx4", 34, "ThirdPartyEmployee", "***");
	tp1.addBank("Fibank");
	tp1.addBank("DSK");
	c1.open("Fibank");
	e1.printTasks();
	e1.view(0);
	e1.approve(0);
	c1.messages();
	int accountNum = c1.getMessageAtIndex(0)->getAccNumber();
	c1.list("Fibank");
	c1.check_avl("Fibank", accountNum);
	c1.change("DSK", "Fibank", accountNum);
	e2.printTasks();
	e2.view(0);
	e2.approve(0);
	e2.validate(0);
	e2.printTasks();
	e2.approve(0);
	int accountNum2 = c1.getMessageAtIndex(1)->getAccNumber();
	tp1.send_check(150.00,"DSK", "agd", "0xxxxxxxx1");
	c1.messages();
	c1.check_avl("DSK", accountNum2);
	c1.redeem("DSK", accountNum2, "agd");
	c1.check_avl("DSK", accountNum2);
	

}

