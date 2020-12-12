#pragma once
#include "Struct.h"
ref class RequestSendPublicFileClass:public StructClass
{
public:
	String^ fileName;

	RequestSendPublicFileClass() {
		
		fileName = nullptr;
	}
	virtual array<Byte>^ pack() override {
		List<Byte>^ byteData = gcnew List<Byte>();
		byteData->AddRange(BitConverter::GetBytes(int(StructClass::MessageType::RequestSendPublicFile)));



		//add FileName Info
		if (fileName != nullptr)
		{
			byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(fileName))); //Length of FileName
			byteData->AddRange(Encoding::UTF8->GetBytes(fileName)); //FileName string
		}
		else
			byteData->AddRange(BitConverter::GetBytes(0));

		//Return
		return byteData->ToArray();
	}
	virtual StructClass^ unpack(array<Byte>^ buff) override {

		int offset = 4; //Skip messageType
		int  filenameLength;


		filenameLength = BitConverter::ToInt32(buff, offset);
		offset += 4; //Update offset
		if (filenameLength > 0)
			fileName = Encoding::UTF8->GetString(buff, offset, filenameLength);

		return this;
	}

};

