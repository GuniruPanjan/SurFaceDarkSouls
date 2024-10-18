#pragma once
#include "Scene/SceneBase.h"
#include<memory>

//class SceneBase;

/// <summary>
/// �V�[�����Ǘ�����N���X
/// </summary>
class SceneManager
{
public:
	//�R���X�g���N�^
	SceneManager();
	//�f�X�g���N�^
	virtual ~SceneManager();

	//����������
	void Init();

	//�X�V����
	void Update();

	//�`�揈��
	void Draw();

	//�I������
	void End();

	//�v���O�������������锻���Ԃ�
	bool GetEnd() { return m_pScene->GetEnd(); }

private:

	//�X�}�[�g�|�C���^
	std::shared_ptr<SceneBase> m_pScene;
};

