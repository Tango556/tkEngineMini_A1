#pragma once
class PlayerCamera
{
private:
	Vector3 eyePosition;
	Vector3 targetPosition;
	Vector3 targetDistance;
	float maxFar = 10000.0f;
	float maxNear = 0.05f;

public:
	void SetTarget(Vector3 t);
	void SetPosition(Vector3 p);
	void SetDistance(Vector3 d);
	void Update();
	void SetFar(float f);
	void SetNear(float n);
};

