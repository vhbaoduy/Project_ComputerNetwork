#pragma once
#include "Struct.h"

#include "Account.h"
#include "ResponseLogIn.h"
#include "LogInNotification.h"
#include "ResponseSignUp.h"



ref class ProcessApp
{
public:
	static StructClass^ unpack(array<Byte>^ buffer) {
		{
			if (buffer->Length == 0)
				return nullptr;


			StructClass^ result = nullptr;
			StructClass::MessageType messageType = (StructClass::MessageType)BitConverter::ToInt32(buffer, 0);

			switch (messageType)
			{
			case StructClass::MessageType::ResponseLogin:
				result = gcnew ResponseLogIn();
				result->messageType = StructClass::MessageType::ResponseLogin;
				result->unpack(buffer);
				break;
			case StructClass::MessageType::SignUp:
				result = gcnew Account();
				result->messageType = StructClass::MessageType::SignUp;
				result->unpack(buffer);

				break;
			case StructClass::MessageType::ResponseSignUp:
				result = gcnew ResponseSignUp();
				result->messageType = StructClass::MessageType::ResponseSignUp;
				result->unpack(buffer);

				break;
			case StructClass::MessageType::LogInNotification:
				result = gcnew LogInNotification();
				result->messageType = StructClass::MessageType::LogInNotification;
				result->unpack(buffer);

				break;
			default:
				break;
			}



			return result;
		}
	}
};
