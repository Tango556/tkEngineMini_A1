#include "stdafx.h"
#include "Player.h"

void Player::InitSkeleton()
{
	m_skeleton.Init("Assets/modelData/unityChan.tks");
}
void Player::InitModel()
{
	ModelInitData initData;
	//tkm�t�@�C���̃t�@�C���p�X���w�肷��B
	initData.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
	//�V�F�[�_�[�t�@�C���̃t�@�C���p�X���w�肷��B
	initData.m_fxFilePath = "Assets/shader/model.fx";
	//�m���X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w�肷��B
	initData.m_vsEntryPointFunc = "VSMain";
	//�X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w��B
	initData.m_vsSkinEntryPointFunc = "VSSkinMain";
	//�X�P���g�����w�肷��B
	initData.m_skeleton = &m_skeleton;
	//���f���̏�������w�肷��B
	//3dsMax�ł̓f�t�H���gZ�A�b�v�ɂȂ��Ă��邪�A
	//���j�e�B�����̓A�j���[�V������Y�A�b�v�ɕύX����Ă���B
	initData.m_modelUpAxis = enModelUpAxisY;

	//�쐬�����������f�[�^�����ƂɃ��f��������������A
	m_model.Init(initData);

	//�L�����R�����������B
	m_charaCon.Init(40.0f, 100.0f, g_vec3Zero);
}
void Player::InitAnimation()
{
	//�A�j���[�V�����N���b�v�����[�h����B
	m_animationClips[enAnimClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimClip_Run].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimClip_Run].SetLoopFlag(true);
	//�A�j���[�V�������������B
	m_animation.Init(
		m_skeleton,			//�A�j���[�V�����𗬂����ރX�P���g���B
		m_animationClips,	//�A�j���[�V�����N���b�v�B
		enAnimClip_Num		//�A�j���[�V�����̐��B
	);
}
bool Player::Start()
{
	//�X�P���g�������[�h�B
	InitSkeleton();
	//���f�����������B
	InitModel();
	//�A�j���[�V�������������B
	InitAnimation();

	return true;
}
void Player::Update()
{
	//�X�P���g�����X�V�B
	m_skeleton.Update(m_model.GetWorldMatrix());
	//�A�j���[�V������i�߂�B
	m_animation.Progress(g_gameTime->GetFrameDeltaTime());

	Vector3 moveSpeed;
	moveSpeed.x = g_pad[0]->GetLStickXF() * 1.0f;
	moveSpeed.z = g_pad[0]->GetLStickYF() * 1.0f;
	m_charaCon.Execute(moveSpeed, 1.0f);

	m_rot.AddRotationY(g_pad[0]->GetRStickXF() * 0.1f);
	m_model.UpdateWorldMatrix(m_charaCon.GetPosition(), m_rot, g_vec3One);
}
void Player::Render(RenderContext& rc)
{
	m_model.Draw(rc);
}
