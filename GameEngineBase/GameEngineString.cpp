#include "PreCompile.h"
#include "GameEngineString.h"
#include "GameEngineDebug.h"

GameEngineString::GameEngineString() // default constructer ����Ʈ ������
{

}

GameEngineString::~GameEngineString() // default destructer ����Ʈ �Ҹ���
{

}

GameEngineString::GameEngineString(GameEngineString&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}

std::string GameEngineString::toupper(const std::string& _Text)
{
	std::string Text = _Text;

	std::transform(Text.begin(), Text.end(), Text.begin(), ::toupper);

	return Text;
}

void GameEngineString::AnsiToUnicode(const std::string& _Text, std::wstring& _Out)
{
	int Size = MultiByteToWideChar(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), nullptr, 0);
#ifdef _DEBUG
	if (Size == 0)
	{
		GameEngineDebug::MsgBoxError("��Ʈ�� ��ȯ�� �����߽��ϴ�.");
		return;
	}
#endif // _DEBUG

	_Out.resize(Size);

	Size = MultiByteToWideChar(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), &_Out[0], Size);
#ifdef _DEBUG
	if (Size == 0)
	{
		GameEngineDebug::MsgBoxError("��Ʈ�� ��ȯ�� �����߽��ϴ�.");
		return;
	}
#endif // _DEBUG
}

// u8""

void GameEngineString::UniCodeToUTF8(const std::wstring& _Text, std::string& _Out)
{
	int Size = WideCharToMultiByte(CP_UTF8, 0, _Text.c_str(), static_cast<int>(_Text.size()), nullptr, 0, nullptr, nullptr);
#ifdef _DEBUG
	if (Size == 0)
	{
		GameEngineDebug::MsgBoxError("��Ʈ�� ��ȯ�� �����߽��ϴ�.");
		return;
	}
#endif // _DEBUG

	_Out.resize(Size);

	Size = WideCharToMultiByte(CP_UTF8, 0, _Text.c_str(), static_cast<int>(_Text.size()), &_Out[0], static_cast<int>(_Out.size()), nullptr, nullptr);
#ifdef _DEBUG
	if (Size == 0)
	{
		GameEngineDebug::MsgBoxError("��Ʈ�� ��ȯ�� �����߽��ϴ�.");
		return;
	}
#endif // _DEBUG

}

void GameEngineString::AnsiToUTF8(const std::string& _Text, std::string& _Out)
{
	std::wstring WString;

	AnsiToUnicode(_Text, WString);
	UniCodeToUTF8(WString, _Out);
}

std::string GameEngineString::AnsiToUTF8Return(const std::string& _Text)
{
	std::wstring WString;
	std::string Result;

	AnsiToUnicode(_Text, WString);
	UniCodeToUTF8(WString, Result);

	return Result;
}

std::wstring GameEngineString::StringToWStringReturn(const std::string& _Text)
{
	std::wstring Return;

	int Size = MultiByteToWideChar(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), nullptr, 0);
#ifdef _DEBUG
	if (Size == 0)
	{
		GameEngineDebug::MsgBoxError("��Ʈ�� ��ȯ�� �����߽��ϴ�.");
		return L"";
	}
#endif // _DEBUG

	Return.resize(Size);

	Size = MultiByteToWideChar(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), &Return[0], Size);
#ifdef _DEBUG
	if (Size == 0)
	{
		GameEngineDebug::MsgBoxError("��Ʈ�� ��ȯ�� �����߽��ϴ�.");
		return L"";
	}
#endif // _DEBUG

	return Return;
}
