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

	Vector3 GetPLigPos()
	{
		return PLigPosition;
	}
};


struct SpotLight
{
private:
	Vector3 SLigPosition;	//位置
	float pad0;				//パディング
	Vector3 SLigColor;		//カラー
	float SLigRange;		//影響範囲
	Vector3 SLigDirection;	//射出方向
	float SLigAngle;		//初出角度
public:
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
	/// 環境光セッター
	/// </summary>
	/// <param name="lig">環境光カラー</param>
	void SetAmbientLight(Vector3 lig)
	{
		LightColor = lig;
	}
	/// <summary>
	/// 環境光セッター
	/// </summary>
	/// <param name="lig">環境光強度</param>
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