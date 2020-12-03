#pragma once
#include "PrivateChatForm.h"
ref class PrivateChatInfo
{
	Form_Client::PrivateChatForm^ privateChatForm;
	System::String^ userName;
	PrivateChatInfo(Form_Client::PrivateChatForm^ _privateChatForm, System::String^ _strUsername) :
		privateChatForm(_privateChatForm), userName(_strUsername) {};
};

