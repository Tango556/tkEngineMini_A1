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
	/// ディレクションセッター
	/// </summary>
	/// <param name="Dir"></param>
	void SetDirection(const Vector3 Dir)
	{
		ligDirection = Dir;
		ligDirection.Normalize();
	}

	/// <summary>
	/// カラーセッター
	/// </summary>
	/// <param name="Cor">カラー</param>
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

	void SetPLigPos(Vector3 PLigPos, Vector3 PLigCol, float Ran)
	{
		PLigPosition = PLigPos;
		PLigColor = PLigCol;
		Range = Ran;
	}

	void SetPosition(Vector3 PLigPos)
	{
		PLigPosition = PLigPos;
	}
};

struct Light
{
	DirectionLight DLight;
	PointLight PLight;
};

class Lighting : public IGameObject
{
	DirectionLight DLig;
	PointLight PLig;
	//SpotLight SLig;	*予定*
public:
	
};