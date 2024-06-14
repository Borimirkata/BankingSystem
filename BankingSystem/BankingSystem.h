#pragma once

#pragma once

# include "MyString.h"
# include "MyVector.hpp"


class Bank;
class Client;

class BankingSystem {
private:
	static MyVector<Bank> banks;
	//MyVector<Client> clients;
public:


	static void createBank(const MyString& bankName);

	static Bank* getBankByName(const MyString& bankName);

};
