#pragma once
#include "DxLib.h"
#include<memory>

/// <summary>
/// BGM���Ǘ�����N���X
/// </summary>
class BgmManager
{
public:
	//�R���X�g���N�^
	BgmManager();
	//�f�X�g���N�^
	virtual ~BgmManager();

	//�^�C�g���V�[��BGM������
	void TitleInit();
	//�Q�[���V�[��BGM������
	void GameInit();
	//�N���A�V�[��BGM������
	void ClearInit();
	//�X�V����
	void Update(int volume);
	//�^�C�g��BGM�X�V����
	void TitleBGM();
	//�Q�[��BGM�X�V����
	void GameBGM();
	//�{�XBGM�X�V����
	void BossBGM();
	//�N���ABGM�X�V����
	void ClearBGM();
	//�I������
	void End();

	//�{�X��BGM�𗬂����̔�����Ƃ�
	int GetBossBGM() { return m_bossBGM; }

private:
	//BGM�֌W
	int m_titleBGM;
	int m_gameBGM;
	int m_bossBGM;
	int m_clearBGM;
	int m_volumePal;
};

