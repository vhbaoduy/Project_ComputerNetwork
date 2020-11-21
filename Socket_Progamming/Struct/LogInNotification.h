#pragma once
#include "Struct.h"
ref class LogInNotification : public StructClass
{
public:
	String^ userName;

	LogInNotification() {
		userName = nullptr;
	}

	array<Byte>^ pack() override {
		List<Byte>^ byteData = gcnew List<Byte>();
		byteData->AddRange(BitConverter::GetBytes(int(StructClass::MessageType::LogInNotification)));

		if (userName != nullptr) {
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(userName)));
			byteData->AddRange(Encoding::UTF8->GetBytes(userName));
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));

		return byteData->ToArray();
	}

	StructClass^ unpack(array<Byte>^ buffer) override {
		int offset = 4;

		int userNameLength = BitConverter::ToInt32(buffer, offset);

		offset += 4;
		if (userNameLength > 0)
			userName = Encoding::UTF8->GetString(buffer, offset, userNameLength);


		return this;
	}
};

