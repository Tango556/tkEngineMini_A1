#include "stdafx.h"
#include "system/system.h"
#include "KTypeBloom.h"
#include "DepthShadow.h"



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
	
	Vector3 DLigDir = { 0.0f, -1.0f, 2.0f };

	DLig.SetColor({1.0f, 1.0f, 1.0f });
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
	ALig.SetAmbientLight(0.3f);

	

	/*Lig.ptColor.x = 15.0f;
	Lig.ptColor.y = 15.0f;
	Lig.ptColor.z = 15.0f;
	Lig.ptPosition.x = 0.0f;
	Lig.ptPosition.y = 50.0f;
	Lig.ptPosition.z = 50.0f;

	Lig.ptRange = 100.0f;*/

	/*Vector3 SunPosition = DLigDir;
	SunPosition.Normalize();
	SunPosition.Scale(6000.0f);

	Camera SunPerspective;
	SunPerspective.SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
	SunPerspective.SetPosition(SunPosition * -1.0f);
	SunPerspective.SetFar(10000.0f);
	SunPerspective.SetTarget({ 0.0f,0.0f,0.0f });
	SunPerspective.SetUp({ 0.0f,1.0f,0.0f });
	SunPerspective.SetWidth(4096);
	SunPerspective.SetHeight(4096);
	SunPerspective.Update();*/

	
	Light Lig;
	Lig.DLight = DLig;
	Lig.PLight = PLig;
	Lig.SLight = SLig;
	Lig.ALight = ALig;
	/*Lig.LV.SetPrjMatrix(SunPerspective.GetViewProjectionMatrix());*/
	DepthShadow DShadow;
	DShadow.Init(Lig);

	//RenderTarget shadowMapRT; //�V���h�E�}�b�v�����_�[�^�[�Q�b�g
	//float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//shadowMapRT.Create(
	//	4096,
	//	4096,
	//	1,
	//	1,
	//	DXGI_FORMAT_R32G32B32A32_FLOAT,
	//	DXGI_FORMAT_D32_FLOAT,
	//	clearColor
	//);

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

	uniSha.m_expandConstantBuffer = &Lig;
	uniSha.m_expandConstantBufferSize = sizeof(Lig);

	uniSha.m_collorBufferFormat[0] = DXGI_FORMAT_R32_FLOAT;

	ModelInitData BG;
	BG.m_tkmFilePath = "Assets/modelData/bg/bg.tkm";
	BG.m_fxFilePath = "Assets/shader/model.fx";
	BG.m_expandShaderResoruceView = &DShadow.GetShadowMap().GetRenderTargetTexture();

	BG.m_expandConstantBuffer = &Lig;
	BG.m_expandConstantBufferSize = sizeof(Lig);
	BG.m_collorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

	Uni.Init(uni);
	BackGround.Init(BG);
	UniSha.Init(uniSha);


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

	Quaternion DireLigRollerX;
	Quaternion DireLigRollerY;

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
		
		DireLigRollerX.SetRotationDeg(Vector3::AxisX, g_pad[0]->GetRStickYF());
		DireLigRollerY.SetRotationDeg(Vector3::AxisY, g_pad[0]->GetRStickXF());
		DireLigRollerX.Multiply(DireLigRollerY);

		DireLigRollerX.Apply(DLigDir);
		DLig.SetDirection(DLigDir);

		//DirRota.SetRotation(Vector3::AxisX, DirAng);
		//DirRota.Apply(DLigDir);

		//DLig.SetDirection(DLigDir);
		Vector3 AdditionColor;

		DLig.SetEyePos();

		Lig.DLight = DLig;
		Lig.PLight = PLig;
		Lig.SLight = SLig;
		DShadow.Update(Lig);

		renderContext.WaitUntilToPossibleSetRenderTarget(DShadow.GetShadowMap());
		renderContext.SetRenderTargetAndViewport(DShadow.GetShadowMap());
		renderContext.ClearRenderTargetView(DShadow.GetShadowMap());

		UniSha.Draw(renderContext, DShadow.GetCamera());

		renderContext.WaitUntilFinishDrawingToRenderTarget(DShadow.GetShadowMap());
		/*DShadow.DrawShadow(uniSha, renderContext);*/

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

		kBloom.Updete(mainRenderTarget);

		renderContext.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);
		
		copyToFrameBufferSprite.Draw(renderContext);
		

		GameObjectManager::GetInstance()->ExecuteUpdate();
		GameObjectManager::GetInstance()->ExecuteRender(renderContext);
		
		
		//////////////////////////////////////
		//�G��`���R�[�h�������̂͂����܂ŁI�I�I
		//////////////////////////////////////
		g_engine->EndFrame();
	}
	//�Q�[���I�u�W�F�N�g�}�l�[�W���[���폜�B
	GameObjectManager::DeleteInstance();
	return 0;
}

