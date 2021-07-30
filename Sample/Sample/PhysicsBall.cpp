#include "stdafx.h"
#include "PhysicsBall.h"

bool PhysicsBall::Start() 
{
	//モデルを初期化。
	ModelInitData initData;
	initData.m_tkmFilePath = "Assets/modelData/ball.tkm";
	initData.m_fxFilePath = "Assets/shader/model.fx";
	m_model.Init(initData);

	//コライダーを初期化。
	m_sphereCollider.Create(10.0f);
	
	//剛体を初期化。
	RigidBodyInitData rbInitData;
	//質量を設定する。
	rbInitData.mass = 3.0f;
	rbInitData.collider = &m_sphereCollider;
	rbInitData.pos.y = 100.0f;
	//回転のしやすさを設定する。0～1
	rbInitData.localInteria.Set(
		0.5f, 
		0.5f, 
		0.5f
	);
	m_rigidBody.Init(rbInitData);
	//摩擦力を設定する。0～10
	m_rigidBody.SetFriction(10.0f);
	//線形移動する要素を設定する。
	//0を指定した軸は移動しない。
	m_rigidBody.SetLinearFactor(1.0f, 1.0f, 0.0f);
	return true;
}
void PhysicsBall::Update()
{
	//剛体の座標と回転を取得。
	Vector3 pos;
	Quaternion rot;
	m_rigidBody.GetPositionAndRotation(pos, rot);
	//剛体の座標と回転をモデルに反映。
	m_model.UpdateWorldMatrix(pos, rot, g_vec3One);
	//剛体に力を加える。
	Vector3 force;
	force.x = -g_pad[0]->GetLStickXF() * 500.0f;
	force.z = -g_pad[0]->GetLStickYF() * 500.0f;
	//力を加える
	m_rigidBody.AddForce(
		force,		//力
		g_vec3Zero	//力を加える剛体の相対位置
	);

	
	Vector3 toCamere = g_camera3D->GetPosition() - g_camera3D->GetTarget();
	g_camera3D->SetTarget(pos);
	toCamere.y = 100.0f;
	g_camera3D->SetPosition(pos + toCamere);
}
void PhysicsBall::Render(RenderContext& rc)
{
	m_model.Draw(rc);
}
