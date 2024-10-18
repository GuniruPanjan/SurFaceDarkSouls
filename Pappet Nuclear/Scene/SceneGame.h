#pragma once
#include "Camera/Camera.h"
#include "Character/Player/Player.h"
#include "Character/Enemy/Enemy.h"
#include "Character/Player/Equipment/Equipment.h"
#include "Character/Animation/BlendAnimation.h"
#include "Map/Map.h"
#include "UI/UI.h"
#include "SceneBase.h"

/// <summary>
/// �Q�[���V�[�����Ǘ�����N���X
/// </summary>
class SceneGame : public SceneBase
{
public:
	//�R���X�g���N�^
	SceneGame();

	//�f�X�g���N�^
	virtual ~SceneGame();

	//����������
	virtual void Init();

	//�X�V����
	virtual std::shared_ptr<SceneBase> Update();

	//�`�揈��
	virtual void Draw();

	//�I������
	virtual void End();

private:

	bool m_one;    //��񂾂����s
	//�X�}�[�g�|�C���^�ŊǗ�
	std::shared_ptr<Player> player = std::make_shared<Player>();
	std::shared_ptr<Camera> camera = std::make_shared<Camera>();
	std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>();
	std::shared_ptr<Map> map = std::make_shared<Map>();
	std::shared_ptr<UI> ui = std::make_shared<UI>();
	std::shared_ptr<Equipment> equipment = std::make_shared<Equipment>();
	std::shared_ptr<BlendAnimation> panim = std::make_shared<BlendAnimation>();
};

