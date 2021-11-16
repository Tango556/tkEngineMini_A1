#pragma once
#include"Lighting.h"
#include"DepthShadow.h"

class SkinModelRender : public IGameObject
{
public:
	SkinModelRender();

	~SkinModelRender();

	bool Start();

	void Update();
	/// <summary>
	/// アニメーション等をしないモデルの初期化
	/// </summary>
	/// <param name="tkmFilePath">ドローしたいtkmファイルのパス</param>
	/// <param name="SC">光の遮蔽物とする</param>
	/// <param name="SR">影の投影物とする</param>
	void Init(const char tkmFilePath[], const bool SC, const bool SR);

	/// <summary>
	/// 指定座標にモデルをおける
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(const Vector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	///	引数のベクトル分、モデルを移動させる
	/// </summary>
	/// <param name="vec">移動量</param>
	void AddVector(const Vector3 vec)
	{
		m_position + vec;
	}

	void SetQuaternion(const Quaternion qua)
	{
		m_rotation = qua;
	}

	void SetScale(const Vector3 sca)
	{
		m_scale = sca;
	}
	void Render(RenderContext& renderContext);

private:
	enum{enModel,enShadow,enVal};
	Model m_model[enVal];
	ModelInitData m_mInitData[enVal];
	DepthShadow m_Shadow;
	Lighting* m_Lighting;
	bool m_shadowCaster = false;
	bool m_shadowReceiver = false;
	Vector3 m_position;
	Quaternion m_rotation;
	Vector3 m_scale = { 1.0f,1.0f,1.0f };
};

