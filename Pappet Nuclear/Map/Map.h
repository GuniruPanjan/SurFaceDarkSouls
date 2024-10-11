#pragma once
#include "DxLib.h"
#include "Col/RectCol.h"
#include "Col/SphereCol.h"
#include "Character/Effect/Effect.h"
#define ITEM_NUMBER 30

class Player;

class Map
{
public:
	Map();
	virtual ~Map();

	void Init();
	void Update(Effect& ef);
	void Draw();
	void End();

	bool CapsuleIsHit(const CapsuleCol& col);
	bool CapsuleSaveHit(const CapsuleCol& col);
	bool CapsuleItemHit(const CapsuleCol& col, int max);

	int GetCollisionMap() { return m_collisionHandle; }
	bool GetRoomEntered() { return m_bossRoomEntered; }
	bool GetSavePossible() { return m_saveSpot; }
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
};

