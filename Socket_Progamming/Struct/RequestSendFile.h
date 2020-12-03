#pragma once
#include "Struct.h"
ref class RequestSendFile : public StructClass
{
public:
	String^ userName;
	String^ fileName;
	int iFileSize;

	RequestSendFile() {
		userName = nullptr;
		fileName = nullptr;
		iFileSize = 0;
	}
	virtual array<Byte>^ pack() override {
		List<Byte>^ byteData = gcnew List<Byte>();
		byteData->AddRange(BitConverter::GetBytes(int(StructClass::MessageType::RequestSendFile)));

		//add Username info
		if (userName != nullptr)
		{
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(userName))); //Length of username
			byteData->AddRange(Encoding::UTF8->GetBytes(userName)); //Username string
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));


		//add FileName Info
		if (fileName != nullptr)
		{
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(fileName))); //Length of FileName
			byteData->AddRange(Encoding::UTF8->GetBytes(fileName)); //FileName string
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));

		//add FileSize info
		byteData->AddRange(BitConverter::GetBytes(iFileSize));

		//Return
		return byteData->ToArray();
	}
	virtual StructClass^ unpack(array<Byte>^ buff) override {

		int offset = 4; //Skip messageType
		int usernameLength, filenameLength;

		usernameLength = BitConverter::ToInt32(buff, offset);
		offset += 4; //Update Offset
		if (usernameLength > 0)
			userName = Encoding::UTF8->GetString(buff, offset, usernameLength);

		offset += usernameLength; //Update offset

		filenameLength = BitConverter::ToInt32(buff, offset);
		offset += 4; //Update offset
		if (filenameLength > 0)
			fileName = Encoding::UTF8->GetString(buff, offset, filenameLength);

		offset += filenameLength;
		iFileSize = BitConverter::ToInt32(buff, offset);

		return this;
	}
};

