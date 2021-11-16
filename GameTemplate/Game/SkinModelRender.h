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
	/// �A�j���[�V�����������Ȃ����f���̏�����
	/// </summary>
	/// <param name="tkmFilePath">�h���[������tkm�t�@�C���̃p�X</param>
	/// <param name="SC">���̎Օ����Ƃ���</param>
	/// <param name="SR">�e�̓��e���Ƃ���</param>
	void Init(const char tkmFilePath[], const bool SC, const bool SR);

	/// <summary>
	/// �w����W�Ƀ��f����������
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(const Vector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	///	�����̃x�N�g�����A���f�����ړ�������
	/// </summary>
	/// <param name="vec">�ړ���</param>
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

