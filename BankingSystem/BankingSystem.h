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


	static void create_bank(const MyString& bankName);

	static Bank* get_bank_by_name(const MyString& bankName);



};
