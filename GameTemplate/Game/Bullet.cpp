#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet()
{

}
Bullet::~Bullet()
{

}
void Bullet::Update()
{
	Vector3 ballistic;
	ballistic = Direction;
	ballistic.Normalize();
	ballistic.Scale(velocity);

	position += ballistic;
	count -= 1;
	if (count <= 0)
	{
		DeleteGO(this);
	}
	auto& renderContext = g_graphicsEngine->GetRenderContext();
	m_model.UpdateWorldMatrix(position, rotation, scale);
	m_model.Draw(renderContext);
}
bool Bullet::Start()
{
	return Inited;
}
void Bullet::Init(Vector3 pos, Quaternion rot, float dmg, float vel, int len, Light lig)
{
	m_lig = lig;
	ModelInitData bulletModel;
	bulletModel.m_tkmFilePath = "Assets/modelData/Bullet.tkm";
	bulletModel.m_fxFilePath = "Assets/shader/model.fx";
	bulletModel.m_expandConstantBuffer = &m_lig;
	bulletModel.m_expandConstantBufferSize = sizeof(m_lig);
	bulletModel.m_collorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;
	m_model.Init(bulletModel);
	//m_modelLib = FindGO<ModelLib>("modelLib");

	//m_model = m_modelLib->GetModel(ModelLib::enTeapot);
	position = pos;
	rotation = rot;

	damage = dmg;
	velocity = vel;
	Vector3 dir;
	dir = Vector3::Front;
	rot.Apply(dir);
	Direction = dir;
	count = len;

	Inited = true;
}