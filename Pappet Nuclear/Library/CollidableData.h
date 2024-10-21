#pragma once

namespace MyLibrary
{
	/// <summary>
	/// �����蔻��̃f�[�^���
	/// </summary>
	class CollidableData
	{
	public:
		//�����蔻����
		enum class Kind
		{
			Capsule,     //�J�v�Z���^
			Sphere,      //���̌^
			Rect,        //�l�p�^
		};

		//�R���X�g���N�^
		CollidableData(Kind kind, bool isTrigger)
		{
			this->kind = kind;
			this->m_isTrigger = isTrigger;
		}

		virtual ~CollidableData() {}

		//�����蔻���ʏ���
		Kind GetKind() const { return kind; }

		//�g���K�[���ǂ���
		bool IsTrigger() const { return m_isTrigger; }

	private:
		Kind kind;
		bool m_isTrigger;
	};
}


