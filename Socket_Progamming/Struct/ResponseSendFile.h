#pragma once
#include "Struct.h"
ref class ResponseSendFile : public StructClass
{
public:
	String^ userName;
	bool isAccept;

	ResponseSendFile() {
		userName = nullptr;
		isAccept = false;
	}
	virtual array<Byte>^ pack() override {
		List<Byte>^ byteData = gcnew List<Byte>();
		byteData->AddRange(BitConverter::GetBytes(int(StructClass::MessageType::ResponseSendFile)));

		//add Username info
		if (userName != nullptr)
		{
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(userName))); //Length of username
			byteData->AddRange(Encoding::UTF8->GetBytes(userName)); //Username string
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));


		//add IsAccept Info
		byteData->AddRange(BitConverter::GetBytes(isAccept));

		//Return
		return byteData->ToArray();
	}
	virtual StructClass^ unpack(array<Byte>^ buff) override {
		int offset = 4; //Skip messageType
		int usernameLength;

		usernameLength = BitConverter::ToInt32(buff, offset);
		offset += 4; //Update Offset
		if (usernameLength > 0)
			userName = Encoding::UTF8->GetString(buff, offset, usernameLength);

		offset += usernameLength; //Update offset
		isAccept = BitConverter::ToBoolean(buff, offset);

		return this;

	}
};

