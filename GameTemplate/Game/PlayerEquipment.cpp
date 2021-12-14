#include "stdafx.h"
#include "PlayerEquipment.h"

PlayerEquipment::PlayerEquipment()
{

}
PlayerEquipment::~PlayerEquipment()
{

}
void PlayerEquipment::Init()
{
	SetWeapons(enPrimary, m_traveler);
}
void PlayerEquipment::SetWeapons(wep enAny, Weapons weapon)
{
	m_weapon[enAny] = weapon;
}
void PlayerEquipment::ChangeWeapons()
{
	if (holdWeapon == enPrimary)
	{
		holdWeapon = enSub;
	}
	else if (holdWeapon == enSub)
	{
		holdWeapon = enPrimary;
	}
}