#pragma once
#include "Struct.h"

ref class ChangePasswordClass :public StructClass
{
public:
	String^ userName;
	String^ oldPassword;
	String^ newPassword;
	String^ confirmPassword;
	bool isEncrypted;
	ChangePasswordClass() {
		userName = nullptr;
		oldPassword = nullptr;
		newPassword = nullptr;
		confirmPassword = nullptr;
		isEncrypted = false;
	}

	virtual array<Byte>^ pack() override {
		List<Byte>^ byteData = gcnew List<Byte>();
		byteData->AddRange(BitConverter::GetBytes(int(StructClass::MessageType::ChangePassword)));

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

		if (oldPassword != nullptr)
		{
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(oldPassword))); //Length of password
			byteData->AddRange(Encoding::UTF8->GetBytes(oldPassword)); //Password string
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));


		if (newPassword != nullptr)
		{
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(newPassword))); //Length of password
			byteData->AddRange(Encoding::UTF8->GetBytes(newPassword)); //Password string
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));

		if (confirmPassword != nullptr)
		{
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(confirmPassword))); //Length of password
			byteData->AddRange(Encoding::UTF8->GetBytes(confirmPassword)); //Password string
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));

		byteData->AddRange(BitConverter::GetBytes(isEncrypted));

		return byteData->ToArray();
	}


	virtual StructClass^ unpack(array<Byte>^ buffer) override {
		int offset = 4; //Skip messageType
		int usernameLength, oldPasswordLength,newPasswordLength,confirmPasswordLength;

		usernameLength = BitConverter::ToInt32(buffer, offset);
		offset += 4; //Update Offset
		if (usernameLength > 0)
			userName = Encoding::UTF8->GetString(buffer, offset, usernameLength);

		offset += usernameLength; //Update offset

		oldPasswordLength = BitConverter::ToInt32(buffer, offset);
		offset += 4; //Update offset
		if (oldPasswordLength > 0)
			oldPassword = Encoding::UTF8->GetString(buffer, offset, oldPasswordLength);
		offset += oldPasswordLength;

		newPasswordLength = BitConverter::ToInt32(buffer, offset);
		offset += 4;
		if (newPasswordLength > 0)
			newPassword = Encoding::UTF8->GetString(buffer, offset, newPasswordLength);

		offset += newPasswordLength;
		confirmPasswordLength = BitConverter::ToInt32(buffer, offset);
		offset += 4;
		if (confirmPasswordLength > 0)
			confirmPassword = Encoding::UTF8->GetString(buffer, offset, confirmPasswordLength);


		offset += confirmPasswordLength;
		isEncrypted = BitConverter::ToBoolean(buffer, offset);
		//if (isEncrypted)
		//	passWord = convertHexToString(passWord);
		return this;
	}
};

