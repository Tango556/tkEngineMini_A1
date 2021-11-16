#pragma once
class Weapons
{
public:
	virtual void Fire();
	virtual void Reload();
};

namespace WeaponLib
{
	class P45_traveler : public Weapons
	{
	public:
		void Fire();
		void Reload();
	};
}