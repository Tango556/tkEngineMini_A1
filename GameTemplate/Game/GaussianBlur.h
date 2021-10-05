#pragma once

/// <summary>
/// �K�E�V�A���u���[�N���X
/// </summary>
class GaussianBlur {
public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="originalTexture">�K�E�V�A���u���[��������I���W�i���e�N�X�`��</param>
	void Init(Texture* originalTexture);
	/// <summary>
	/// �K�E�V�A���u���[��GPU��Ŏ��s
	/// </summary>
	/// <param name="renCon">�����_�����O�^�[�Q�b�g</param>
	/// <param name="blurPower">�u���[���x�B�l���傫���قǋ����Ȃ�</param>
	void ExevuteOnGPU(RenderContext& renCon, float blurPower);
	/// <summary>
	/// �ڂ������e�N�X�`�����擾
	/// </summary>
	/// <returns></returns>
	Texture& GetBlurredTexture()
	{
		return m_yBlurRenderTarget.GetRenderTargetTexture();
	}
private:
	/// <summary>
	/// �����_�����O�^�[�Q�b�g��������
	/// </summary>
	void InitRenderTargets();
	/// <summary>
	/// �X�v���C�g��������
	/// </summary>
	void InitSprites();
	/// <summary>
	/// �d�݃e�[�u�����X�V����
	/// </summary>
	/// <param name="blurPower"></param>
	void UpdateWeightTable(float blurPower);
private:
	enum{NUM_WEIGHTS = 8};
	float m_weights[NUM_WEIGHTS];
	Texture* m_originalTexture = nullptr;
	RenderTarget m_xBlurRenderTarget;
	RenderTarget m_yBlurRenderTarget;
	Sprite m_xBlurSprite;
	Sprite m_yBlurSprite;
};

