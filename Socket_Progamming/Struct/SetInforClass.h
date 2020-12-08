#pragma once
#include "Struct.h"
ref class SetInforClass:public StructClass
{
public:
	String^ userName;
	String^ birthDate;
	SetInforClass()
	{
		userName = nullptr;
		birthDate = nullptr;
	}
	virtual array<Byte>^ pack() override
	{
		List<Byte>^ byteData = gcnew List<Byte>();
		byteData->AddRange(BitConverter::GetBytes(int(StructClass::MessageType::SetInfor)));
		//add Username info
		if (userName != nullptr)
		{
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(userName))); //Length of username
			byteData->AddRange(Encoding::UTF8->GetBytes(userName)); //Username string
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));
		//add full name info
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
		int usernameLength, birthDateLength;

		usernameLength = BitConverter::ToInt32(buff, offset);
		offset += 4; //Update Offset
		if (usernameLength > 0)
			userName = Encoding::UTF8->GetString(buff, offset, usernameLength);

		offset += usernameLength; //Update offset
		birthDateLength = BitConverter::ToInt32(buff, offset);
		offset += 4; //Update Offset
		if (birthDateLength > 0)
			birthDate = Encoding::UTF8->GetString(buff, offset, birthDateLength);
		return this;
	}
};

