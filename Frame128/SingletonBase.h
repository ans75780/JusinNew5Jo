#pragma once
//=====================================================
//  ## singletonBase ## (�� ���̽��� �̱����� �����)
//=====================================================

/*
	�̱��� ������ static member�� �ϳ��� �ν��Ͻ��� �����Ǹ�,
	���α׷� �ȿ��� ���������� ������  �����ϴ�.
	���� Ŭ������ �ν��Ͻ��� �ϳ��� �����ϰ��� �� �� ����Ѵ�.

	���� ������ �̿��ص� �ϳ��� �ν��Ͻ��� ������ �� ������,
	�̱��� ������ ����ϸ� Ŭ���� �ڽ��� �ڱ��� ������ �ν��Ͻ���
	�����ϴ� ����� ĸ��ȭ �Ͽ� ������ �� �ְ�, ���, ��ü ����,
	��ü �Ҹ�, �ν��Ͻ��� ���� ������ Ȱ�뿡 �����ϴ�.

	�� ���� ����� �ڱ� �����ΰ� �ڱ��� ������ �ν��Ͻ��� �����ϴ�
	����� ��ü������ �����ϴ� ����̴�.
	�� �̱��� ���̽��� �ٸ� �ν��Ͻ��� �������� �ʵ��� ó�� �� �� �ְ�,
	���� ��� ���� ������ �� �� �ִ�.
*/
template <typename T>
class CSingletonBase
{
protected:
	//�̱��� �ν��Ͻ� ����
	static T* singleton;

	CSingletonBase() {};
	~CSingletonBase() {};

public:
	//�̱��� ��ü ��������
	static T* GetSingleton();
	void ReleaseSingleton();
};

//�̱��� �ν��Ͻ� ����
template <typename T>
T* CSingletonBase<T>::singleton = nullptr;

//�̱��� ��ü ��������
template<typename T>
inline T* CSingletonBase<T>::GetSingleton()
{
	//�̱��� ��ü�� ������ ���� ����
	if (!singleton) singleton = new T;

	return singleton;
}

//�̱��� ��ü �޸𸮿��� ����
template<typename T>
inline void CSingletonBase<T>::ReleaseSingleton()
{
	//�̱��� ��ü�� �ִٸ� �޸𸮿��� ����
	if (singleton)
	{
		delete singleton;
		singleton = nullptr;
	}
}
