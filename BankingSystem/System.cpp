#include "System.h"
#include "BankingSystem.h"

void run() {
	BankingSystem b;
	MyString command;

	while (true) {
		std::cin >> command;
		if (command == "signup") {
			MyString firstName, secondName, egn, age, role, password;
			std::cout << "Enter firstName,secondName,egn,age and role: ";
			std::cin >> firstName >> secondName >> egn >> age >> role;
			int ageInt = getNumFromStr(age);
			if (role == Roles::client) {
				MyString address;
				std::cout << "Enter address and password: ";
				std::cin >> address >> password;
				b.signup(firstName, secondName, egn, ageInt, role, password, "Empty", address);

			}
			else if (role == Roles::employee) {
				MyString bankName;
				std::cout << "Enter bankName and password: ";
				std::cin >> bankName >> password;
				b.signup(firstName, secondName, egn, ageInt, role, password, bankName, "Empty");
			}
			else if (role == Roles::thirdParty) {
				std::cout << "Enter password: ";
				std::cin >> password;
				b.signup(firstName, secondName, egn, ageInt, role, password, "Empty", "Empty");
			}
			else {
				throw std::exception("Wrong role");
			}
		}
		else if (command == "whoami") {
			b.userWhoami();
		}
		else if (command == "help") {
			b.userHelp();
		}
		else if (command == "exit") {
			b.exit();
		}
		else if (command == "quit") {
			b.quit();
			break;
		}
		else if (command == "login") {
			MyString firstName, secondName, password;
			std::cout << "Enter firstName,secondName and password: ";
			std::cin >> firstName >> secondName >> password;
			b.login(firstName, secondName, password);
		}
		else if (command == "create_bank") {
			std::cin.ignore();
			MyString bankName;
			std::cin >> bankName;
			b.createBank(bankName);
		}
		else if (command == "check_avl") {
			std::cin.ignore();
			MyString bankName, accountNumber;
			std::cin >> bankName >> accountNumber;
			int accNumberInt = getNumFromStr(accountNumber);
			b.clientCheckAvl(bankName, accNumberInt);
		}
		else if (command == "open") {
			MyString bankName;
			std::cin.ignore();
			std::cin >> bankName;
			b.clientOpen(bankName);
		}
		else if (command == "close") {
			MyString bankName, accountNumber;
			std::cin >> bankName >> accountNumber;
			int accountNumberInt = getNumFromStr(accountNumber);
			b.clientClose(bankName, accountNumberInt);
		}
		else if (command == "change") {
			MyString newBankName, currBankName, accountNumber;
			std::cin >> newBankName >> currBankName >> accountNumber;
			int accountNumberInt = getNumFromStr(accountNumber);
			b.clientChange(newBankName, currBankName, accountNumberInt);
		}
		else if (command == "redeem") {
			MyString bankName, accountNumber, code;
			std::cin >> bankName >> accountNumber >> code;
			int accountNumberInt = getNumFromStr(accountNumber);
			b.clientRedeem(bankName, accountNumberInt, code);
		}
		else if (command == "list") {
			MyString bankName;
			std::cin >> bankName;
			b.clientList(bankName);
		}
		else if (command == "messages") {
			b.clientMessages();
		}
		else if (command == "tasks") {
			b.employeePrintTasks();
		}
		else if (command == "view") {
			unsigned idx;
			std::cin >> idx;
			idx--;
			b.employeeView(idx);
		}
		else if (command == "approve") {
			unsigned idx;
			std::cin >> idx;
			idx--;
			b.employeeApprove(idx);
		}
		else if (command == "disapprove") {
			unsigned idx;
			std::cin >> idx;
			MyString content;
			std::cin >> content;
			idx--;
			b.employeeDisapprove(idx, content);
		}
		else if (command == "validate") {
			unsigned idx;
			std::cin >> idx;
			idx--;
			b.employeeValidate(idx);
		}
		else if (command == "send_check") {
			MyString bankName, code, egn;
			double sum;
			std::cin >> sum;
			std::cin.ignore();
			std::cin >> bankName>>code>>egn;
			b.thirdPartySendCheck(sum, bankName, code, egn);
		}
		else {
			throw std::exception("Invalid command");
		}
	}
}
