#pragma once
#include "Struct.h"
ref class LogOutNotification:public StructClass
{

public:
	String^ userName;
	LogOutNotification() {
		this->userName = nullptr;
	}

	virtual array<Byte>^ pack() override{
		List<Byte>^ byteData = gcnew List<Byte>();
		byteData->AddRange(BitConverter::GetBytes(int(StructClass::MessageType::LogOutNotification)));

		//add Username info
		if (userName != nullptr)
		{
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(userName))); //Length of username
			byteData->AddRange(Encoding::UTF8->GetBytes(userName)); //Username string
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));

		return byteData->ToArray();
	}

	virtual StructClass^ unpack(array<Byte>^ buffer) override {
		int offset = 4;
		int userNameLength;

		userNameLength = BitConverter::ToInt32(buffer, offset);
		offset += 4;
		if (userNameLength > 0)
			userName = Encoding::UTF8->GetString(buffer,offset, userNameLength);

		return this;
	}
};

