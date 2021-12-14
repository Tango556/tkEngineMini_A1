#pragma once
#include "PlayerVital.h"
#include "PlayerEquipment.h"
#include "PlayerControll.h"
#include "Lighting.h"
#include "PlayerCamera.h"
#include "Bullet.h"

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
	Vector3 GetPosition()
	{
		return PlayerPos;
	}
	Quaternion GetRotation()
	{
		return PlayerRot;
	}
	float GetSpeed()
	{
		if (m_controller.IsSprint())
		{
			return m_vital.GetMoveVelocity() * m_vital.GetSprintMul();
		}
		return m_vital.GetMoveVelocity();
	}
	bool IsSprint()
	{
		return m_controller.IsSprint();
	}

private:
	enum {enModel,enShadow,enMVal};

	//プレイヤー用のモデル。enModelでスキンモデル、enShadowでシャドーモデル
	Model* m_model[enMVal] = { new Model, new Model };
	PlayerCamera m_playerCamera;
	Vector3 ComDistance = { 0.0f, 1000.0f, 400.0f };
	ModelInitData m_modelInitData[enMVal];
	PlayerControll m_controller;
	PlayerVital m_vital;
	PlayerEquipment m_equipment;
	Bullet* m_bullet = nullptr;
	Vector3 PlayerPos;
	Quaternion PlayerRot;
	const Vector3 Scale = { 1.0f,1.0f,1.0f };

	Light m_lig;
};

