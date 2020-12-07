#pragma once
#include "Struct.h"
ref class PrivateFile:public StructClass
{
public:

	String^ userName;
	String^ fileName;
	int iPackageNumber;
	int iTotalPackage;
	array<Byte>^ bData;
	bool isEncrypted;
	PrivateFile() {
		userName = nullptr;
		fileName = nullptr;
		iPackageNumber = 0;
		iTotalPackage = 0;
		bData = nullptr;
		isEncrypted = false;
	}
	virtual array<Byte>^ pack() override {
		List<Byte>^ byteData = gcnew List<Byte>();
		byteData->AddRange(BitConverter::GetBytes(int(StructClass::MessageType::PrivateFile)));

		//add Username info
		if (userName != nullptr)
		{
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(userName))); //Length of username
			byteData->AddRange(Encoding::UTF8->GetBytes(userName)); //Username string
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));


		//add Filename Info
		if (fileName != nullptr)
		{
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(fileName))); //Length of strFilename
			byteData->AddRange(Encoding::UTF8->GetBytes(fileName)); //strFilename string
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));

		//file package number and total package info
		byteData->AddRange(BitConverter::GetBytes(iPackageNumber));
		byteData->AddRange(BitConverter::GetBytes(iTotalPackage));

		//Add data info
		byteData->AddRange(BitConverter::GetBytes(bData->Length));
		byteData->AddRange(bData);
		//Return

		byteData->AddRange(BitConverter::GetBytes(isEncrypted));
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
		iPackageNumber = BitConverter::ToInt32(buff, offset);
		offset += 4;
		iTotalPackage = BitConverter::ToInt32(buff, offset);
		offset += 4;

		int dataSize = BitConverter::ToInt32(buff, offset);
		offset += 4;
		bData = gcnew array<Byte>(dataSize);
		if (dataSize > 0)
			System::Array::Copy(buff, offset, bData, 0, dataSize);

		offset += dataSize;
		isEncrypted = BitConverter::ToBoolean(buff, offset);
		return this;

	}
};

