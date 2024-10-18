#pragma once
#include "DxLib.h"
#include "BGM�ESE/BgmManager.h"
#include "UI/Setting.h"
#include "UI/UI.h"
#include<memory>

/// <summary>
/// �V�[���̃x�[�X���Ǘ�����N���X
/// </summary>
class SceneBase : public std::enable_shared_from_this<SceneBase>
{
public:
	//�R���X�g���N�^
	SceneBase():
		m_end(false)
	{}

	//�f�X�g���N�^
	virtual ~SceneBase(){}

	//virtual�Ōp������Ăяo��

	//����������
	virtual void Init() = 0;

	//�X�V����
	virtual std::shared_ptr<SceneBase> Update() = 0;

	//�`�揈��
	virtual void Draw() = 0;

	//�I������
	virtual void End() = 0;

	/// <summary>
	/// ������Ƃ�
	/// </summary>
	/// <returns>�I�������Ԃ�</returns>
	bool GetEnd() { return m_end; }

	/// <summary>
	/// �I����������߂�
	/// </summary>
	/// <param name="end">������Ƃ�</param>
	/// <returns>���ʂ�Ԃ�</returns>
	bool SetEnd(bool end) { return m_end = end; }

protected:
	//�ϐ�������
	int m_backScene = 0;
	bool m_end;   //�Q�[���I���ϐ�

	//�X�}�[�g�|�C���^
	std::shared_ptr<Setting> setting = std::make_shared<Setting>();
	std::shared_ptr<BgmManager> pbgm = std::make_shared<BgmManager>();
	std::shared_ptr<UI> pui = std::make_shared<UI>();
};

