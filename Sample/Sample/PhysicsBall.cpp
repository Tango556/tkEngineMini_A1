#include "stdafx.h"
#include "PhysicsBall.h"

bool PhysicsBall::Start() 
{
	//���f�����������B
	ModelInitData initData;
	initData.m_tkmFilePath = "Assets/modelData/ball.tkm";
	initData.m_fxFilePath = "Assets/shader/model.fx";
	m_model.Init(initData);

	//�R���C�_�[���������B
	m_sphereCollider.Create(10.0f);
	
	//���̂��������B
	RigidBodyInitData rbInitData;
	//���ʂ�ݒ肷��B
	rbInitData.mass = 3.0f;
	rbInitData.collider = &m_sphereCollider;
	rbInitData.pos.y = 100.0f;
	//��]�̂��₷����ݒ肷��B0�`1
	rbInitData.localInteria.Set(
		0.5f, 
		0.5f, 
		0.5f
	);
	m_rigidBody.Init(rbInitData);
	//���C�͂�ݒ肷��B0�`10
	m_rigidBody.SetFriction(10.0f);
	//���`�ړ�����v�f��ݒ肷��B
	//0���w�肵�����͈ړ����Ȃ��B
	m_rigidBody.SetLinearFactor(1.0f, 1.0f, 0.0f);
	return true;
}
void PhysicsBall::Update()
{
	//���̂̍��W�Ɖ�]���擾�B
	Vector3 pos;
	Quaternion rot;
	m_rigidBody.GetPositionAndRotation(pos, rot);
	//���̂̍��W�Ɖ�]�����f���ɔ��f�B
	m_model.UpdateWorldMatrix(pos, rot, g_vec3One);
	//���̂ɗ͂�������B
	Vector3 force;
	force.x = -g_pad[0]->GetLStickXF() * 500.0f;
	force.z = -g_pad[0]->GetLStickYF() * 500.0f;
	//�͂�������
	m_rigidBody.AddForce(
		force,		//��
		g_vec3Zero	//�͂������鍄�̂̑��Έʒu
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
