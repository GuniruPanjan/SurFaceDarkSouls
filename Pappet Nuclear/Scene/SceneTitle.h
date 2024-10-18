#pragma once
#include "SceneBase.h"
#include "Map/Map.h"
#include<memory>

class SelectManager;

//�V�[���^�C�g���̃N���X
class SceneTitle : public SceneBase
{
public:
	//�R���X�g���N�^
	SceneTitle();
	//�f�X�g���N�^
	virtual ~SceneTitle();

	//����������
	virtual void Init();
	//�X�V����
	virtual std::shared_ptr<SceneBase> Update();

	/// <summary>
    /// �I�𒆂̏ꍇ
    /// </summary>
    /// <param name="select">�񋓌^</param>
    /// <param name="now">�I�����Ă����</param>
    /// <param name="other1">����ȊO�P</param>
    /// <param name="other2">����ȊO�Q</param>
	void SelectBlend(int select, int now, int other1, int other2);

	//�`�揈��
	virtual void Draw();

	//�I������
	virtual void End();

private:
	XINPUT_STATE m_xpad;  //�p�b�h����
	int m_start;      //�X�^�[�g�{�^���摜�i�[�ϐ�
	int m_setting;    //�ݒ�{�^���摜�i�[�ϐ�
	int m_end;        //�I���{�^���摜�i�[�ϐ�
	int m_button;    //���������Ԃ𓾂�
	int m_select[3];    //�I��p�̕ϐ�
	int m_pal[3];      //�u�����h�`��p
	bool m_one;      //�P������
	bool m_blend;    //�u�����h����
	bool m_setButton;    //�ݒ�̔���
	int m_waitTime;      //�҂��߂̎���
	VECTOR m_cameraPos;    //�J�����|�W�V����
	VECTOR m_cameraTarget;     //�J�����̃^�[�Q�b�g�|�W�V����

	//���f���p�ϐ�
	int m_playerHandle;          //�v���C���[�̃��f���i�[�ϐ�
	int m_anim;                  //�v���C���[�̃A�j���[�V�����i�[�ϐ�
	int m_animation;
	float m_totalAnimationTime;
	float m_playTime;
	VECTOR m_pos;

	
	//�X�}�[�g�|�C���^
	std::shared_ptr<Map> map = std::make_shared<Map>();
	std::shared_ptr<SEManager> se = std::make_shared<SEManager>();
	std::shared_ptr<SelectManager> pselect = std::make_shared<SelectManager>();
};