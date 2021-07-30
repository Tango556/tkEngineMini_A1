#pragma once


class Player : public IGameObject
{
public:
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
private:
	/// <summary>
	/// スケルトンを初期化。
	/// </summary>
	void InitSkeleton();
	/// <summary>
	/// モデルを初期化。
	/// </summary>
	void InitModel();
	/// <summary>
	/// アニメーションを初期化。
	/// </summary>
	void InitAnimation();
private:
	/// <summary>
	/// アニメーションクリップ。
	/// </summary>
	enum EnAnimationClip {
		enAnimClip_Idle,
		enAnimClip_Run,
		enAnimClip_Num,
	};
	
	Model m_model;			//モデル表示処理。
	Animation m_animation;	//アニメション再生処理。
	AnimationClip m_animationClips[enAnimClip_Num];	//アニメーションクリップ。
	Skeleton m_skeleton;	//スケルトン。
	Quaternion m_rot;
	CharacterController m_charaCon;
};

