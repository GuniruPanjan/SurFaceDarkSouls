#pragma once
#include <memory>
#include <string>
#include "Library/MyLibrary.h"

class Camera;
class Player;
class Enemy;
class Map;
class UI;

/// <summary>
/// �Q�[�����̂��Ǘ�����N���X
/// </summary>
class GameManager
{
public:
	enum StageName : int
	{
		FirstStage,      //��ԍŏ��̃X�e�[�W
		SecondStage,     //��Ԗڂ̃X�e�[�W
		ThreeStage,      //�O�Ԗڂ̃X�e�[�W
		FourStage,       //�l�Ԗڂ̃X�e�[�W
		LastStage,       //�Ō�̃X�e�[�W
		RestStage        //�x���X�e�[�W
	};

public:
	//�R���X�g���N�^
	GameManager();
	//�f�X�g���N�^
	virtual ~GameManager();

	//������
	void Init();
	//�X�V
	void Update();
	//�ŏ��̃X�e�[�W�̍X�V
	void FirstUpdate();
	//��ڂ̃X�e�[�W�̍X�V
	void SecondUpdate();
	//�O�ڂ̃X�e�[�W�̍X�V
	void ThreeUpdate();
	//�l�ڂ̃X�e�[�W�̍X�V
	void FourUpdate();
	//�Ō�̃X�e�[�W�̍X�V
	void LastUpdate();
	//�x���X�e�[�W�̍X�V
	void RestUpdate();
	//�`��
	void Draw();
	//�I��
	void End();

private:
	//�X�e�[�W��
	std::string m_stageName;

	//�v���C���[�N���X�|�C���^
	std::shared_ptr<Player> m_pPlayer;
	//�G�N���X�|�C���^
	std::shared_ptr<Enemy> m_pEnemy;
	//�J�����N���X�|�C���^
	std::shared_ptr<Camera> m_pCamera;
	//�}�b�v�N���X�|�C���^
	std::shared_ptr<Map> m_pMap;
	//UI�N���X�|�C���^
	std::shared_ptr<UI> m_pUI;

	//����
	std::shared_ptr<MyLibrary::Physics> m_pPhysics;

	//�v���C���[�����S�������̔���
	bool m_playerDead;
};

