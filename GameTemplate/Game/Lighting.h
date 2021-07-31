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
	/// <param name="Dir">ライト方向</param>
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
	/// <summary>
	/// ライトポジションセッター
	/// </summary>
	/// <param name="PLigPos">ポイントライトの座標</param>
	void SetPLigPos(Vector3 PLigPos)
	{
		PLigPosition = PLigPos;
	}
	/// <summary>
	/// カラーセッター
	/// </summary>
	/// <param name="PLigCor">カラー</param>
	void SetColor(Vector3 PLigCor)
	{
		PLigColor = PLigCor;
	}
	/// <summary>
	/// 影響範囲セッター
	/// </summary>
	/// <param name="Ran">影響範囲の値</param>
	void SetRange(float Ran)
	{
		Range = Ran;
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