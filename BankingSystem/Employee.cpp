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
		bank->sendAnswerToClient(Message(this->getFirstName(), "You opened an account in ", bank->getBankName()), req->getClient());

		srand(time(NULL));
		unsigned id = rand()+1;//the plus 1 is added so that the accountNumber has to be a positive integer
		bank->addAccount(id,START_BALANCE,req->getClient());
	}
	else if (req->getType() == type2) {
		bank->sendAnswerToClient(Message(this->getFirstName(), "You closed an account in", bank->getBankName()), req->getClient());

		bank->deleteAccount(req->getAccountNum(), req->getClient());
	}
	else if (req->getType() == type3) {
		//to do
	}
}

void Employee::disapprove(size_t idx, const MyString& message) {
	Request* req = bank->getRequestByIndex(idx);

	bank->sendAnswerToClient(Message(this->getFirstName(), message, bank->getBankName()), req->getClient());
	this->tasks.erase(idx);
}

void Employee::view(size_t index) const{
	Request* req = bank->getRequestByIndex(index);

	std::cout << req->getType() << " request from:" << std::endl;
	std::cout << "Name: " << req->getFirstName() << " " << req->getSecondName() << std::endl;
	std::cout << "EGN: " << req->getEgn() << std::endl;
	std::cout << "Age: " << req->getAge() << std::endl;
}

void Employee::validate(size_t index) {
	//to do
}

MyVector<Request*> Employee::getTasks() {
	return tasks;
}

void Employee::printTasks() const {
	if (tasks.empty()) {
		std::cout << "No tasks to print!";
	}
	int count = tasks.getSize();

	for (int i = 0; i < count; i++) {
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