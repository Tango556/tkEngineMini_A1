#pragma once

/// <summary>
/// プレイヤーのHP、スタミナ等の管理用クラス
/// </summary>
class PlayerVital
{
public:
	float GetMoveVelocity()
	{
		return m_moveVelocity;
	}

private:
	float m_playerLife = 100.0f;
	float m_parkLifeBuff = 0;
	float m_itemLifeBuff = 0;
	const float m_maxPlayerLife = 100.0f;
	float m_playerStamina = 100.0f;
	const float m_maxPlayerStamina = 100.0f;
	float m_moveVelocity = 5.0f;
};