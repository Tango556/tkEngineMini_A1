#pragma once
#include "stdafx.h"
#include <math.h>

struct DirectionLight
{
	Vector3 ligDirection = Vector3::Zero;
	float pad0 = 0.0f;
	Vector3 DirColor = Vector3::Zero;
	float pad1 = 0.0f;
	Vector3 eyePos = Vector3::Zero;
	float pad2 = 0.0f;
	/// <summary>
	/// �f�B���N�V�����Z�b�^�[
	/// </summary>
	/// <param name="Dir">���C�g����</param>
	void SetDirection(const Vector3 Dir)
	{
		ligDirection = Dir;
		ligDirection.Normalize();
	}

	/// <summary>
	/// �J���[�Z�b�^�[
	/// </summary>
	/// <param name="Cor">�J���[</param>
	void SetColor(const Vector3 Cor)
	{
		DirColor = Cor;
	}
};

struct PointLight
{
	Vector3 PLigPosition = Vector3::Zero;
	float pad = 0.0f;
	Vector3 PLigColor = Vector3::Zero;
	float Range = 0.0f;
	/// <summary>
	/// ���C�g�|�W�V�����Z�b�^�[
	/// </summary>
	/// <param name="PLigPos">�|�C���g���C�g�̍��W</param>
	void SetPLigPos(Vector3 PLigPos)
	{
		PLigPosition = PLigPos;
	}
	/// <summary>
	/// �J���[�Z�b�^�[
	/// </summary>
	/// <param name="PLigCor">�J���[</param>
	void SetColor(Vector3 PLigCor)
	{
		PLigColor = PLigCor;
	}
	/// <summary>
	/// �e���͈̓Z�b�^�[
	/// </summary>
	/// <param name="Ran">�e���͈͂̒l</param>
	void SetRange(float Ran)
	{
		Range = Ran;
	}
};

struct SpotLight
{
	Vector3 SLigPosition;	//�ʒu
	float pad0;				//�p�f�B���O
	Vector3 SLigColor;		//�J���[
	float SLigRange;		//�e���͈�
	Vector3 SLigDirection;	//�ˏo����
	float SLigAngle;		//���o�p�x

	/// <summary>
	/// �X�|�b�g���C�g�ʒu�Z�b�^�[
	/// </summary>
	/// <param name="SLPos">�ʒu���W</param>
	void SetSLigPos(Vector3 SLPos)
	{
		SLigPosition = SLPos;
	}

	/// <summary>
	/// �X�|�b�g���C�g�J���[�Z�b�^�[
	/// </summary>
	/// <param name="SLCol">���C�g�J���[</param>
	void SetSLigColor(Vector3 SLCol)
	{
		SLigColor = SLCol;
	}

	/// <summary>
	/// �X�|�b�g���C�g�e���͈̓Z�b�^�[
	/// </summary>
	/// <param name="SLRan">�e���͈͎w��</param>
	void SetSLigRan(float SLRan)
	{
		SLigRange = SLRan;
	}

	/// <summary>
	/// �X�|�b�g���C�g�ˏo�����Z�b�^�[
	/// </summary>
	/// <param name="SLDir">�ˏo����</param>
	void SetSLigDir(Vector3 SLDir)
	{
		SLigDirection = SLDir;
		SLigDirection.Normalize();
	}

	/// <summary>
	/// �X�|�b�g���C�g�ˏo�p�Z�b�^�[
	/// </summary>
	/// <param name="SLAng">�ˏo�p</param>
	void SetSLigAng(float SLAng)
	{
		SLigAngle = Math::DegToRad(SLAng);
	}
};

struct AmbientLight {
	float Light;
	Vector3 VPad;
};

struct Light
{
	DirectionLight DLight;
	PointLight PLight;
	SpotLight SLight;
	AmbientLight ALight;
};

class Lighting : public IGameObject
{
private:
	DirectionLight DLig;
	PointLight PLig;
	SpotLight SLig;
	AmbientLight Alig;
public:
	
};