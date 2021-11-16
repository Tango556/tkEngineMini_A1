#pragma once
#include "PlayerVital.h"
#include "PlayerEquipment.h"
#include "PlayerControll.h"
#include "Lighting.h"

/// <summary>
/// プレイヤー
/// </summary>
class Player
{
public:
	Player();
	~Player();
	void Init(Light& lig);
	void Update(Light& lig);
	void ShadowDrower(Camera cam);
	void ModelDrower();
	void SetPosition(Vector3 pos)
	{
		PlayerPos = pos;
	}
	void SetRotation(Quaternion rot)
	{
		PlayerRot = rot;
	}
	Vector3 GetPositon()
	{
		return PlayerPos;
	}
	Quaternion GetRotation()
	{
		return PlayerRot;
	}
	float GetSpeed()
	{
		return m_vital.GetMoveVelocity();
	}

private:
	enum {enModel,enShadow,enMVal};

	//プレイヤー用のモデル。enModelでスキンモデル、enShadowでシャドーモデル
	Model* m_model[enMVal] = { new Model, new Model };
	ModelInitData m_modelInitData[enMVal];
	PlayerControll m_controller;
	PlayerVital m_vital;
	Vector3 PlayerPos;
	Quaternion PlayerRot;
	const Vector3 Scale = { 1.0,1.0,1.0 };
};

