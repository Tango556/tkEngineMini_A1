#pragma once
#include"ModelLib.h"
class Bullet : public IGameObject
{
public:
	Bullet();
	~Bullet();
	void Update();
	bool Start();
	void Init(Vector3 pos, Quaternion rot, float dmg, float vel, int len, Light lig);
	float GetDamage()
	{
		return damage;
	};
	Vector3 GetPosition()
	{
		return position;
	}

private:
	float damage;
	float velocity;
	Vector3 Direction;
	Model m_model;
	int count;
	bool Inited = false;
	ModelLib* m_modelLib = new ModelLib;

	Vector3 position;
	Quaternion rotation;
	Vector3 scale = { 5.0f,5.0f,5.0f };

	Light m_lig;
};

