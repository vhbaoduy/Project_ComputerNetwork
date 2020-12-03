#pragma once
#include "Struct.h"
ref class UserStatusClass : public StructClass
{
public:
	array<String^>^ listUser;
	UserStatusClass() {
		listUser = nullptr;
	}

	virtual array<Byte>^ pack() override {
		List<Byte>^ byteData = gcnew List<Byte>();
		byteData->AddRange(BitConverter::GetBytes(int(StructClass::MessageType::UserStatus)));


		String^ message = "";
		if (listUser != nullptr) {
			for (int i = 0; i < listUser->Length - 1; ++i)
				message += listUser[i] + ",";
			if (listUser->Length > 0)
				message += listUser[listUser->Length - 1];
		}
		
		if (message != "") {
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(message))); //Length of strListOnlineUsers
			byteData->AddRange(Encoding::UTF8->GetBytes(message));
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));

		return byteData->ToArray();
	}

	virtual StructClass^ unpack(array<Byte>^ buffer) override {
		int offset = 4;
		int length = BitConverter::ToInt32(buffer, offset);
		offset += 4;
		String^ message = "";

		if (length > 0) {
			message = Encoding::UTF8->GetString(buffer, offset, length);
			array<wchar_t>^ delimiter = gcnew array<wchar_t>(1);
			delimiter[0] = ',';
			listUser = message->Split(delimiter);


		}

		return this;
	}
};

