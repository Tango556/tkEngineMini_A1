#include "stdafx.h"
#include "PlayerControll.h"

Quaternion PlayerControll::rotation()
{
	if (IsSprint())
	{
		return SprintRotation();
	}
	Quaternion playerRot;
	const Vector3 baseVector = { -1.0f, 0.0f, 0.0f };
	float SY = g_pad[0]->GetRStickYF();
	float SX = -g_pad[0]->GetRStickXF();
	Vector3 SXY = { SX,0.0f,SY };
	SXY.Normalize();
	float Ang = SXY.Dot(baseVector);
	Ang *= 90.0f;
	if (SY >= 0)
	{
		Ang += 180.0f;
	}
	else Ang *= -1.0f;
	playerRot.SetRotationDegY(Ang);

	if (SY == 0 && SX == 0) return m_plaeyrQua;

	playerRot.CopyTo(m_plaeyrQua);

	return m_plaeyrQua;
}

Vector3 PlayerControll::Move()
{
	if (g_pad[0]->IsTrigger(enButtonLB3))
	{
		m_sprint = !m_sprint;
	}
	float SY = -g_pad[0]->GetLStickYF();
	float SX = -g_pad[0]->GetLStickXF();
	Vector3 SXY = { SX, 0.0f, SY };
	SXY.Normalize();
	float inputAmount = SXY.Length();
	if (m_sprint)
	{
		inputAmount = 1.0f;
	}
	if (SY == 0.0f && SX == 0.0f)
	{
		m_sprint = false;
	}
	SXY.Scale(m_moveVelocity * inputAmount);

	return SXY;
}

Quaternion PlayerControll::SprintRotation()
{
	float SY = g_pad[0]->GetLStickYF();
	float SX = -g_pad[0]->GetLStickXF();
	Vector3 SXY = { SX, 0.0f, SY };

	Quaternion playerRot;

	const Vector3 baseVector = { -1.0f, 0.0f, 0.0f };

	float Ang = SXY.Dot(baseVector);
	Ang *= 90.0f;

	if (SY >= 0)
	{
		Ang += 180.0f;
	}
	else Ang *= -1.0f;
	playerRot.SetRotationDegY(Ang);

	return playerRot;
}