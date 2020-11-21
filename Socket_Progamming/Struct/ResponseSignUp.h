#pragma once
#include "Struct.h"
ref class ResponseSignUp : public StructClass
{
public:
	bool isSuccessful;
	String^ errorMessage;

	ResponseSignUp() {
		isSuccessful = false;
		errorMessage = nullptr;
	}

	array<Byte>^ pack()override {
		List<Byte>^ byteData = gcnew List<Byte>();
		byteData->AddRange(BitConverter::GetBytes(int(StructClass::MessageType::ResponseLogin)));
		byteData->AddRange(BitConverter::GetBytes(isSuccessful));

		if (errorMessage != nullptr) {
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(errorMessage)));
			byteData->AddRange(Encoding::UTF8->GetBytes(errorMessage));
		}

		else
			byteData->AddRange(BitConverter::GetBytes(0));
		return byteData->ToArray();
	}

	StructClass^ unpack(array<Byte>^ buffer) override {
		int offset = 4;
		isSuccessful = BitConverter::ToBoolean(buffer, offset);

		offset += 4;
		int errorMessageLength = BitConverter::ToInt32(buffer, offset);

		offset += 4;

		if (errorMessageLength > 0)
			errorMessage = Encoding::UTF8->GetString(buffer, offset, errorMessageLength);



		return this;


	}
};

