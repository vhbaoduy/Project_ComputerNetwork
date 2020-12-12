#pragma once
#include "Struct.h"
ref class DownloadPublicFileClass:public StructClass
{
public:

	String^ fileName;
	int iFileSize;
	int iPackageNumber;
	int iTotalPackage;
	array<Byte>^ bData;
	//bool isEncrypted;
	DownloadPublicFileClass() {
		fileName = nullptr;
		iFileSize = 0;
		iPackageNumber = 0;
		iTotalPackage = 0;
		bData = nullptr;
		//isEncrypted = false;
	}
	virtual array<Byte>^ pack() override {
		List<Byte>^ byteData = gcnew List<Byte>();
		byteData->AddRange(BitConverter::GetBytes(int(StructClass::MessageType::DownloadPublicFile)));

		//add Username info

		//add Filename Info
		if (fileName != nullptr)
		{
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(fileName))); //Length of strFilename
			byteData->AddRange(Encoding::UTF8->GetBytes(fileName)); //strFilename string
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));

		byteData->AddRange(BitConverter::GetBytes(iFileSize));
		//file package number and total package info
		byteData->AddRange(BitConverter::GetBytes(iPackageNumber));
		byteData->AddRange(BitConverter::GetBytes(iTotalPackage));

		//Add data info
		byteData->AddRange(BitConverter::GetBytes(bData->Length));
		byteData->AddRange(bData);
		//Return

		//byteData->AddRange(BitConverter::GetBytes(isEncrypted));
		return byteData->ToArray();

	}
	virtual StructClass^ unpack(array<Byte>^ buff) override {
		int offset = 4; //Skip messageType
		int filenameLength;

		filenameLength = BitConverter::ToInt32(buff, offset);
		offset += 4; //Update offset
		if (filenameLength > 0)
			fileName = Encoding::UTF8->GetString(buff, offset, filenameLength);

		offset += filenameLength;
		iFileSize = BitConverter::ToInt32(buff, offset);
		offset += 4;
		iPackageNumber = BitConverter::ToInt32(buff, offset);
		offset += 4;
		iTotalPackage = BitConverter::ToInt32(buff, offset);
		offset += 4;

		int dataSize = BitConverter::ToInt32(buff, offset);
		offset += 4;
		bData = gcnew array<Byte>(dataSize);
		if (dataSize > 0)
			System::Array::Copy(buff, offset, bData, 0, dataSize);

		//offset += dataSize;
		//isEncrypted = BitConverter::ToBoolean(buff, offset);
		return this;
	}
};

