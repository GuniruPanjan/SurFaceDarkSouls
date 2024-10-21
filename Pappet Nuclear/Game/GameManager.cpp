#include "GameManager.h"
#include "Character/Player/Item/ItemManager.h"
#include "Character/Effect/Effect.h"

namespace
{
	int seSize;      //seの音量
	int a;         //ブレンド率

	std::shared_ptr<ItemManager> item = std::make_shared<ItemManager>();

	//シングルトン
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
