#include "ItemManager.h"
#include "Singleton/HandleManager.h"

namespace
{
	//シングルトン
	auto& handle = HandleManager::GetInstance();
}

ItemManager::ItemManager()
{
}

ItemManager::~ItemManager()
{
}

void ItemManager::Init()
{
}

void ItemManager::Update()
{
}

void ItemManager::Draw()
{
}

void ItemManager::End()
{
}
