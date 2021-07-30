#include "stdafx.h"
#include "Background.h"

bool Background::Start()
{
	ModelInitData initData;
	initData.m_tkmFilePath = "Assets/modelData/bg/bg2.tkm";
	//�V�F�[�_�[�t�@�C���̃t�@�C���p�X���w�肷��B
	initData.m_fxFilePath = "Assets/shader/model.fx";
	//���_�V�F�[�_�[�̃G���g���[�|�C���g
	initData.m_vsEntryPointFunc = "VSMain";
	m_model.Init(initData);

	//���b�V���R���C�_�[���쐬�B
	m_physicsStaticObject.CreateFromModel(m_model, m_model.GetWorldMatrix());
	m_physicsStaticObject.SetFriction(10.0f);
	return true;
}
void Background::Update()
{

}
void Background::Render(RenderContext& rc)
{
	m_model.Draw(rc);
}