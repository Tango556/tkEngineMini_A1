#include "stdafx.h"
#include "KTypeBloom.h"

void KTypeBloom::Init(RenderTarget& RT)
{
	bloomTarget = RT;

	luminanceRenderTarget.Create(
		1280,
		720,
		1,
		1,
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		DXGI_FORMAT_D32_FLOAT
	);

	//�P�x���o�p�X�v���C�g�̏��������
	SpriteInitData luminanceSpriteInitData;
	//�P�x���o�p�V�F�[�_�[�̃t�@�C���p�X���w��
	luminanceSpriteInitData.m_fxFilePath = "Assets/shader/posteffects.fx";
	//���_�V�F�[�_�[�̃G���g���[�|�C���g���w��
	luminanceSpriteInitData.m_vsEntryPointFunc = "VSMain";

	//���_�V�F�[�_�[�̃G���g���[�|�C���g���w��
	luminanceSpriteInitData.m_psEntryPointFunc = "PSSamplingLuminance";

	//�X�v���C�g�̕��ƍ�����luminanceRenderTarget�Ɠ���
	luminanceSpriteInitData.m_width = 1280;
	luminanceSpriteInitData.m_height = 720;

	//�e�N�X�`����BlurTarget�̃J���[�o�b�t�@
	luminanceSpriteInitData.m_textures[0] = &bloomTarget.GetRenderTargetTexture();

	//�`�����ރ����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g���w�肷��
	luminanceSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

	//�쐬�����������������ɃX�v���C�g������������
	luminanceSprite.Init(luminanceSpriteInitData);
	
	//toBloomGaussianBlur[0]�͋P�x�e�N�X�`���ɃK�E�V�A���u���[��������
	toBloomGaussianBlur[0].Init(&luminanceRenderTarget.GetRenderTargetTexture());
	//toBloomGaussianBlur[1]��toBloomGaussianBlur[0]�̃e�N�X�`���ɃK�E�V�A���u���[��������
	toBloomGaussianBlur[1].Init(&toBloomGaussianBlur[0].GetBlurredTexture());
	toBloomGaussianBlur[2].Init(&toBloomGaussianBlur[1].GetBlurredTexture());
	toBloomGaussianBlur[3].Init(&toBloomGaussianBlur[2].GetBlurredTexture());

	//�u���[�h�摜���������ĕ`�����ނ��߂̃X�v���C�g��������
	SpriteInitData finalSpriteInitData;
	finalSpriteInitData.m_textures[0] = &toBloomGaussianBlur[0].GetBlurredTexture();
	finalSpriteInitData.m_textures[1] = &toBloomGaussianBlur[1].GetBlurredTexture();
	finalSpriteInitData.m_textures[2] = &toBloomGaussianBlur[2].GetBlurredTexture();
	finalSpriteInitData.m_textures[3] = &toBloomGaussianBlur[3].GetBlurredTexture();

	//�𑜓x��bloomTarget�̕��ƍ���
	finalSpriteInitData.m_width = 1280;
	finalSpriteInitData.m_height = 720;
	//�u���[�h�摜����������K�v������̂Ő�p�V�F�[�_�[���w��
	finalSpriteInitData.m_fxFilePath = "Assets/shader/posteffects.fx";
	finalSpriteInitData.m_psEntryPointFunc = "PSBloomFinal";
	
	//���������Z�����ŕ`�悷��̂ŁA�A���t�@�u�����f�B���O���[�h�ɉ��Z�ɂ���
	finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;
	//�J���[�o�b�t�@�̃t�H�[�}�b�g��32bitFloatingPoint�o�b�t�@
	finalSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

	//���Z������̂̃X�v���C�g��������
	finalSprite.Init(finalSpriteInitData);
}

void KTypeBloom::Updete(RenderTarget& RT, RenderContext& RC)
{
	//�P�x���o
	//�P�x���o�p�̃����_�����O�^�[�Q�b�g�ɕύX
	RC.WaitUntilToPossibleSetRenderTarget(luminanceRenderTarget);
	//�����_�����O�^�[�Q�b�g�ɐݒ�
	RC.SetRenderTargetAndViewport(luminanceRenderTarget);
	//�����_�����O�^�[�Q�b�g���N���A
	RC.ClearRenderTargetView(luminanceRenderTarget);
	//�P�x���o���s��
	luminanceSprite.Draw(RC);
	//�����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
	RC.WaitUntilFinishDrawingToRenderTarget(luminanceRenderTarget);
	//�K�E�V�A���u���[��4����s����
	toBloomGaussianBlur[0].ExecuteOnGPU(RC, 10);
	toBloomGaussianBlur[1].ExecuteOnGPU(RC, 10);
	toBloomGaussianBlur[2].ExecuteOnGPU(RC, 10);
	toBloomGaussianBlur[3].ExecuteOnGPU(RC, 10);

	//�u���[�h�摜�������������_�����O�^�[�Q�b�g�ɉ��Z����
	//�����_�����O�^�[�Q�b�g�ւ̏������ݏI���܂�
	RC.WaitUntilToPossibleSetRenderTarget(RT);
	//�����_�����O�^�[�Q�b�g��ݒ�
	RC.SetRenderTargetAndViewport(RT);
	//�ŏI����
	finalSprite.Draw(RC);
	//�����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
	//RC.WaitUntilFinishDrawingToRenderTarget(RT);
}