#pragma once
/// <summary>
/// ��������̊��N���X
/// </summary>
class ThrowingWeapon
{
public:
	ThrowingWeapon() {};
	~ThrowingWeapon() {};
	/// <summary>
	/// ���f��������
	/// </summary>
	virtual void Init() { return; }
	/// <summary>
	/// ��������̎g�p
	/// </summary>
	/// <param name="direction">����</param>
	/// <param name="power">�������</param>
	virtual void GrenadeOut(Vector3 direction, float power) { return; };
	/// <summary>
	/// �N��,���ʂ𔭊�����
	/// </summary>
	virtual void Detonation() { return; };
	/// <summary>
	/// ����,���ʂ𔭊�����܂ł̏���(�^�C�����O�≽���ɓ���������)
	/// </summary>
	virtual void Detonator() { return; };

	ThrowingWeapon& operator=(const ThrowingWeapon& obj);
protected:
	Model m_model;
	Stopwatch m_watch;
	Vector3 m_throwDirection;
	float m_throwPower;
	const float m_range = 0;
	const float m_maxDamage = 0;
};

/// <summary>
/// �͈͓��̓G�ɑ�_���[�W��^����
/// </summary>
class FlagGrenade : public ThrowingWeapon
{
public:
	FlagGrenade();
	~FlagGrenade();
	void Init();
	void GrenadeOut(Vector3 direction, float power);
	void Detonation();
	void Detonator();
private:
	Model m_model;
	Stopwatch m_watch;
	Vector3 m_throwDirection;
	float m_throwPower;
	const float m_range = 20.0f;
	const float m_maxDamage = 700.0f;
};

/// <summary>
/// �y�􎞔͈͓��̓G���s���s�\�Ɏ��炵�߂�
/// </summary>
class StanGrenade : public ThrowingWeapon
{
public:
	StanGrenade();
	~StanGrenade();
	void Init();
	void GrenadeOut(Vector3 direction, float power);
	void Detonation();
	void Detonator();
private:
	Model m_model;
	Stopwatch m_watch;
	Vector3 m_throwDirection;
	float m_throwPower;
	const float m_range = 40.0f;
	const float m_maxDamage = 10.0f;
};

/// <summary>
/// �_���[�W�G���A������
/// </summary>
class MorotovCocktail : public ThrowingWeapon
{
public:
	MorotovCocktail();
	~MorotovCocktail();
	void Init();
	void GrenadeOut(Vector3 direction, float power);
	void Detonation();
	void Detonator();
private:
	Model m_model;
	Stopwatch m_watch;
	Vector3 m_throwDirection;
	float m_throwPower;
	const float m_range = 35.0f;
	const float m_maxDamage = 15.0f;
};

/// <summary>
/// �Ȃɂ��ɓ��������Ƃ��ɏ������͈͂œG�𑦎�������
/// </summary>
class TomahawkAxe : public ThrowingWeapon
{
public:
	TomahawkAxe();
	~TomahawkAxe();
	void Init();
	void GrenadeOut(Vector3 direction, float power);
	void Detonation();
	void Detonator();
private:
	Model m_model;
	Stopwatch m_watch;
	Vector3 m_throwDirection;
	float m_throwPower;
	const float m_range = 2.0f;
	const float m_maxDamage = 9999.0f;
};