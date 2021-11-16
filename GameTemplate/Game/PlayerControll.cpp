#include "stdafx.h"
#include "PlayerControll.h"

Quaternion PlayerControll::Rotation()
{
	Quaternion playerRot;
	const Vector3 baseVector = { -1.0f, 0.0f, 0.0f };
	float SY = g_pad[0]->GetRStickYF();
	float SX = -g_pad[0]->GetRStickXF();
	Vector3 SXY = { SX,0.0f,SY };
	SXY.Normalize();
	float Ang = SXY.Dot(baseVector);
	Ang + 1.0f;
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
	float SY = -g_pad[0]->GetLStickYF();
	float SX = -g_pad[0]->GetLStickXF();
	Vector3 SXY = { SX, 0.0f, SY };
	SXY.Normalize();
	SXY.Scale(m_moveVelocity);
	return SXY;
}