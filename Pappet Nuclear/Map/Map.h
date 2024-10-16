#pragma once
#include "DxLib.h"
#include "Col/RectCol.h"
#include "Col/SphereCol.h"
#include "Character/Player/Item/ItemManager.h"
#include<memory>

class Player;
class Effect;

class Map
{
public:
	Map();
	virtual ~Map();

	void Init();
	void Update();
	void ItemPos(int number, float x, float y, float z);
	void Draw();
	void End();

	/// <summary>
	/// �L�����N�^�[�Ƃ̓����蔻��
	/// </summary>
	/// <param name="col">�v���C���[�̃J�v�Z��</param>
	/// <returns></returns>
	bool CapsuleIsHit(const CapsuleCol& col);

	/// <summary>
	/// �v���C���[�̋x������
	/// </summary>
	/// <param name="col">�v���C���[�̃J�v�Z��</param>
	/// <returns></returns>
	bool CapsuleSaveHit(const CapsuleCol& col);

	/// <summary>
	/// �A�C�e���̓����蔻��
	/// </summary>
	/// <param name="col">�v���C���[�Ƃ̓����蔻��</param>
	/// <param name="max">�A�C�e���̔z��</param>
	/// <returns></returns>
	bool CapsuleItemHit(const CapsuleCol& col, int max);

	int GetCollisionMap() { return m_collisionHandle; }
	bool GetRoomEntered() { return m_bossRoomEntered; }
	bool GetSavePossible() { return m_saveSpot; }
	bool GetItem(int max) { return item->GetItem(max); }
	bool SetItemSpot(int max, bool set) { return m_itemSpot[max] = set; }
	bool SetGetItem(int max, bool get) { return item->SetGetItem(max, get); }
	VECTOR GetVectorMapPos() { return m_MapPosition; }
	VECTOR GetRestPos() { return m_restPos; }

private:
	int m_handle;   //�}�b�v�̃f�[�^������ϐ�
	int m_collisionHandle;   //�}�b�v�̃R���W�����̃f�[�^������ϐ�
	int m_light;    //���C�g�����ϐ�
	int m_itemModel[ITEM_NUMBER];         //�}�b�v�ɒu���A�C�e���̃��f���ϐ�
	float m_size;   //���f���̃T�C�Y�ϐ�
	float m_Xposition;    //X�|�W�V����
	float m_Yposition;    //Y�|�W�V����
	float m_Zposition;    //Z�|�W�V����
	float m_XCollisionposition;    //X�|�W�V����
	float m_YCollisionposition;    //Y�|�W�V����
	float m_ZCollisionposition;    //Z�|�W�V����
	bool m_bossRoomEntered;    //�{�X�����ɓ���������
	bool m_saveSpot;        //�񕜃X�|�b�g���g���锻��
	bool m_oneInit;         //��񂾂�����������
	bool m_itemSpot[ITEM_NUMBER];        //�A�C�e���������ł���ꏊ
	VECTOR m_MapPosition;   //�}�b�v�̃|�W�V����
	VECTOR m_collisionMapPosition;   //�R���W�����̃|�W�V�����ݒ�
	VECTOR m_restPos;        //�x������|�W�V����


	//Col�̓����蔻��
	float m_sphereRadius;
	float m_itemRadius;
	Pos3 m_rectPos;
	Pos3 m_spherePos;
	Pos3 m_itemPos[ITEM_NUMBER];
	Size m_rectSize;
	RectCol m_rectCol;
	SphereCol m_sphereCol;
	SphereCol m_itemCol[ITEM_NUMBER];
	unsigned int m_color = 0xffffff;
	unsigned int m_sphereColor = 0xffffff;
	unsigned int m_itemColor[ITEM_NUMBER];

	//�X�}�[�g�|�C���^
	std::shared_ptr<ItemManager> item = std::make_shared<ItemManager>();
};

