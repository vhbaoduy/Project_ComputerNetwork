#pragma once
#include "Struct.h"
#include "LogInClass.h"
#include "ResponseLogIn.h"
#include "LogInNotification.h"
#include "SignUpClass.h"
#include "ResponseSignUp.h"
#include "LogOutNotification.h"
#include "UserStatusClass.h"
#include "PublicChat.h"
#include "PrivateChat.h"
#include "RequestSendFile.h"
#include "ResponseSendFile.h"
#include "PrivateFile.h"
#include "ChangePasswordClass.h"
#include "ResponseChangePassword.h"
#include "SetInforClass.h"
#include "RequestInforClass.h"
#include "ResponseInforClass.h"




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
			case StructClass::MessageType::ChangePassword:
				result = gcnew ChangePasswordClass();
				result->messageType = StructClass::MessageType::ChangePassword;
				result->unpack(buffer);

				break;
			case StructClass::MessageType::ResponseChangePassword:
				result = gcnew ResponseChangePassword();
				result->messageType = StructClass::MessageType::ResponseChangePassword;
				result->unpack(buffer);

				break;
			case StructClass::MessageType::LogInNotification:
				result = gcnew LogInNotification();
				result->messageType = StructClass::MessageType::LogInNotification;
				result->unpack(buffer);

				break;
			case StructClass::MessageType::LogOutNotification:
				result = gcnew LogOutNotification();
				result->messageType = StructClass::MessageType::LogOutNotification;
				result->unpack(buffer);
				break;
			case StructClass::MessageType::UserStatus:
				result = gcnew UserStatusClass();
				result->messageType = StructClass::MessageType::UserStatus;
				result->unpack(buffer);
				break;

			case StructClass::MessageType::PublicChat:
			{
				result = gcnew PublicChat();
				result->messageType = StructClass::MessageType::PublicChat;
				result->unpack(buffer);
				break;
			}
			case StructClass::MessageType::PrivateChat:
			{
				result = gcnew PrivateChat();
				result->messageType = StructClass::MessageType::PrivateChat;
				result->unpack(buffer);
				break;
			}
			case StructClass::MessageType::RequestSendFile:
			{
				result = gcnew RequestSendFile();
				result->messageType = StructClass::MessageType::RequestSendFile;
				result->unpack(buffer);
				break;
			}
			case StructClass::MessageType::ResponseSendFile:
			{
				result = gcnew ResponseSendFile();
				result->messageType = StructClass::MessageType::ResponseSendFile;
				result->unpack(buffer);
				break;

			}
			case StructClass::MessageType::PrivateFile:
			{
				result = gcnew PrivateFile();
				result->messageType = StructClass::MessageType::PrivateFile;
				result->unpack(buffer);
				break;
			}

			case StructClass::MessageType::SetInfor:
			{
				result = gcnew SetInforClass();
				result->messageType = StructClass::MessageType::SetInfor;
				result->unpack(buffer);
				break;
			}
			case StructClass::MessageType::ResponseInfor:
			{
				result = gcnew ResponseInforClass();
				result->messageType = StructClass::MessageType::ResponseInfor;
				result->unpack(buffer);
				break;

			}
			case StructClass::MessageType::RequestInfor:
			{
				result = gcnew RequestInforClass();
				result->messageType = StructClass::MessageType::RequestInfor;
				result->unpack(buffer);
				break;
			}
			default:
				break;
			}



			return result;
		}
	}
};
