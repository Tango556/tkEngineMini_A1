#pragma once
#include "stdafx.h"
#include <math.h>

Camera SunPerspective;


struct DirectionLight
{
private:
	Vector3 ligDirection = Vector3::Zero;
	float pad0 = 0.0f;
	Vector3 DirColor = Vector3::Zero;
	float pad1 = 0.0f;
	Vector3 eyePos = Vector3::Zero;
	float pad2 = 0.0f;
public:
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

	void SetEyePos()
	{
		eyePos = g_camera3D->GetPosition();
	}

	Vector3 GetDirection()
	{
		return ligDirection;
	}
};

struct PointLight
{
private:
	Vector3 PLigPosition = Vector3::Zero;
	float pad = 0.0f;
	Vector3 PLigColor = Vector3::Zero;
	float Range = 0.0f;
public:
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

	Vector3 GetPLigPos()
	{
		return PLigPosition;
	}
};


struct SpotLight
{
private:
	Vector3 SLigPosition;	//�ʒu
	float pad0;				//�p�f�B���O
	Vector3 SLigColor;		//�J���[
	float SLigRange;		//�e���͈�
	Vector3 SLigDirection;	//�ˏo����
	float SLigAngle;		//���o�p�x
public:
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

	Vector3 GetSLigPos()
	{
		return SLigPosition;
	}
};

struct AmbientLight {
private:
	Vector3 LightColor;
	float Pad1;
public:
	/// <summary>
	/// �����Z�b�^�[
	/// </summary>
	/// <param name="lig">�����J���[</param>
	void SetAmbientLight(Vector3 lig)
	{
		LightColor = lig;
	}
	/// <summary>
	/// �����Z�b�^�[
	/// </summary>
	/// <param name="lig">�������x</param>
	void SetAmbientLight(float lig)
	{
		LightColor = { lig, lig, lig };
	}
};

struct LightView {
private:
	Matrix rightProjectionView;
public:
	void SetPrjMatrix(const Matrix& cam)
	{
		rightProjectionView = cam;
	}
};

struct Light
{
	DirectionLight DLight;
	PointLight PLight;
	SpotLight SLight;
	AmbientLight ALight;
	LightView LV;
};

class Lighting
{
private:
	DirectionLight DLig[10];
	PointLight PLig[50];
	SpotLight SLig[50];
	AmbientLight Alig;
public:
	
};