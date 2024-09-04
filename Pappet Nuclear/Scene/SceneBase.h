#pragma once
#include "DxLib.h"
#include<memory>

class SceneBase : public std::enable_shared_from_this<SceneBase>
{
public:
	SceneBase():
		m_settingScene(false)
	{}

	virtual ~SceneBase(){}

	//virtual�Ōp������Ăяo��

	virtual void Init() = 0;
	virtual std::shared_ptr<SceneBase> Update() = 0;
	virtual void Draw() = 0;
	virtual void End() = 0;

	int MyLoadGraph(const char* FileName, int XSize, int YSize);

protected:
	//�ϐ�������
	int m_backScene = 0;
	bool m_settingScene;    //�ݒ肷�邽�߂̉�ʂ��Ăԕϐ�
};

