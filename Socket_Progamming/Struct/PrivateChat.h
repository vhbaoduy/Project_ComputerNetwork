#pragma once
#include "Struct.h"
ref class PrivateChat:public StructClass
{
public:
	String^ userNameReceiver;
	String^ message;

	PrivateChat() {
		userNameReceiver = nullptr;
		message = nullptr;
	}
	virtual array<Byte>^ pack() override {
		List<Byte>^ byteData = gcnew List<Byte>();
		byteData->AddRange(BitConverter::GetBytes(int(StructClass::MessageType::PrivateChat)));

		//add Username info
		if (userNameReceiver != nullptr)
		{
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(userNameReceiver))); //Length of username
			byteData->AddRange(Encoding::UTF8->GetBytes(userNameReceiver)); //Username string
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));


		//add Message Info
		if (message != nullptr)
		{
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(message))); //Length of message
			byteData->AddRange(Encoding::UTF8->GetBytes(message)); //message string
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));

		//Return
		return byteData->ToArray();
	}
	virtual StructClass^ unpack(array<Byte>^ buff) override {
		int offset = 4; //Skip messageType
		int userNameLength, messageLength;

		userNameLength = BitConverter::ToInt32(buff, offset);
		offset += 4; //Update Offset
		if (userNameLength > 0)
			userNameReceiver = Encoding::UTF8->GetString(buff, offset, userNameLength);

		offset += userNameLength; //Update offset

		messageLength = BitConverter::ToInt32(buff, offset);
		offset += 4; //Update offset
		if (messageLength > 0)
			message = Encoding::UTF8->GetString(buff, offset, messageLength);

		return this;
	}
};

