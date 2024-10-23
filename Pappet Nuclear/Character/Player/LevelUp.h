#pragma once

class Player;
class Enemy;

/// <summary>
/// ���x���֌W���Ǘ�����N���X
/// </summary>
class LevelUp
{
public:
	//�R���X�g���N�^
	LevelUp();
	//�f�X�g���N�^
	virtual ~LevelUp();

	//����������
	void Init(Player& player, Enemy& enemy);
	//���x�����グ��X�V����
	void Update(Player& player, Enemy& enemy);
	//�v���C���[�����񂾎��̏���
	void PlayerDeath(Player& player);
	//�X�e�[�^�X��`�悷��
	void Draw();
	//�I������
	void End();

private:
	int m_lHp;        //�̗̓��x�� 
	int m_lStamina;   //�X�^�~�i���x��
	int m_lMuscle;    //�ؗ̓��x��
	int m_lSkill;     //�Z�ʃ��x��
	int m_lAll;       //���ׂẴ��x��
	int m_lCore;      //���x���グ�Ɏg���R�A�܂Ƃ�
	int m_lUseCore;   //���x���グ�Ɏg���R�A
};

