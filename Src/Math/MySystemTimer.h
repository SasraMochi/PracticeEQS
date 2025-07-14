#ifndef MYTIMER_H_
#define MYTIMER_H_

// �}���`�v���b�g�t�H�[���Ή��̎�����舵���N���X(C++11�Ή��Ȃ�ڐA�e��)

#include <chrono> // ���x�̍��������𓾂�(C++�Ȃ�Windows,Mac�ȂǐF��Ȋ��Ŏg����)
#include <thread> // �����x�~sleep_for���邽�߂ɕK�v
#include <vector> // ���X�gvector�ɕK�v
#include <map>	// �����^�A�z�z��ɕK�v
#include <memory> // shared_ptr�񂵓ǂ݃|�C���^�ɕK�v
#include <string> // ������string�^�ɕK�v
#include <sstream> // ostringstream�ɕK�v �W���o��(ostringstream�ŕ�����ɕW���o�͂�)
#include <iomanip> // ���Ԃ̕�����o��put_time()�ɕK�v


#include "Singleton.h"

class MySystemTimer : public Singleton<MySystemTimer>
{
public:
	friend class Singleton<MySystemTimer>; // Singleton �ł̃C���X�^���X�쐬�͋���

	// �ŏ���system_clock��steady_clock�̗����Ō��ݎ��Ԃ��擾
	// ��system_clock�́yWindow�Ȃ�OS�̎���(���[�U�[���ύX�����犪���߂������肤��)�z
	// ��steady_clock�́y��OS�Ɉˑ����Ȃ�����(�s�t�Ȃ̂Ŏ��Ԍv���Ɍ����Ă���)�z
	std::chrono::system_clock::time_point systemInitTime = std::chrono::system_clock::now();
	std::chrono::steady_clock::time_point steadyInitTime = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point steadyNowTime = std::chrono::steady_clock::now();
	//
	std::chrono::system_clock::time_point systemTimeFromStart = UpdateSystemTimeFromStart();

	// ������ۊǂ��镶����y���ӁzUpdateSystemTimeFromStart()�Ă΂Ȃ������͍ŐV�ɍX�V����Ȃ�
	std::string timeStringSystemClock = GetTimeString("%Y�N%m��%d��%H��%M��%S�b");
	float timeScale = 1.0f;//[�����@�\]main.cpp�ŉ�ʂ�`�����x�ƘA�������ăX���[���[�V�����⑁�����
	bool isTimeScaleMode = false; //[�����@�\]�X���[���[�V�����A�����胂�[�h��ON OFF

	
	// �N�����Ԃ̋L�^�̏�����/���Z�b�g(Init�������΍Ď擾���ł���)
	void Init()
	{
		// �ŏ���system_clock��steady_clock�̗����Ō��ݎ��Ԃ��擾(�Ď擾��)
		systemInitTime = std::chrono::system_clock::now();
		steadyInitTime = std::chrono::steady_clock::now();
	}

	// ��������OS�ɍ��E���ꂸ���߂�(�v�Z���ʂ�systemTimeFromStart�ɕۊ�)
	std::chrono::system_clock::time_point UpdateSystemTimeFromStart()
	{
		steadyNowTime = std::chrono::steady_clock::now(); //�������𓾂�(OS�̎�������Ȃ���)
		// �J�n����steady_clock::now�Ƃ̍����Ƃ��āA�J�n����system_clock::now�ɑ���
		// [�Q�l] https://techblog.kayac.com/steady_clock
		systemTimeFromStart =
			systemInitTime + std::chrono::duration_cast<std::chrono::seconds>(steadyNowTime - steadyInitTime);
		return systemTimeFromStart;
	}

	// �����������̕�����t�H�[�}�b�g�œ���(�������̂�steadyNowTime��timeStringSystemClock�ɕۊ�)
	// �o�͂�"%c"�Ȃ�t�H�[�}�b�g��[Mon Nov 27 10:58:32 2017]
	// "%Y�N%m��%d��%H��%M��%S�b"�Ȃ�[2020�N12��11��14��30��15�b](�f�t�H���g)
	// [�t�H�[�}�b�g��] https://cpprefjp.github.io/reference/chrono/local_time.html
	std::string GetTimeString(const char* timeStringFormat = "%Y�N%m��%d��%H��%M��%S�b")
	{
		systemTimeFromStart = UpdateSystemTimeFromStart();//��������OS�����ɍ��E���ꂸ����

		// �����^�C�v�^��system_clock��time_point�^����time_t�^�ɕϊ�����B
		std::time_t timeFromStart = std::chrono::system_clock::to_time_t(systemTimeFromStart);
		// ���[�J���^�C���𓾂�(���[�J���^�C���ɂ��Ă͈ȉ������N�Q��)
		// https://programming.pc-note.net/c/time.html
		struct tm localTimeFromStart;
		localtime_s(&localTimeFromStart, &timeFromStart);
		//�yostringstream�z�͕�����X�g���[����<<���Z�q�Ȃǂ̕��@�Ńf�[�^�𗬂�����ł���
		// https://programming-place.net/ppp/contents/cpp/library/029.html#write_to_string_stream
		std::ostringstream oss;
		//�����̈�s�ŕ�����X�g���[���ɗ�������
		oss << std::put_time(&localTimeFromStart, timeStringFormat) << std::endl;

		timeStringSystemClock = oss.std::ostringstream::str(); //str()�ŕ�����string�����ĕۊ�
		return timeStringSystemClock; //�������𕶎���Ƃ��ĕԂ�
	}


	// Init���Ă��猻�݂܂ł̌o�ߎ��Ԃ𓾂�(�P��Tick = 100�i�m�b = 1/10000000�b)
	long GetElapsedTicks()
	{	// �������X�V
		UpdateSystemTimeFromStart();
		// Init���Ă��猻�݂܂ł̌o�ߎ���(�i�m�b)
		auto durationFromInit = std::chrono::duration_cast<std::chrono::nanoseconds>(steadyNowTime - steadyInitTime);
		// Tick���B1Tick = 100�i�m�b = 1/10000000�b
		return (long)(durationFromInit.count() / 100);
	}

	// �w��i�m�b �v���O�������x�~
	void SleepForNanoSec(int waittime)
	{	// �w��i�m�b �v���O�������x�~
		std::this_thread::sleep_for(std::chrono::nanoseconds(waittime));
	}

	// �w��}�C�N���b �v���O�������x�~
	void SleepForMicroSec(int waittime)
	{	// �w��~���b �v���O�������x�~
		std::this_thread::sleep_for(std::chrono::microseconds(waittime));
	}

	// �w��~���b �v���O�������x�~
	void SleepForMilliSec(int waittime)
	{	// �w��~���b �v���O�������x�~
		std::this_thread::sleep_for(std::chrono::milliseconds(waittime));
	}

	// �w�� �b �v���O�������x�~
	void SleepForSec(int waittime)
	{	// �w�� �b �v���O�������x�~
		std::this_thread::sleep_for(std::chrono::seconds(waittime));
	}

	// �w�� �� �v���O�������x�~
	void SleepForMinutes(int waittime)
	{	// �w�� �� �v���O�������x�~
		std::this_thread::sleep_for(std::chrono::minutes(waittime));
	}

protected:
	// �O������̃C���X�^���X�쐬�͋֎~
	MySystemTimer() {};
	//�O������̃C���X�^���X�j�����֎~
	virtual ~MySystemTimer() {};
};

#endif
