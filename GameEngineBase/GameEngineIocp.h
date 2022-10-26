#pragma once
#include <Windows.h>
#include <process.h>

// CreateIoCompletionPort�� 2���� �뵵�� ���ȴ�.
// ��������¿��� ����Ҽ� �ִ°͵� �ƴմϴ�.
// �����带 �ڵ鸵
// ���� ���������� �����带 �����ϰ� ������
// ��������°� ���Ͽ����� ������� �ʰ�
// ��������� == ��������̱� ������

// ������ �����带 �ھ� ������ŭ ����̴ϴ�.

class GameEngineIocp
{
private:
	HANDLE IocpHandle;

public:
	bool Start(int ThreadCount = 0)
	{
		IocpHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, ThreadCount);
		if (nullptr == IocpHandle)
		{
			// ġ������ ����.
			return false;
		}

		return true;
	}


	// ��������� == �������
	// HANDLE CompletionPort, �� �����带 �����ϴ� IOCP
	// LPDWORD lpNumberOfBytesTransferred, ������� Ȥ�� ��������� �ϰ� �ִٸ� 
	//                                    ���� ��Ʃ�� ���� �������� xxx����Ʈ ��ŭ �޾Ҿ��.
	//                                    ���� ���� 3�Ⱑ¥�� ������ 200�ް� �о����
	// PULONG_PTR lpCompletionKey, // ���� �ѱ涧 8����Ʈ ������ �ѱ�� �ִ�.
	// LPOVERLAPPED* lpOverlapped, // ��������� �Ҷ� ������� ���� �񵿱� ����� ����.  
	// DWORD dwMilliseconds      // �̰� �󸶳� ��ٸ��ų�.
	//                          INFINITY�� ������ ��¥ ���� ���������� ������ ��ٸ�.

	BOOL WaitforWork(DWORD& lpNumberOfBytesTransferred, ULONG_PTR& lpCompletionKey, LPOVERLAPPED& lpOverlapped, DWORD dwMilliseconds = INFINITE)
	{
		return GetQueuedCompletionStatus(IocpHandle, &lpNumberOfBytesTransferred, &lpCompletionKey, &lpOverlapped, dwMilliseconds);
	}

	// WorkParameter �ƹ��ų� ��������� �������ش�.
	// -1�� ����.
	BOOL Makework(DWORD _WorkParameter, void* _Ptr)
	{
		return PostQueuedCompletionStatus(IocpHandle, _WorkParameter, reinterpret_cast<ULONG_PTR>(_Ptr), nullptr);
	}

public:
	GameEngineIocp()
		: IocpHandle(nullptr)
	{}

	~GameEngineIocp() {}
};

