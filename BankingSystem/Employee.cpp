#include "Employee.h"
#include <time.h>

Employee::Employee(const MyString& firstName, const MyString& secondName, const MyString& egn, size_t age, const MyString& role, const MyString& password, const MyString& bankName) : User(firstName, secondName, egn, age, role, password)
{

	bank = BankingSystem::getBankByName(bankName);
	bank->getEmployees().push_back(this);
}

void Employee::addTask(Request* request)
{
	tasks.push_back(request);
}

void Employee::approve(size_t idx)
{
	Request* req = bank->getRequestByIndex(idx);

	if (req->getType() == type1) {
		srand(time(NULL));
		unsigned id = rand();
		bank->sendAnswerToClient(Message(this->getFirstName(), "You opened an account in ", bank->getBankName(),id), req->getClient());

		bank->addAccount(id, START_BALANCE, req->getClient());

		this->tasks.erase(idx);
	}
	else if (req->getType() == type2) {
		bank->sendAnswerToClient(Message(this->getFirstName(), "You closed an account in", bank->getBankName()), req->getClient());

		bank->deleteAccount(req->getAccountNum(), req->getClient());

		this->tasks.erase(idx);
	}
	else if (req->getType() == type3) {
		std::cout << "Cannot proceed - please make sure " << req->getClient()->getFirstName() << " is real user by asking the bank!" << std::endl;
		std::cout << "Validate the user!" << std::endl;
	}
	else if (req->getType() == (type3 + approvedChange)) {
		srand(time(NULL));
		unsigned id = rand();

		bank->sendAnswerToClient(Message(this->getFirstName(), "You changed your account to ", bank->getBankName(), id), req->getClient());

		bank->addAccount(id, req->getMoney(), req->getClient());

		this->tasks.erase(idx);
	}
}

void Employee::disapprove(size_t idx, const MyString& message) {
	Request* req = bank->getRequestByIndex(idx);

	bank->sendAnswerToClient(Message(this->getFirstName(), ("Reason: "+message), bank->getBankName()), req->getClient());
	this->tasks.erase(idx);
}

void Employee::view(size_t index) const{
	Request* req = bank->getRequestByIndex(index);
	Client* client = req->getClient();

	std::cout << req->getType() << " request from:" << std::endl;
	std::cout << "Name: " << client->getFirstName() << " " << client->getSecondName() << std::endl;
	std::cout << "EGN: " << client->getEgn() << std::endl;
	std::cout << "Age: " << client->getAge() << std::endl;
}

void Employee::validate(size_t index) {
	Request* req = bank->getRequestByIndex(index);
	if (req->getType() != type3) {
		throw std::exception("Can only validate Change tasks!");
	}

	Client* client = req->getClient();

	const MyString& name = req->getNameOfBank();
	Bank* currBank = client->getBank(name);

	bool validation = bank->checkClient(client);
	if (validation) {
		tasks[index]->setType(type3 + approvedChange);
		tasks[index]->setMoney(currBank->getAccountBalance(req->getAccountNum()));

		currBank->deleteAccount(req->getAccountNum(), req->getClient());
	}
	else {
		currBank->sendAnswerToClient(Message(getFirstName(), "Sorry but the client is not valid", currBank->getBankName()),req->getClient());
		tasks.erase(index);
	}
}

MyVector<Request*> Employee::getTasks() {
	return tasks;
}

void Employee::printTasks() const {
	if (tasks.empty()) {
		std::cout << "No tasks to print!";
	}
	size_t count = tasks.getSize();

	for (size_t i = 0; i < count; i++) {
		std::cout << "[" << i << "] ";
		tasks[i]->printRequest();
	}
}

void Employee::help() const {
	std::cout << "The commands that you can use are:" << std::endl;
	std::cout << "-tasks " << std::endl;
	std::cout << "-view [task_index] " << std::endl;
	std::cout << "-approve [task_index] " << std::endl;
	std::cout << "-disapprove [task_index] [message] " << std::endl;
	std::cout << "-validate [task_index]" << std::endl;
	std::cout << "-whoami " << std::endl;
	std::cout << "-exit " << std::endl;
}

void Employee::whoami() const {
	std::cout << "You are: " << getFirstName() << " " << getSecondName() << std::endl;
	std::cout << "Your role is: " << getRole() << std::endl;
	std::cout << "You work for: " << this->bankAssociated << std::endl;
	std::cout << "You are " << getAge() << " years old." << std::endl;
	std::cout << "Your EGN is: " << getEgn() << std::endl;
	std::cout << "Your password is: " << getPassword() << std::endl;
}

Employee::~Employee() {
	bank = nullptr;
}

void Employee::exit() const {
	std::cout << getRole() << ": " << getFirstName() << " " << getSecondName() << " exited!" << std::endl;
}