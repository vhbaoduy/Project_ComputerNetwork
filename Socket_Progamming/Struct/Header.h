#pragma once
#include "Struct.h"
#include "LogInClass.h"
#include "ResponseLogIn.h"
#include "LogInNotification.h"
#include "SignUpClass.h"
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
			case StructClass::MessageType::LogIn:
				result = gcnew LogInClass();
				result->messageType = StructClass::MessageType::LogIn;
				result->unpack(buffer);

				break;
			case StructClass::MessageType::ResponseLogin:
				result = gcnew ResponseLogIn();
				result->messageType = StructClass::MessageType::ResponseLogin;
				result->unpack(buffer);
				break;
			case StructClass::MessageType::SignUp:
				result = gcnew SignUpClass();
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
