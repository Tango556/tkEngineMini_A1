#pragma once

/// <summary>
/// �v���C���[�̈ړ��𐧌䂷��N���X
/// </summary>
class PlayerControll
{
public:
	Quaternion rotation();
	Quaternion SprintRotation();
	Vector3 Move();
	void SetMoveVelocity(float Velo)
	{
		m_moveVelocity = Velo;
	}
	bool IsSprint()
	{
		return m_sprint;
	}

private:
	float m_moveVelocity;
	Quaternion m_plaeyrQua;
	bool m_sprint = false;
};

