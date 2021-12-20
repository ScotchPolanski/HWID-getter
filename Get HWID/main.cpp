#include <iostream>
#include <atlsecurity.h> // für get_hwid()
#include <atlconv.h> // für CT2A
#include <fstream> // für TXT
#include "xorstr.hpp"

using namespace std;

string getHWID() 
{
	HW_PROFILE_INFO hwProfileInfo;
	GetCurrentHwProfile(&hwProfileInfo);
	wstring hwidWString = hwProfileInfo.szHwProfileGuid;
	string hwid(hwidWString.begin(), hwidWString.end());
	return hwid;
}


static std::string get_hwid() 
{
	ATL::CAccessToken accessToken;
	ATL::CSid currentUserSid;
	if (accessToken.GetProcessToken(TOKEN_READ | TOKEN_QUERY) &&
		accessToken.GetUser(&currentUserSid))
		return std::string(CT2A(currentUserSid.Sid()));
}

void ClearEnter()
{
	cin.ignore(cin.rdbuf()->in_avail());
}

int main()
{
	SetConsoleTitle(XorStr(L"HWID getter | Scotch#5627").c_str());
	ofstream datei("HWID by Scotch.txt");


	if (!datei)
	{
		cout << XorStr("Error in creating file!").c_str();
		return 0;
	}
	else
	{
		datei << XorStr("getHWID = ").c_str() << getHWID() << std::endl;
		datei << XorStr("get_hwid = ").c_str() << get_hwid() << std::endl;
		datei.close();
		char path[MAX_PATH];
		std::cout << getHWID() << std::endl;
		std::cout << get_hwid() << std::endl;
		std::cout << std::endl;
		std::cout << XorStr("Textfile created!").c_str() << std::endl;
		ClearEnter;
		getchar();
		return 0;
	}
}
