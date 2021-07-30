#include "stdafx.h"
#include "Hello2D.h"


bool Hello2D::Start()
{
	SpriteInitData initData;
	//DDS�t�@�C��(�摜�f�[�^)�̃t�@�C���p�X���w�肷��B
	initData.m_ddsFilePath[0] = "Assets/image/sample.dds";
	//Sprite�\���p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��B
	initData.m_fxFilePath = "Assets/shader/sprite.fx";
	//�X�v���C�g�̕��ƍ������w�肷��B
	initData.m_width = 200;
	initData.m_height = 200;
	//Sprite�������I�u�W�F�N�g���g�p���āASprite������������B
	m_sprite.Init( initData );

	return true;
}
void Hello2D::Update()
{
	m_sprite.Update(
		{ 400.0f, 0.0f, 0.0f },
		g_quatIdentity,
		g_vec3One);
}
void Hello2D::Render(RenderContext& rc)
{
	m_sprite.Draw(rc);
}