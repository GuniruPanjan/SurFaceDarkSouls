#pragma once
#include "SceneBase.h"

/// <summary>
/// �Q�[���̃N���A�V�[�����Ǘ�����N���X
/// </summary>
class SceneClear : public SceneBase
{
public:
	//�R���X�g���N�^
	SceneClear();
	//�f�X�g���N�^
	virtual ~SceneClear();

	//����������
	virtual void Init();

	//�X�V����
	virtual std::shared_ptr<SceneBase> Update();

	//�`�揈��
	virtual void Draw();

	//�I������
	virtual void End();

private:
	//Pad���͏����ϐ�
	int m_pad;
};

