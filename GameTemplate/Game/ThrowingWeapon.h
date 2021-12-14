#pragma once
/// <summary>
/// 投擲武器の基底クラス
/// </summary>
class ThrowingWeapon
{
public:
	ThrowingWeapon() {};
	~ThrowingWeapon() {};
	/// <summary>
	/// モデル初期化
	/// </summary>
	virtual void Init() { return; }
	/// <summary>
	/// 投擲武器の使用
	/// </summary>
	/// <param name="direction">方向</param>
	/// <param name="power">投げる力</param>
	virtual void GrenadeOut(Vector3 direction, float power) { return; };
	/// <summary>
	/// 起爆,効果を発揮する
	/// </summary>
	virtual void Detonation() { return; };
	/// <summary>
	/// 雷管,効果を発揮するまでの条件(タイムラグや何かに当たった等)
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
/// 範囲内の敵に大ダメージを与える
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
/// 炸裂時範囲内の敵を行動不能に至らしめる
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
/// ダメージエリアを作れる
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
/// なにかに当たったとき極小さい範囲で敵を即死させる
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