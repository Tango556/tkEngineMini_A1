#pragma once

class PlayerControll
{
public:
	Quaternion Rotation();
	Vector3 Move();
	void SetMoveVelocity(float Velo)
	{
		m_moveVelocity = Velo;
	}

private:
	float m_moveVelocity;
	Quaternion m_plaeyrQua;
};

