#pragma once


/// <summary>
///�I������I�Ԃ��߂̃}�l�[�W���[
/// </summary>
class SelectManager
{
public:
	SelectManager();
	virtual ~SelectManager();

	//�I�����邽�߂̗񋓌^
	typedef enum
	{

		One,       //�I��0
		Two,       //�I��1
		Three,     //�I��2
		Four,      //�I��3
		Five,      //�I��4
		Six,       //�I��5
		Seven,     //�I��6
		Eight,     //�I��7
		Nine,      //�I��8
		Ten,       //�I��9
		SELECT_SIZE

	}SelectName;

	int NowSelect;    //�I��ł������

	//���j���[�Ȃǂ̑I��p�֐�
	void Menu_Update(int stick, bool& one, int button, int& decision, int now);

	//�A�C�e���Ȃǂ̑I��p�֐�
	void Item_Update();

	void Draw();

};

