#include "stdafx.h"
#include "Player.h"

Player::Player()
{

}

Player::~Player()
{
	for (int alpha = 0; alpha < enMVal; alpha++)
		delete(m_model);
}

void Player::Init(Light& lig)
{
	m_lig = lig;
	m_modelInitData[enModel].m_tkmFilePath = "Assets/modelData/AHuman.tkm";
	m_modelInitData[enModel].m_fxFilePath = "Assets/shader/model.fx";
	m_modelInitData[enModel].m_expandConstantBuffer = &m_lig;
	m_modelInitData[enModel].m_expandConstantBufferSize = sizeof(m_lig);
	m_modelInitData[enModel].m_collorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;
	m_modelInitData[enShadow].m_tkmFilePath = "Assets/modelData/AHuman.tkm";
	m_modelInitData[enShadow].m_fxFilePath = "Assets/shader/SampleDepthShadow.fx";
	m_modelInitData[enShadow].m_expandConstantBuffer = &m_lig;
	m_modelInitData[enShadow].m_expandConstantBufferSize = sizeof(m_lig);
	m_modelInitData[enShadow].m_collorBufferFormat[0] = DXGI_FORMAT_R32_FLOAT;

	m_model[enModel]->Init(m_modelInitData[enModel]);
	m_model[enShadow]->Init(m_modelInitData[enShadow]);

	m_equipment.SetWeapons(m_equipment.enPrimary, m_equipment.m_flawless);
}

void Player::Update(Light& lig)
{
	m_lig = lig;
	m_controller.SetMoveVelocity(GetSpeed());
	SetPosition(GetPosition() + m_controller.Move());
	SetRotation(m_controller.rotation());

	for (int alpha = 0; alpha < enMVal; alpha++)
	{
		m_model[alpha]->UpdateWorldMatrix(PlayerPos, PlayerRot, Scale);
	}
	if (g_pad[0]->IsTrigger(enButtonRB1))
	{
		m_bullet = NewGO<Bullet>(0);
		m_bullet->Init(PlayerPos + Vector3{0.0f, 200.0f, 10.0f}, PlayerRot, 0, 80.0f, 60, m_lig);
	}
}

/// <summary>
/// 影モデルを描画する関数
/// </summary>
/// <param name="cam">ライトカメラ</param>
void Player::ShadowDrower(Camera cam)
{
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	m_model[enShadow]->Draw(renderContext, cam);
}

void Player::ModelDrower()
{
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	m_model[enModel]->Draw(renderContext);
}

