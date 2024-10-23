#pragma once
#include "DxLib.h"
#include "Library/MyLibrary.h"
#include "EnemyBase.h"

/// <summary>
/// �G���G�i�P�j
/// </summary>
class EnemyOne : public EnemyBase
{
public:
	//�R���X�g���N�^
	EnemyOne();
	//�f�X�g���N�^
	virtual ~EnemyOne();

	//������
	void Init(std::shared_ptr<MyLibrary::Physics> physics) override;
	//�X�V
	void Update(MyLibrary::LibVec3 playerPos, bool isChase);
	//�`��
	void Draw();
};

