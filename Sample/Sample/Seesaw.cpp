#include "stdafx.h"
#include "Seesaw.h"

bool Seesaw::Start()
{
	//���f�����������B
	ModelInitData initData;
	initData.m_tkmFilePath = "Assets/modelData/seesaw.tkm";
	initData.m_fxFilePath = "Assets/shader/model.fx";
	m_model.Init(initData);

	//�R���C�_�[���������B
	Vector3 size;
	size.x = 100.0f;
	size.y = 10.0f;
	size.z = 40.0f;
	
	m_boxCollider.Create(size);

	//���̂��������B
	RigidBodyInitData rbInitData;
	//���ʂ�ݒ肷��B
	rbInitData.mass = 10.0f;
	rbInitData.collider = &m_boxCollider;
	rbInitData.pos.y = 20.0f;
	//��]�̂��₷����ݒ肷��B
	//�����G���W���C���̉�]�͂��Ȃ��̂ŁA�S���̎�0�ɂ���B
	rbInitData.localInteria.Set(0.0f, 0.0f, 0.0f);
	m_rigidBody.Init(rbInitData);
	//���C�͂�ݒ肷��B
	m_rigidBody.SetFriction(10.0f);
	//���`�ړ�����v�f��ݒ肷��B
	//�V�[�\�[�͓����Ȃ��̂őS���̎���0�ɂ���B
	m_rigidBody.SetLinearFactor(0.0f, 0.0f, 0.0f);
	//�G���W���C����
	m_rigidBody.SetAngularFactor(0.0f, 0.0f, 0.0f);
	return true;
}
void Seesaw::Render(RenderContext& rc)
{
	m_model.Draw(rc);
}

void Seesaw::Update()
{
	//���̂̍��W�Ɖ�]���擾�B
	static Vector3 angularVel = { 0.0f, 0.0f, 0.0f };

	Vector3 pos;
	Quaternion rot;
	m_rigidBody.GetPositionAndRotation(pos, rot);
	auto rb = m_rigidBody.GetBody();

	if (fabsf(g_pad[0]->GetRStickXF()) > 0.0f) {
		angularVel.Set(0.0f, 0.0f, g_pad[0]->GetRStickXF() * 2.0f);

	}
	//���X�Ɍ���
	angularVel *= 0.98f;

	m_rigidBody.SetAngularVelocity(angularVel);
	
	//���̂̍��W�Ɖ�]�����f���ɔ��f�B
	m_model.UpdateWorldMatrix(pos, rot, g_vec3One);
}
