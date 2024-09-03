#pragma once
#include "SceneBase.h"
#define SCREEN_W         640       //�摜�̉���
#define SCREEN_H         480       //�摜�̗���
#define DOWN_SCALE       8         //�K�E�X�t�B���^���|����摜����ʂ̃T�C�Y�̉�����1��
#define DOWN_SCALE_SCREEN_W   (SCREEN_W / DOWN_SCALE)     //�K�E�X�t�B���^���|����摜�̉���
#define DOWN_SCALE_SCREEN_H   (SCREEN_H / DOWN_SCALE)     //�K�E�X�t�B���^���|���闧��


class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update();
	virtual void Draw();
	virtual void End();

private:
	//Pad���͏����ϐ�
	int m_pad;

	int ColorScreeen = 0;  //���ʂ̕`�挋�ʂ��������ރX�N���[��
	int HighBringhtScreen = 0;  //���ʂ̕`�挋�ʂ��獂�P�x�����𔲂��o�������ʂ��������ރX�N���[��
	int DownScaleScreen = 0;    //���P�x�������k���������ʂ��������ރX�N���[��
	int GaussScreen = 0;    //�k���摜���K�E�X�t�B���^�łڂ��������ʂ��������ރX�N���[��

};