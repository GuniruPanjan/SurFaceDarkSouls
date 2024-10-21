#pragma once
#include "DxLib.h"
#include "LibVec3.h"

namespace MyLibrary
{
	/// <summary>
	/// �����A�Փ˔���ɕK�v�ȃf�[�^�̉�
	/// </summary>
	class Rigidbody
	{
	public:
		//�R���X�g���N�^
		Rigidbody();

		//������
		void Init(bool gravity = false);

		//velocity�ɗ͂�������
		void AddForce(const LibVec3& force);

		//���ݍ��W���擾
		const LibVec3& GetPos() const { return m_pos; }
		//�ړ��\����W
		const LibVec3& GetNextPos() const { return m_nextPos; }
		//����������
		const LibVec3& GetDir() const { return m_dir; }
		//�ړ����x������
		const LibVec3& GetVelocity() const { return m_velocity; }


		//���ݍ��W������
		const VECTOR GetPosVECTOR() { return m_pos.ConversionToVECTOR(); }
		//�ړ��\����W������
		const VECTOR GetNextPosVECTOR() { return m_nextPos.ConversionToVECTOR(); }
		//����������
		const VECTOR GetDirVECTOR() { return m_dir.ConversionToVECTOR(); }
		//�ړ����x������
		const VECTOR GetVelocityVECTOR() { return m_velocity.ConversionToVECTOR(); }
		//�d�͂�^���邩�ǂ���������
		bool GetUseGravity() const { return m_useGravity; }


		//���ݍ��W��ݒ�
		void SetPos(const LibVec3& set) { m_pos = set; }
		//�ړ��\����W��ݒ�
		void SetNextPos(const LibVec3& set) { m_nextPos = set; }
		//������ݒ�
		void SetVelocity(LibVec3 set, float mul = 1.0f);
		//�ړ����x��ݒ�
		void SetUseGravity(bool set) { m_useGravity = set; }

	private:
		//���ݍ��W
		LibVec3 m_pos;
		//�ړ��\����W
		LibVec3 m_nextPos;

		//����
		LibVec3 m_dir;
		//�ړ����x
		LibVec3 m_velocity;
		//�d�͂�^���邩���肷��
		bool m_useGravity;
	};
}


