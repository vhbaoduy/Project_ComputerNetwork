#pragma once
#include "Struct.h"
ref class SignUpClass:public StructClass
{
public:
	String^ userName;
	String^ passWord;

	SignUpClass() {
		userName = nullptr;
		passWord = nullptr;
	}

	virtual array<Byte>^ pack() override {
		List<Byte>^ byteData = gcnew List<Byte>();
		byteData->AddRange(BitConverter::GetBytes(int(StructClass::MessageType::SignUp)));

		//add Username info
		if (userName != nullptr)
		{
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(userName))); //Length of username
			byteData->AddRange(Encoding::UTF8->GetBytes(userName)); //Username string
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));

		//add Password Info
		if (passWord != nullptr)
		{
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(passWord))); //Length of password
			byteData->AddRange(Encoding::UTF8->GetBytes(passWord)); //Password string
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));

		return byteData->ToArray();
	}


	virtual StructClass^ unpack(array<Byte>^ buffer) override {
		int offset = 4; //Skip messageType
		int usernameLength, passwordLength;

		usernameLength = BitConverter::ToInt32(buffer, offset);
		offset += 4; //Update Offset
		if (usernameLength > 0)
			userName = Encoding::UTF8->GetString(buffer, offset, usernameLength);

		offset += usernameLength; //Update offset

		passwordLength = BitConverter::ToInt32(buffer, offset);
		offset += 4; //Update offset
		if (passwordLength > 0)
			passWord = Encoding::UTF8->GetString(buffer, offset, passwordLength);

		return this;
	}

};

