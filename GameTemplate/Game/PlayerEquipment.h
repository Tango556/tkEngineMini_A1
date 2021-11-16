#pragma once
#include "Weapons.h"

/// <summary>
/// 武器、投擲武器とメディカルキットの管理をするクラス
/// </summary>
class PlayerEquipment
{
private:
	int m_mediKit = 0;
	const int m_maxMediKit = 3;
	enum granade { enFlag, enStan, enMorotov, enTomahawk, enGrenadeVal };
	int m_Grenade[enGrenadeVal] = { 0,0,0,0 };
	const int m_maxGrenade = 3;
	enum wep {enPrimary, enSub, enVal};
	Weapons m_weapon[enVal];

public:
	PlayerEquipment();
	~PlayerEquipment();
	void m_maxMediKitBuff();
	void SetWeapons(wep enAny, Weapons weapon);
};

