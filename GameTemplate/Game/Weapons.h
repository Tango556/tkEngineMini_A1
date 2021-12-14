#pragma once
#include "Bullet.h"
#include <vector>

class Weapons// : public IGameObject
{
private:
	virtual void FiringPin();
	virtual void Bolt();
public:
	//virtual void Receiver();
	virtual void Trigger();
	virtual void Reload();	
	virtual void SetPosition(Vector3 pos) {};
	virtual void SetRotation(Quaternion rot) {};
	virtual int GetMaxAmmo() { return 0; }
	Weapons& operator=(Weapons& obj);
protected:
	const wchar_t* Name;
	bool Chamber = true;
	float Damage = 0;
	float BulletVelocity = 0;
	float Agirity = 0;
	float Spread = 0;
	float CriticalDamageMultiply = 0;
	float CriticalRate = 0;
	int FiringDelay = 0;
	int Penetration = 0;
	int Pellet = 0;
	int maxAmmo = 0;
	int levelAdditionAmmo = 0;
	int range = 0;
	const int ReloadTime = 0;
	int Cost = 0;
	int level = 0;
	Bullet* m_bullet = nullptr;
	enum enFireMode
	{
		enSingle,enAuto,enVal
	};
	enFireMode fireMode = enSingle;

	Vector3 m_position;
	Quaternion m_rotation;
};


class Traveler_9mm : public Weapons
{
private:
	void FiringPin();
	void Bolt();
public:
	void Trigger();
	void Reload();
	virtual void SetPosition(Vector3 pos) {};
	virtual void SetRotation(Quaternion rot) {};
	int GetMaxAmmo();
private:
	const wchar_t* Name = L"Traveler_9mm";
	bool Chamber = true;
	float Damage = 20;
	float BulletVelocity = 40.0f;
	float Agirity = 1.0f;
	float Spread = 8.0f;
	float CriticalDamageMultiply = 2.0f;
	float CriticalRate = 0.2f;
	const int DFiringDeley = 8;
	int FiringDelay = 8;
	int Penetration = 2;
	int Pellet = 1;
	int Ammo = 12;
	const int maxAmmo = 12;
	int levelAdditionAmmo = 0;
	int range = 30;
	const int ReloadTime = 80;
	int Cost = 0;
	int level = 0;
	Bullet* m_bullet = nullptr;
	enFireMode fireMode = enSingle;

	Vector3 m_position;
	Quaternion m_rotation;
};

class M65_Flawless : public Weapons
{
private:
	void FiringPin();
	//void Bolt();
public:
	//void Trigger();
	void Reload();
	virtual void SetPosition(Vector3 pos) {};
	virtual void SetRotation(Quaternion rot) {};
	int GetMaxAmmo();
private:
	const wchar_t* Name = L"M65_Flawless";
	bool Chamber = true;
	float Damage = 28;
	float BulletVelocity = 60.0f;
	float Agirity = 0.8f;
	float Spread = 2.0f;
	float CriticalDamageMultiply = 2.2f;
	float CriticalRate = 0.4f;
	int FiringDelay = 12.0f;
	int Penetration = 4;
	int Pellet = 1;
	int Ammo = 30;
	const int maxAmmo = 30;
	int range = 50;
	const int ReloadTime = 150;
	int Cost = 3400;
	int level = 0;
	Bullet* m_bullet = nullptr;
	enFireMode fireMode = enAuto;

	Vector3 m_position;
	Quaternion m_rotation;
};