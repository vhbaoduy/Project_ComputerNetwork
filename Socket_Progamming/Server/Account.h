#pragma once
#include "Library.h"

class Account
{
private:
	string userName, passWord;
public:
	Account() {
		userName = passWord = "";
	}
	void setUserName(const string& user) { userName = user; }
	void setPassWord(const string& pw) { passWord = pw; }
	string getUserName() { return userName; }
	string getPassWord() { return passWord; }
	void changePassWord(const string& npw){
		this->setPassWord(npw);
	}
	void registerAccount(const string& user, const string& pw) {
		this->setPassWord(pw);
		this->setUserName(user);
	}
};

