#include "GameManager.h"
#include "Character/Player/Item/ItemManager.h"
#include "Character/Effect/Effect.h"

namespace
{
	int seSize;      //se�̉���
	int a;         //�u�����h��

	std::shared_ptr<ItemManager> item = std::make_shared<ItemManager>();

	//�V���O���g��
	auto& effect = Effect::GetInstance();
}

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

void GameManager::Init()
{
}

void GameManager::Update()
{
}

void GameManager::FirstUpdate()
{
}

void GameManager::SecondUpdate()
{
}

void GameManager::ThreeUpdate()
{
}

void GameManager::FourUpdate()
{
}

void GameManager::LastUpdate()
{
}

void GameManager::RestUpdate()
{
}

void GameManager::Draw()
{
}

void GameManager::End()
{
}
