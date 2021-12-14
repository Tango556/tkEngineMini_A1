#pragma once
#include "Weapons.h"
#include "ThrowingWeapon.h"

/// <summary>
/// ����A��������ƃ��f�B�J���L�b�g�̊Ǘ�������N���X
/// </summary>
class PlayerEquipment
{
public:
	enum wep { enPrimary, enSub, enVal };

	//����
	M65_Flawless m_flawless;
	Traveler_9mm m_traveler;
	//��������
	FlagGrenade m_flag;
	StanGrenade m_stan;
	MorotovCocktail m_morotov;
	TomahawkAxe m_tomahawk;
private:
	int m_mediKit = 0;
	const int m_maxMediKit = 3;
	enum grenade { enFlag, enStan, enMorotov, enTomahawk, enGrenadeVal };
	ThrowingWeapon m_throwingWeapon[enGrenadeVal];
	grenade holdGrenade = enFlag;
	int m_Grenade[enGrenadeVal] = { 0,0,0,0 };
	const int m_maxGrenade = 3;
	
	Weapons m_weapon[enVal];
	wep holdWeapon = enPrimary;

	
public:
	PlayerEquipment();
	~PlayerEquipment();
	
	void Init();
	void SetWeapons(wep enAny, Weapons weapon);
	void ChangeWeapons();
	//void ChangeGrenade();
	int GetMediKitNum()
	{
		return m_mediKit;
	};
	int GetGranedeValu(grenade enAny)
	{
		return m_Grenade[enAny];
	};
};

