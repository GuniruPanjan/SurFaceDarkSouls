#include "SceneClear.h"
#include "SceneTitle.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneClear::SceneClear():
	m_pad(0)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneClear::~SceneClear()
{
	//���������
	DeleteGraph(m_backScene);
}

/// <summary>
/// ����������
/// </summary>
void SceneClear::Init()
{
	//�ǂݍ���
	m_backScene = pui->MyLoadGraph("Data/SceneBack/CLEARBackMini.png", 2, 2);

	//�ݒ�֌W
	setting->Init();
	pbgm->ClearInit();
	pbgm->ClearBGM();
}

/// <summary>
/// �X�V����
/// </summary>
/// <returns>�V�[����Ԃ�</returns>
std::shared_ptr<SceneBase> SceneClear::Update()
{
	//�p�b�h���͏���
	m_pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//A�{�^����������
	if (m_pad & PAD_INPUT_1)
	{
		return std::make_shared<SceneTitle>();
	}

	pbgm->Update(setting->GetVolume());

	return shared_from_this();  //���g�̃|�C���^��Ԃ�
}

/// <summary>
/// �`�揈��
/// </summary>
void SceneClear::Draw()
{
	DrawGraph(430, 100, m_backScene, false);

	setting->SettingDraw(setting->GetVolume());
}

/// <summary>
/// �I������
/// </summary>
void SceneClear::End()
{
	//���������
	DeleteGraph(m_backScene);
	setting->End();
	pbgm->End();
}
