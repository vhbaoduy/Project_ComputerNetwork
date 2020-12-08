#pragma once
#include "Struct.h"
ref class RequestInforClass:public StructClass
{
public:
	String^ friendUsername;
	RequestInforClass()
	{
		friendUsername = nullptr;
	}
	virtual array<Byte>^ pack() override
	{
		List<Byte>^ byteData = gcnew List<Byte>();
		byteData->AddRange(BitConverter::GetBytes(int(StructClass::MessageType::RequestInfor)));

		//add Username info
		if (friendUsername != nullptr)
		{
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(friendUsername))); //Length of username
			byteData->AddRange(Encoding::UTF8->GetBytes(friendUsername)); //Username string
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));

		//Return
		return byteData->ToArray();
	}

	virtual StructClass^ unpack(array<Byte>^ buff) override
	{
		int offset = 4; //Skip messageType
		int usernameLength;

		usernameLength = BitConverter::ToInt32(buff, offset);
		offset += 4; //Update Offset
		if (usernameLength > 0)
			friendUsername = Encoding::UTF8->GetString(buff, offset, usernameLength);
		return this;
	}
};

