#include "stdafx.h"
#include "system/system.h"
#include "KTypeBloom.h"



///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	//////////////////////////////////////
	// �������珉�������s���R�[�h���L�q����B
	//////////////////////////////////////

	//�Q�[���I�u�W�F�N�g�}�l�[�W���[�̃C���X�^���X���쐬����B
	GameObjectManager::CreateInstance();
	PhysicsWorld::CreateInstance();

	//g_camera3D->SetPosition(0.0f, 300.0f, 20.0f);

	//DirectionLight dirLig;
	//dirLig.SetDirection({ 1.0f, -1.0f, -1.0f });
	////���K������
	//dirLig.ligDirection.Normalize();

	//dirLig.SetColor({ 1.0f,1.0f,1.0f });

	//dirLig.eyePos = g_camera3D->GetPosition();

	RenderTarget mainRenderTarget;
	mainRenderTarget.Create(
		1280,
		720,
		1,
		1,
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		DXGI_FORMAT_D32_FLOAT
	);
	//g_camera3D->SetPosition(0.0f, 10000.0f, 0.0001f);
	g_camera3D->SetFar(100000.0f);

	DirectionLight DLig;
	
	Vector3 DLigDir = { 0.0f, -1.0f, -0.5f };

	DLig.SetColor({ 1.6f, 1.6f, 1.6f });
	DLig.SetDirection(DLigDir);
	
	PointLight PLig;
	
	/*PLig.SetColor({ 40.0f, 10.0f, 10.0f });
	PLig.SetPLigPos({ 0.0f, 15.0f, 0.0f });
	PLig.SetRange(30.0f);*/

	SpotLight SLig;
	/*SLig.SetSLigColor({ 15.0f,15.0f,15.0f });
	SLig.SetSLigPos({ 0.0f, 300.0f, 0.0f });
	SLig.SetSLigAng(30.0f);
	SLig.SetSLigRan(1000.0f);
	SLig.SetSLigDir({ 0.0f, -1.0f, 0.0f });*/


	AmbientLight ALig;
	ALig.SetAmbientLight(0.15f);

	

	/*Lig.ptColor.x = 15.0f;
	Lig.ptColor.y = 15.0f;
	Lig.ptColor.z = 15.0f;
	Lig.ptPosition.x = 0.0f;
	Lig.ptPosition.y = 50.0f;
	Lig.ptPosition.z = 50.0f;

	Lig.ptRange = 100.0f;*/

	Vector3 SunPosition = DLigDir;
	SunPosition.Normalize();
	SunPosition.Scale(6000.0f);

	Camera SunPerspective;
	SunPerspective.SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
	SunPerspective.SetPosition(SunPosition * -1.0f);
	SunPerspective.SetFar(10000.0f);
	SunPerspective.SetTarget({ 0.0f,0.0f,0.0f });
	SunPerspective.SetUp({ 0.0f,1.0f,0.0f });
	SunPerspective.SetWidth(1024);
	SunPerspective.SetHeight(1024);
	SunPerspective.Update();

	//g_camera3D = &SunPerspective;
	//Camera MAUEView;	//�^�㎋�_
	//MAUEView.SetPosition(0.0f, 2000.0, 0.01f);
	//MAUEView.SetTarget(0.0f, 0.0f, 0.0f);
	//MAUEView.SetFar(10000.0f);
	//MAUEView.Update();

	//g_camera3D = &MAUEView;

	Light Lig;
	Lig.DLight = DLig;
	Lig.PLight = PLig;
	Lig.SLight = SLig;
	Lig.ALight = ALig;
	Lig.LV.SetPrjMatrix(SunPerspective.GetViewProjectionMatrix());


	RenderTarget shadowMapRT; //�V���h�E�}�b�v�����_�[�^�[�Q�b�g
	float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	shadowMapRT.Create(
		2048,
		2048,
		1,
		1,
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		DXGI_FORMAT_D32_FLOAT,
		clearColor
	);

	Model Uni;
	Model UniSha;
	Model BackGround;

	ModelInitData uni;
	uni.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
	uni.m_fxFilePath = "Assets/shader/model.fx";
	//uni.m_expandShaderResoruceView = &shadowMapRT.GetRenderTargetTexture();
	uni.m_expandConstantBuffer = &Lig;
	uni.m_expandConstantBufferSize = sizeof(Lig);
	uni.m_collorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

	ModelInitData uniSha;
	uniSha.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
	uniSha.m_fxFilePath = "Assets/shader/SampleDepthShadow.fx";
	uniSha.m_psEntryPointFunc = "PSMain";

	//uniSha.m_expandConstantBuffer = &Lig;
	//uniSha.m_expandConstantBufferSize = sizeof(Lig);

	uniSha.m_collorBufferFormat[0] = DXGI_FORMAT_R32_FLOAT;

	ModelInitData BG;
	BG.m_tkmFilePath = "Assets/modelData/bg/bg.tkm";
	BG.m_fxFilePath = "Assets/shader/model.fx";
	BG.m_expandShaderResoruceView = &shadowMapRT.GetRenderTargetTexture();

	BG.m_expandConstantBuffer = &Lig;
	BG.m_expandConstantBufferSize = sizeof(Lig);
	BG.m_collorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

	Uni.Init(uni);
	UniSha.Init(uniSha);
	BackGround.Init(BG);
	/*
	//�P�x���o�p�����_�����O�^�[�Q�b�g���쐬
	RenderTarget luminanceRenderTarget;

	//�𑜓x�A�~�j�}�b�v���x��
	luminanceRenderTarget.Create(
		1280,
		720,
		1,
		1,
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		DXGI_FORMAT_D32_FLOAT
	);

	//�P�x���o�p�̃X�v���C�g��������
	//�����������쐬����
	SpriteInitData luminanceSpriteInitData;

	//�P�x���o�p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��
	luminanceSpriteInitData.m_fxFilePath = "Assets/shader/posteffects.fx";

	//���_�V�F�[�_�[�̃G���g���[�|�C���g���w��
	luminanceSpriteInitData.m_vsEntryPointFunc = "VSMain";
	
	//�s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g���w�肷��
	luminanceSpriteInitData.m_psEntryPointFunc = "PSSamplingLuminance";

	//�X�v���C�g�̕��ƍ�����luminannceRenderTarget�Ɠ���
	luminanceSpriteInitData.m_width = 1280;
	luminanceSpriteInitData.m_height = 720;

	// �e�N�X�`���̓��C�������_�����O�^�[�Q�b�g�̃J���[�o�b�t�@�[
	luminanceSpriteInitData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();

	//�`�����ރ����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g���w�肷��
	luminanceSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

	//�쐬�����������������ƂɃX�v���C�g������������
	Sprite luminanceSprite;
	luminanceSprite.Init(luminanceSpriteInitData);

	//�K�E�V�A���u���[��������
	GaussianBlur toBloomGaussianBlur[4];
	//gaussianBlur[0]�͋P�x�e�N�X�`���ɃK�E�V�A���u���[��������B
	toBloomGaussianBlur[0].Init(&luminanceRenderTarget.GetRenderTargetTexture());
	//gaussianBlur[1]��gaussianBlur[0]�e�N�X�`���ɃK�E�V�A���u���[��������
	toBloomGaussianBlur[1].Init(&toBloomGaussianBlur[0].GetBlurredTexture());
	toBloomGaussianBlur[2].Init(&toBloomGaussianBlur[1].GetBlurredTexture());
	toBloomGaussianBlur[3].Init(&toBloomGaussianBlur[2].GetBlurredTexture());

	//�{�P�摜���������ĕ`�����ނ��߂̃X�v���C�g��������
	//����������ݒ肷
	SpriteInitData finalSpriteInitData;
	finalSpriteInitData.m_textures[0] = &toBloomGaussianBlur[0].GetBlurredTexture();
	finalSpriteInitData.m_textures[1] = &toBloomGaussianBlur[1].GetBlurredTexture();
	finalSpriteInitData.m_textures[2] = &toBloomGaussianBlur[2].GetBlurredTexture();
	finalSpriteInitData.m_textures[3] = &toBloomGaussianBlur[3].GetBlurredTexture();

	//�𑜓x��mainRenderTarget�̕��ƍ���
	finalSpriteInitData.m_width = 1280;
	finalSpriteInitData.m_height = 720;
	//�{�P�摜����������K�v������̂Ő�p�V�F�[�_�[���w��B
	finalSpriteInitData.m_fxFilePath = "Assets/shader/posteffects.fx";
	finalSpriteInitData.m_psEntryPointFunc = "PSBloomFinal";

	//���������Z�����ŕ`�悷��̂ŁA�A���t�@�u�����f�B���O���[�h�ɉ��Z�ɂ���
	finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;
	//�J���[�o�b�t�@�̃t�H�[�}�b�g��32bitFloatingPoint�o�b�t�@
	finalSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

	//�������������ɉ��Z�����p�̃X�v���C�g������������B
	Sprite finalSprite;
	finalSprite.Init(finalSpriteInitData);
	*/
	//mainRenderTarget�̃e�N�X�`�����t���[���o�b�t�@�[�ɓ\��t���邽�߂̃X�v���C�g������������
	//�X�v���C�g�̏������I�u�W�F�N�g���쐬����B
	



	SpriteInitData spriteInitData;

	//�e�N�X�`����mainRenderTarget�̃J���[�o�b�t�@�[
	spriteInitData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
	spriteInitData.m_width = 1280;
	spriteInitData.m_height = 720;

	//���m�N���p�̃V�F�[�_�[���w�肷��
	spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";

	Sprite copyToFrameBufferSprite;
	copyToFrameBufferSprite.Init(spriteInitData);	

	KTypeBloom kBloom;
	kBloom.Init(mainRenderTarget);

	Vector3 SligPos = SLig.GetSLigPos();


	//////////////////////////////////////
	// ���������s���R�[�h�������̂͂����܂ŁI�I�I
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	


	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		//�����_�����O�J�n�B
		g_engine->BeginFrame();
		
		//////////////////////////////////////
		//��������G��`���R�[�h���L�q����B
		//////////////////////////////////////
		
		SLig.SetSLigPos({ SLig.GetSLigPos().x - g_pad[0]->GetLStickXF(),SLig.GetSLigPos().y, SLig.GetSLigPos().z });
		if (g_pad[0]->IsPress(enButtonB)) {
			SLig.SetSLigPos({ SLig.GetSLigPos().x, SLig.GetSLigPos().y, SLig.GetSLigPos().z + g_pad[0]->GetLStickYF() });
		}
		else {			
			SLig.SetSLigPos({ SLig.GetSLigPos().x, SLig.GetSLigPos().y + g_pad[0]->GetLStickYF(),SLig.GetSLigPos().z });
		}


		//DirRota.SetRotation(Vector3::AxisX, DirAng);
		//DirRota.Apply(DLigDir);

		//DLig.SetDirection(DLigDir);
		Vector3 AdditionColor;

		DLig.SetEyePos();

		Lig.DLight = DLig;
		Lig.PLight = PLig;
		Lig.SLight = SLig;

		renderContext.WaitUntilToPossibleSetRenderTarget(shadowMapRT);
		renderContext.SetRenderTargetAndViewport(shadowMapRT);
		renderContext.ClearRenderTargetView(shadowMapRT);
		UniSha.Draw(renderContext, SunPerspective);
		renderContext.WaitUntilFinishDrawingToRenderTarget(shadowMapRT);


		//�����_�����O�^�[�Q�b�g��mainRenderTarget�ɕύX����
		//�����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂�
		renderContext.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
		//�����_�����O�^�[�Q�b�g��ݒ�
		renderContext.SetRenderTargetAndViewport(mainRenderTarget);
		//�����_�����O�^�[�Q�b�g���N���A
		renderContext.ClearRenderTargetView(mainRenderTarget);

		Uni.Draw(renderContext);
		BackGround.Draw(renderContext);

		renderContext.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);
		//renderContext.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);

		//���f���`��
		

		/*
		//�P�x���o
		//�P�x���o�p�̃����_�����O�^�[�Q�b�g�ɕύX
		renderContext.WaitUntilToPossibleSetRenderTarget(luminanceRenderTarget);
		//�����_�����O�^�[�Q�b�g�ɐݒ�
		renderContext.SetRenderTargetAndViewport(luminanceRenderTarget);
		//�����_�����O�^�[�Q�b�g���N���A
		renderContext.ClearRenderTargetView(luminanceRenderTarget);
		//�P�x���o���s��
		luminanceSprite.Draw(renderContext);
		//�����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
		renderContext.WaitUntilFinishDrawingToRenderTarget(luminanceRenderTarget);
		//�K�E�V�A���u���[��4����s����
		toBloomGaussianBlur[0].ExecuteOnGPU(renderContext, 10);
		toBloomGaussianBlur[1].ExecuteOnGPU(renderContext, 10);
		toBloomGaussianBlur[2].ExecuteOnGPU(renderContext, 10);
		toBloomGaussianBlur[3].ExecuteOnGPU(renderContext, 10);

		//�{�P�摜���������ă����_�����O�^�[�Q�b�g�ɉ��Z����
		//�����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂�
		renderContext.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
		//�����_�����O�^�[�Q�b�g��ݒ�
		renderContext.SetRenderTargetAndViewport(mainRenderTarget);
		//�ŏI����
		finalSprite.Draw(renderContext);
		*/
		//�����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
		//renderContext.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);
		

		kBloom.Updete(mainRenderTarget, renderContext);

		renderContext.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);

		

		
		copyToFrameBufferSprite.Draw(renderContext);
		

		//GameObjectManager::GetInstance()->ExecuteUpdate();
		//GameObjectManager::GetInstance()->ExecuteRender(renderContext);
		
		
		//////////////////////////////////////
		//�G��`���R�[�h�������̂͂����܂ŁI�I�I
		//////////////////////////////////////
		g_engine->EndFrame();
	}
	//�Q�[���I�u�W�F�N�g�}�l�[�W���[���폜�B
	GameObjectManager::DeleteInstance();
	return 0;
}

