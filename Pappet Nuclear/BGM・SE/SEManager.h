#pragma once
#include "DxLib.h"
#include<memory>

/// <summary>
/// SE���Ǘ�����N���X
/// </summary>
class SEManager
{
public:
	//�R���X�g���N�^
	SEManager();
	//�f�X�g���N�^
	virtual ~SEManager();

	//�V�[����SE����������
	void SceneInit();
	//�L����SE����������
	void CharaInit();
	//�{�XSE����������
	void BossInit();
	//�X�V����
	void Update(int volume);
	//�I������
	void End();

	int GetButtonSE() { return m_buttonSE; }              //�{�^����SE���Ƃ�
	int GetSelectSE() { return m_selectSE; }              //�I����SE���Ƃ�
	int GetHitSE() { return m_hitSE; }                    //�U�����q�b�g��������SE���Ƃ�
	int GetPlayerHitSE() { return m_playerHitSE; }        //�v���C���[�ɍU����������������SE���Ƃ�
	int GetAttackSE() { return m_attackSE; }              //�U������SE���Ƃ�
	int GetWalkSE() { return m_walkSE; }                  //��������SE���Ƃ�
	int GetHeelSE() { return m_playerHeelSE; }            //�񕜂�������SE���Ƃ�
	int GetRestSE() { return m_playerRestSE; }            //�x����������SE���Ƃ�
	int GetBossVoiceSE() { return m_bossVoiceSE; }        //�{�X�̋��т�SE���Ƃ�
	int GetBossAttackSE1() { return m_bossAttackSE[0]; }  //�{�X�̍U���P��SE���Ƃ�
	int GetBossAttackSE2() { return m_bossAttackSE[1]; }  //�{�X�̍U��2��SE���Ƃ�
	int GetBossAttackSE3() { return m_bossAttackSE[2]; }  //�{�X�̍U��3��SE���Ƃ�
	int GetBossWalkSE() { return m_bossWalkSE; }          //�{�X������������SE���Ƃ�
	int GetDiedSE() { return m_diedSE; }                  //���񂾎���SE���Ƃ�

private:
	//SE�֌W
	int m_buttonSE;         //�{�^����SE
	int m_selectSE;         //�I����������SE
	int m_hitSE;            //�G�l�~�[�ƃv���C���[�ƃ{�X��Hit����SE
	int m_playerHitSE;      //�{�X�̍U����Hit����SE
	int m_attackSE;         //�G�l�~�[�ƃv���C���[�̍U������SE
	int m_walkSE;           //�G�l�~�[�ƃv���C���[�̕�������SE
	int m_playerHeelSE;     //�񕜂�������SE
	int m_playerRestSE;     //�x����������SE
	int m_bossVoiceSE;      //�{�X�̙��KSE
	int m_bossAttackSE[3];  //�{�X�̍U���R�p�^�[��
	int m_bossWalkSE;       //�{�X����������SE
	int m_diedSE;           //���񂾎���SE
	int m_volumePal;        //����
};

