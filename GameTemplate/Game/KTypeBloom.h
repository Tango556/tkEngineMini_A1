#pragma once
#include "GaussianBlur.h"
class KTypeBloom
{
private:
	/// @brief �P�x���o�pRenderTarget
	RenderTarget luminanceRenderTarget;
	/// @brief ���Z�����Ώ� : isAObject
	RenderTarget bloomTarget;
	/// @brief �P�x���o�p�̃X�v���C�g
	Sprite luminanceSprite;
	/// @brief ���Z������� : isASubject
	Sprite finalSprite;
	/// @brief �K�E�V�A���u���[
	GaussianBlur toBloomGaussianBlur[4];		
public:
	/// <summary>
	/// �������֐�
	/// </summary>
	/// <param name="renderTarget">���Z���������������_�[�^�[�Q�b�g</param>
	void Init(RenderTarget& RT);
	/// <summary>
	/// ���[�v���ōs������
	/// </summary>
	/// <param name="RT">�����_�[�^�[�Q�b�g</param>
	/// <param name="RC">�����_�[�R���e�L�X�g</param>
	void Updete(RenderTarget& RT, RenderContext& RC);
};

