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

struct SpotLight
{
	Vector3 SLigPosition;	//位置
	float pad0;				//パディング
	Vector3 SLigColor;		//カラー
	float SLigRange;		//影響範囲
	Vector3 SLigDirection;	//射出方向
	float SLigAngle;		//初出角度

	/// <summary>
	/// スポットライト位置セッター
	/// </summary>
	/// <param name="SLPos">位置座標</param>
	void SetSLigPos(Vector3 SLPos)
	{
		SLigPosition = SLPos;
	}

	/// <summary>
	/// スポットライトカラーセッター
	/// </summary>
	/// <param name="SLCol">ライトカラー</param>
	void SetSLigColor(Vector3 SLCol)
	{
		SLigColor = SLCol;
	}

	/// <summary>
	/// スポットライト影響範囲セッター
	/// </summary>
	/// <param name="SLRan">影響範囲指数</param>
	void SetSLigRan(float SLRan)
	{
		SLigRange = SLRan;
	}

	/// <summary>
	/// スポットライト射出方向セッター
	/// </summary>
	/// <param name="SLDir">射出方向</param>
	void SetSLigDir(Vector3 SLDir)
	{
		SLigDirection = SLDir;
		SLigDirection.Normalize();
	}

	/// <summary>
	/// スポットライト射出角セッター
	/// </summary>
	/// <param name="SLAng">射出角</param>
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