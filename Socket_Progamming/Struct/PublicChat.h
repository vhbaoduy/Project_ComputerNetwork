#pragma once
#include "Struct.h"
ref class PublicChat:public StructClass
{
public:
	String^ message;
	PublicChat() {
		message = nullptr;
	}

	virtual array<Byte>^ pack() override {

		List<Byte>^ byteData = gcnew List<Byte>();
		byteData->AddRange(BitConverter::GetBytes(int(StructClass::MessageType::PublicChat)));

		//add Username info
		if (message != nullptr)
		{
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(message))); //Length of username
			byteData->AddRange(Encoding::UTF8->GetBytes(message)); //Username string
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));


		return byteData->ToArray();

	}


	virtual StructClass^ unpack(array<Byte>^ buffer) override {
		int offset = 4;
		int messageLength = BitConverter::ToInt32(buffer, offset);
		offset += 4;
		if (messageLength > 0)
			message = Encoding::UTF8->GetString(buffer, offset, messageLength);


		return this;


	}
};


