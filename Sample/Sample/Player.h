#pragma once


class Player : public IGameObject
{
public:
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
private:
	/// <summary>
	/// �X�P���g�����������B
	/// </summary>
	void InitSkeleton();
	/// <summary>
	/// ���f�����������B
	/// </summary>
	void InitModel();
	/// <summary>
	/// �A�j���[�V�������������B
	/// </summary>
	void InitAnimation();
private:
	/// <summary>
	/// �A�j���[�V�����N���b�v�B
	/// </summary>
	enum EnAnimationClip {
		enAnimClip_Idle,
		enAnimClip_Run,
		enAnimClip_Num,
	};
	
	Model m_model;			//���f���\�������B
	Animation m_animation;	//�A�j���V�����Đ������B
	AnimationClip m_animationClips[enAnimClip_Num];	//�A�j���[�V�����N���b�v�B
	Skeleton m_skeleton;	//�X�P���g���B
	Quaternion m_rot;
	CharacterController m_charaCon;
};

