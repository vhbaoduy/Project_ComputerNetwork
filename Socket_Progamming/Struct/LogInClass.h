#pragma once
#include "Struct.h"

ref class LogInClass : public StructClass
{
public:
	String^ userName;
	String^ passWord;
	bool isEncrypted;

	LogInClass() {
		userName = nullptr;
		passWord = nullptr;
		isEncrypted = false;
	}

	virtual array<Byte>^ pack() override {
		List<Byte>^ byteData = gcnew List<Byte>();
		byteData->AddRange(BitConverter::GetBytes(int(StructClass::MessageType::LogIn)));

		//add Username info
		if (userName != nullptr)
		{
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(userName))); //Length of username
			byteData->AddRange(Encoding::UTF8->GetBytes(userName)); //Username string
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));

		//add Password Info
		// encrypted
		//if (isEncrypted) {
		//	passWord = convertStringToHex(passWord);
		//}

		if (passWord != nullptr)
		{
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(passWord))); //Length of password
			byteData->AddRange(Encoding::UTF8->GetBytes(passWord)); //Password string
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));

		byteData->AddRange(BitConverter::GetBytes(isEncrypted));

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
		offset += passwordLength;
		isEncrypted = BitConverter::ToBoolean(buffer,offset);
		//if (isEncrypted)
		//	passWord = convertHexToString(passWord);
		return this;
	}


};

