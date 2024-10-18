#include "SceneTitle.h"
#include "SceneGame.h"
#include "Singleton/HandleManager.h"
#include "UI/SelectManager.h"

namespace
{
	int selectDecision = 0;  //�I�����A���肵������

	//�V���O���g��
	auto& handle = HandleManager::GetInstance();
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneTitle::SceneTitle():
	m_start(0),
	m_setting(0),
	m_end(0),
	m_button(0),
	m_one(false),
	m_blend(false),
	m_setButton(false),
	m_waitTime(0),
	m_cameraPos(VGet(0.0f,0.0f,0.0f)),
	m_playerHandle(0),
	m_anim(0),
	m_animation(0),
	m_totalAnimationTime(0.0f),
	m_playTime(0.0f),
	m_pos(VGet(0.0f,0.0f,0.0f)),
	m_cameraTarget(VGet(0.0f,0.0f,0.0f)),
	m_xpad()
{
	for (int i = 0; i < 3; i++)
	{
		m_select[i] = 0;
		m_pal[i] = 0;
	}
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneTitle::~SceneTitle()
{
	//���������
	DeleteGraph(m_backScene);
	DeleteGraph(m_start);
	DeleteGraph(m_setting);
	DeleteGraph(m_end);
	MV1DeleteModel(m_playerHandle);
	MV1DeleteModel(m_anim);
	setting->End();
	bgmse->End();
	se->End();

	handle.Clear();
}

/// <summary>
/// ����������
/// </summary>
void SceneTitle::Init()
{
	//�������ǂݍ���
	m_backScene = pui->MyLoadGraph("Data/SceneBack/PuppetNuclearTitleMini.png", 1, 1);     //144 KB (147,793 �o�C�g)
	m_start = pui->MyLoadGraph("Data/UI/STARTButtonMini.png", 1, 1);                       //27.1 KB (27,851 �o�C�g)
	m_setting = pui->MyLoadGraph("Data/UI/SettingButtonMini.png", 1, 1);                   //29.4 KB (30,170 �o�C�g)
	m_end = pui->MyLoadGraph("Data/UI/EndButtonMini.png", 1, 1);                           //22.5 KB (23,109 �o�C�g)

	m_playerHandle = handle.GetModelHandle("Data/Player/PuppetPlayerModel.mv1");
	m_anim = handle.GetModelHandle("Data/PlayerAnimation/JumpingDown.mv1");

	selectDecision = 0;

	//�A�j���[�V�����A�^�b�`
	m_animation = MV1AttachAnim(m_playerHandle, 1, m_anim, TRUE);

	//����
	m_totalAnimationTime = MV1GetAttachAnimTotalTime(m_playerHandle, m_animation);

	m_playTime = 28.0f;

	m_pos = VGet(485.0f, 0.0f, -800.0f);

	m_select[0] = 1;
	m_select[1] = 0;
	m_select[2] = 0;

	for (int i = 0; i < 3; i++)
	{
		m_pal[i] = 255;
	}

	m_cameraPos = VGet(550.0f, 20.0f, -450.0f);
	m_cameraTarget = VGet(485.0f, 80.0f, -550.0f);

	map->Init();

	//�ݒ�֌W
	setting->Init();
	bgmse->TitleInit();
	bgmse->TitleBGM();
	se->SceneInit();

	m_one = false;
	m_blend = false;
}

/// <summary>
/// �X�V����
/// </summary>
/// <returns>�V�[����Ԃ�</returns>
std::shared_ptr<SceneBase> SceneTitle::Update()
{
	if (setting->GetSettingScene() == false)
	{
		//�p�b�h���͏���
		GetJoypadXInputState(DX_INPUT_KEY_PAD1, &m_xpad);

		//��
		if (m_xpad.ThumbLY > 2000)
		{
			m_button++;
		}
		//��
		else if (m_xpad.ThumbLY < 0)
		{
			m_button--;
		}
		else
		{
			//������
			m_button = 0;

			m_one = false;
		}

		m_playTime += 0.5f;

		//�I������
		if (setting->GetSettingScene() == false)
		{
			pselect->Menu_Update(m_button, m_one, m_xpad.Buttons[12], selectDecision, pselect->Eight);
		}

		if (m_waitTime > 50)
		{
			//A�{�^������������
			if (m_xpad.Buttons[12] == 1)
			{
				PlaySoundMem(se->GetButtonSE(), DX_PLAYTYPE_BACK, true);

				//�Q�[���X�^�[�g
				if (selectDecision == 8)
				{
					return std::make_shared<SceneGame>();

					map->End();
				}
				//�ݒ�
				if (selectDecision == 9)
				{
					m_setButton = true;

					m_waitTime = 0;

					setting->SetSettingScene(m_setButton);
				}
				//�I��
				if (selectDecision == 10)
				{
					SetEnd(true);
				}
			}
		}
		else if(setting->GetSettingScene() == false)
		{
			m_waitTime++;
		}


		SelectBlend(7, 0, 1, 2);
		SelectBlend(8, 1, 0, 2);
		SelectBlend(9, 2, 1, 0);

	}
	//�ݒ���J��
	if (setting->GetSettingScene() == true)
	{
		setting->Update();
	}

	if (m_playTime >= m_totalAnimationTime && m_animation != -1)
	{
		m_playTime = 80.0f;
	}
	if (m_animation != -1)
	{
		MV1SetAttachAnimTime(m_playerHandle, m_animation, m_playTime);
	}

	bgmse->Update(setting->GetVolume());
	se->Update(setting->GetVolume());

	SetCameraPositionAndTarget_UpVecY(m_cameraPos, m_cameraTarget);

	return shared_from_this();  //���g�̃|�C���^��Ԃ�
}

/// <summary>
/// �I�𒆂̏ꍇ
/// </summary>
/// <param name="select">�񋓌^</param>
/// <param name="now">�I�����Ă����</param>
/// <param name="other1">����ȊO�P</param>
/// <param name="other2">����ȊO�Q</param>
void SceneTitle::SelectBlend(int select, int now, int other1, int other2)
{
	if (pselect->NowSelect == select)
	{
		if (m_blend == false)
		{
			if (m_pal[now] < 256)
			{
				m_pal[now] += 2;
			}
			else
			{
				m_blend = true;
			}

		}
		if (m_blend == true)
		{
			if (m_pal[now] > 125)
			{
				m_pal[now] -= 2;
			}
			else
			{
				m_blend = false;
			}
		}


		m_pal[other1] = 255;
		m_pal[other2] = 255;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void SceneTitle::Draw()
{

	map->Draw();

	MV1SetPosition(m_playerHandle, m_pos);

	MV1DrawModel(m_playerHandle);

	//3D���f���̉�]�n���Z�b�g����
	MV1SetRotationXYZ(m_playerHandle, VGet(0.0f, 160.0f, 0.0f));

	DrawGraph(120, 0, m_backScene, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_pal[0]);
	DrawGraph(500, 350, m_start, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_pal[1]);
	DrawGraph(500, 500, m_setting, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_pal[2]);
	DrawGraph(500, 650, m_end, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�ݒ��ʂ�`��
	if (setting->GetSettingScene() == true)
	{
		setting->Draw();
	}

	setting->SettingDraw(setting->GetVolume());

	if (setting->GetSettingScene() == false)
	{
		pselect->Draw();
	}
}

/// <summary>
/// �I������
/// </summary>
void SceneTitle::End()
{
	//���������
	DeleteGraph(m_backScene);
	DeleteGraph(m_start);
	DeleteGraph(m_setting);
	DeleteGraph(m_end);
	MV1DeleteModel(m_playerHandle);
	MV1DeleteModel(m_anim);
	setting->End();
	bgmse->End();
	se->End();

	handle.Clear();
}
