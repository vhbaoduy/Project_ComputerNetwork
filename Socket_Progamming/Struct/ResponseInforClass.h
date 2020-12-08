#pragma once
#include "Struct.h"
ref class ResponseInforClass:public StructClass
{
public:
	String^ friendUsername;
	String^ birthDate;
	ResponseInforClass()
	{
		birthDate = nullptr;
	}
	virtual array<Byte>^ pack() override
	{
		List<Byte>^ byteData = gcnew List<Byte>();
		byteData->AddRange(BitConverter::GetBytes(int(StructClass::MessageType::ResponseInfor)));

		//add Username info
		if (friendUsername != nullptr)
		{
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(friendUsername))); //Length of username
			byteData->AddRange(Encoding::UTF8->GetBytes(friendUsername)); //Username string
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));

		//add birthdate info
		if (birthDate != nullptr)
		{
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(birthDate))); //Length of username
			byteData->AddRange(Encoding::UTF8->GetBytes(birthDate)); //Username string
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));

		//Return
		return byteData->ToArray();
	}

	virtual StructClass^ unpack(array<Byte>^ buff) override
	{
		int offset = 4; //Skip messageType
		int friendusernameLength, birthdateLength;

		friendusernameLength = BitConverter::ToInt32(buff, offset);
		offset += 4; //Update Offset
		if (friendusernameLength > 0)
			friendUsername = Encoding::UTF8->GetString(buff, offset, friendusernameLength);

		offset += friendusernameLength; //Update offset

		birthdateLength = BitConverter::ToInt32(buff, offset);
		offset += 4; //Update offset
		if (birthdateLength > 0)
			birthDate = Encoding::UTF8->GetString(buff, offset, birthdateLength);

		return this;
	}
};

