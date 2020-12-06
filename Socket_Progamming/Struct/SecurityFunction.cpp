//#include "SecurityFunction.h"
//String^ convertStringToHex(String^ input)
//{
//    List<Byte>^ stringBytes = gcnew List<Byte>();
//    stringBytes->AddRange(Encoding::UTF8->GetBytes(input));
//    // Byte[] stringBytes = encoding.GetBytes(input);
//    array<Byte>^ temp = stringBytes->ToArray();
//    StringBuilder^ sbBytes = gcnew StringBuilder(temp->Length * 2);
//    for each (Byte b in temp)
//    {
//        sbBytes->AppendFormat("{0:X2}", b);
//    }
//    return sbBytes->ToString();
//}
//
//String^ convertHexToString(String^ hexInput)
//{
//    int numberChars = hexInput->Length;
//    array<Byte>^ bytes = gcnew array<Byte>(numberChars / 2);
//    // byte[] bytes = new byte[numberChars / 2];
//    for (int i = 0; i < numberChars; i += 2)
//    {
//        bytes[i / 2] = Convert::ToByte(hexInput->Substring(i, 2), 16);
//    }
//    return Encoding::UTF8->GetString(bytes);
//}