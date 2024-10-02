#include "HandleManager.h"
#include "DxLib.h"
#include<cassert>

HandleManager* HandleManager::m_instance = nullptr;

namespace
{
	//���f���̃n���h��
	int m_weakEnemyHandle;
	int m_bossEnemyHandle;
	int m_playerHandle;
}

HandleManager::HandleManager()
{
	//m_weakEnemyHandle = MV1LoadModel("Data/Enemy/EnemyModel.mv1");
	//m_bossEnemyHandle = MV1LoadModel("Data/Enemy/BossEnemy.mv1");
	//m_playerHandle = MV1LoadModel("Data/Player/PuppetPlayerModel.mv1");
}

HandleManager::~HandleManager()
{
	for (auto& h : m_handles)
	{
		MV1DeleteModel(h.handle);
	}

	m_handles.clear();
}

int HandleManager::GetModelHandle(std::string path, bool isEternal)
{
	//���łɃ��[�h����Ă����畡���n���h����Ԃ�
	for (auto& h : m_handles)
	{
		if (h.path == path)
		{
			return MV1DuplicateModel(h.handle);
		}
	}

	//���[�h����Ă��Ȃ�������
	Handle add;
	add.handle = MV1LoadModel(path.c_str());
	add.path = path;
	add.isEternal = isEternal;

	m_handles.emplace_back(add);

	//���[�h�����n���h���̕����n���h����Ԃ�
	return MV1DuplicateModel(add.handle);
}

void HandleManager::Clear()
{
	//isEternal��false�̃n���h����Delete����
	for (auto& h : m_handles)
	{
		if (!h.isEternal)
		{
			MV1DeleteModel(h.handle);
			h.handle = 0;
		}
	}

	//�s�v�ɂȂ����n���h���������ō폜��������
	auto it = remove_if(m_handles.begin(), m_handles.end(), []
	(auto& v) {
			return v.handle == 0;
		       });

	m_handles.erase(it, m_handles.end());
}
