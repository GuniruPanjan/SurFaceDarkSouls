#include "SceneManager.h"
#include "SceneTitle.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneManager::SceneManager():
	m_pScene(nullptr)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneManager::~SceneManager()
{
}

/// <summary>
/// ����������
/// </summary>
void SceneManager::Init()
{
	//�ŏ��̃V�[���̃��������������
	m_pScene = std::make_shared<SceneTitle>();

	m_pScene->Init();
}

/// <summary>
/// �X�V����
/// </summary>
void SceneManager::Update()
{
	std::shared_ptr<SceneBase> pNext = m_pScene->Update();
	if (pNext != m_pScene)
	{
		//���݂̃V�[���̏I������
		m_pScene->End();

		//Update���Ԃ����V�����V�[���̊J�n�������s��
		m_pScene = pNext;
		m_pScene->Init();
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void SceneManager::Draw()
{
	m_pScene->Draw();
}

/// <summary>
/// �I������
/// </summary>
void SceneManager::End()
{
	m_pScene->End();
}
