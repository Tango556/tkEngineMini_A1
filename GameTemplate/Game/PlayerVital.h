#pragma once

/// <summary>
/// �v���C���[��HP�A�X�^�~�i���̊Ǘ��p�N���X
/// </summary>
class PlayerVital
{
public:
	float GetMoveVelocity()
	{
		return m_moveVelocity;
	}
	float GetSprintMul()
	{
		return m_sprintMoveMul/*+ parkBuff*/;
	}

private:
	float m_playerLife = 100.0f;
	float m_parkLifeBuff = 0;
	float m_itemLifeBuff = 0;
	const float m_maxPlayerLife = 100.0f;
	float m_playerStamina = 100.0f;
	const float m_maxPlayerStamina = 100.0f;
	float m_moveVelocity = 7.0f;
	const float m_sprintMoveMul = 2.0f;
};