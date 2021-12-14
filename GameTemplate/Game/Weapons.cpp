#include "stdafx.h"
#include "Weapons.h"

void Weapons::FiringPin()
{
	
}
void Weapons::Reload()
{

}
void Weapons::Bolt()
{

}
void Weapons::Trigger()
{

}
Weapons& Weapons::operator=(Weapons& obj)
{
	return obj;
}

void Traveler_9mm::FiringPin()
{
	if (Chamber == false)
		return;

	m_bullet = NewGO<Bullet>(0, "Bullet");
	//m_bullet->Init(m_position, m_rotation, Damage, BulletVelocity,range, );
	Chamber = false;
}
void Traveler_9mm::Reload()
{
	//if (Ammo == GetMaxAmmo()) return;
	Ammo = GetMaxAmmo();
}
void Traveler_9mm::Bolt()
{
	if (Chamber == true)
	{
		return;
	}
	FiringDelay -= 1;
	if (FiringDelay <= 0)
	{
		Chamber = true;
	}
}
void Traveler_9mm::Trigger()
{

}
int Traveler_9mm::GetMaxAmmo()
{
	return maxAmmo + levelAdditionAmmo;
}

void M65_Flawless::FiringPin()
{
	m_bullet = NewGO<Bullet>(0, "Bullet");
	//m_bullet->Init(m_position, m_rotation, Damage, BulletVelocity, range);
}
void M65_Flawless::Reload()
{
	Ammo = GetMaxAmmo();
}
int M65_Flawless::GetMaxAmmo()
{
	return maxAmmo + levelAdditionAmmo;
}