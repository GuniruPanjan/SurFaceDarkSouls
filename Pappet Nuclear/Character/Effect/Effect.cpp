#include "Effect.h"
#include <cassert>

Effect* Effect::m_instance = nullptr;

Effect::~Effect()
{
	//�����p�X�̃G�t�F�N�g�����[�h����Ă��Ȃ����m�F����
	for (auto& effect : m_effect)
	{
		DeleteEffekseerEffect(effect.second->emitterHandle);
	}
}

/// <summary>
/// �G�t�F�N�g���[�h
/// </summary>
/// <param name="name">�G�t�F�N�g�̖��O</param>
/// <param name="path">���[�h���邽�߂̃p�X</param>
/// <param name="endFrame">�I���t���[��</param>
/// <param name="scale">�g�嗦</param>
void Effect::EffectLoad(std::string name, const char* path, int endFrame, float scale)
{
	//�����p�X�̃G�t�F�N�g�����[�h����Ă��Ȃ����m�F����
	for (auto& effect : m_effect)
	{
		if (effect.second->effectPath == path)
		{
			return;
		}
	}

	//�����܂ŗ����烍�[�h����
	std::shared_ptr<EffectEmitter> add = std::make_shared<EffectEmitter>();
	add->emitterHandle = LoadEffekseerEffect(path, scale);
	assert(add->emitterHandle != -1 && "�G�t�F�N�g���[�h���s");
	add->endFrame = endFrame;

	m_effect[name] = add;
}

/// <summary>
/// �X�V
/// </summary>
void Effect::Update()
{

	Effekseer_Sync3DSetting();


	UpdateEffekseer3D();

	//�G�t�F�N�g�̍X�V
	for (auto& effects : m_effect)
	{
		for (auto& ef : effects.second->effects)
		{
			if (ef.frame > effects.second->endFrame)
			{
				StopEffekseer3DEffect(ef.handle);
				ef.isExist = false;
			}

			ef.frame++;
		}

		//isExist��false�̃I�u�W�F�N�g���폜
		auto it = std::remove_if(effects.second->effects.begin(), effects.second->effects.end(), [](auto& v)
			{
				return v.isExist = false;
			});
		effects.second->effects.erase(it, effects.second->effects.end());
	}
}

/// <summary>
/// �`��
/// </summary>
void Effect::Draw()
{
	DrawEffekseer3D();
}

/// <summary>
/// �G�t�F�N�g�𐶐�
/// </summary>
/// <param name="name">�G�t�F�N�g�̖��O</param>
/// <param name="pos">�`����W</param>
void Effect::EffectCreate(std::string name, VECTOR pos)
{
	int handle = -1;
	for (auto& effects : m_effect)
	{
		if (effects.first == name)
		{
			handle = effects.second->emitterHandle;
		}
	}

	//�ǉ����悤�Ƃ����G�t�F�N�g�̖��O�̃n���h�����Ȃ���ΏI���
	if (handle == -1)
	{
		return;
	}

	Effectstruct add;
	add.handle = PlayEffekseer3DEffect(handle);
	add.frame = 0;
	add.x = pos.x;
	add.y = pos.y;
	add.z = pos.z;
	add.isExist = true;

	SetPosPlayingEffekseer3DEffect(add.handle, add.x, add.y, add.z);

	m_effect[name]->effects.emplace_back(add);

	return;
}
