#include "stdafx.h"
#include "system/system.h"
#include "KTypeBloom.h"
#include "DepthShadow.h"
#include "ModelLib.h"
#include "Player.h"

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
	
	Vector3 DLigDir = { 0.2f, -1.0f, 0.8f };

	DLig.SetColor({1.f, 1.0f, 1.05f });
	DLig.SetDirection(DLigDir);
	
	PointLight PLig;

	SpotLight SLig;

	AmbientLight ALig;
	ALig.SetAmbientLight(0.3f);

	
	Light Lig;
	Lig.DLight = DLig;
	Lig.PLight = PLig;
	Lig.SLight = SLig;
	Lig.ALight = ALig;
	/*Lig.LV.SetPrjMatrix(SunPerspective.GetViewProjectionMatrix());*/
	DepthShadow DShadow;
	DShadow.Init(Lig);

	Player* m_player = new Player;
	m_player->Init(Lig);

	Model BackGround;
	Model BackGroundSh;
	Model TW;
	Model shTW;

	ModelInitData BG;
	BG.m_tkmFilePath = "Assets/modelData/GreenCity.tkm";
	BG.m_fxFilePath = "Assets/shader/model.fx";
	BG.m_expandShaderResoruceView = &DShadow.GetShadowMap().GetRenderTargetTexture();
	BG.m_expandConstantBuffer = &Lig;
	BG.m_expandConstantBufferSize = sizeof(Lig);
	BG.m_collorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;
	ModelInitData BGSelfSModel;
	BGSelfSModel.m_tkmFilePath = "Assets/modelData/GreenCity.tkm";
	BGSelfSModel.m_fxFilePath = "Assets/shader/SampleDepthShadow.fx";
	BGSelfSModel.m_expandConstantBuffer = &Lig;
	BGSelfSModel.m_expandConstantBufferSize = sizeof(Lig);
	BGSelfSModel.m_collorBufferFormat[0] = DXGI_FORMAT_R32_FLOAT;

	ModelInitData TWData;
	TWData.m_tkmFilePath = "Assets/modelData/teapot.tkm";
	TWData.m_fxFilePath = "Assets/shader/model.fx";
	TWData.m_expandConstantBuffer = &Lig;
	TWData.m_expandConstantBufferSize = sizeof(Lig);
	TWData.m_collorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

	ModelInitData shTWdata;
	shTWdata.m_tkmFilePath = "Assets/modelData/teapot.tkm";
	shTWdata.m_fxFilePath = "Assets/shader/SampleDepthShadow.fx";
	shTWdata.m_expandConstantBuffer = &Lig;
	shTWdata.m_expandConstantBufferSize = sizeof(Lig);
	shTWdata.m_collorBufferFormat[0] = DXGI_FORMAT_R32_FLOAT;

	BackGround.Init(BG);
	BackGroundSh.Init(BGSelfSModel);
	TW.Init(TWData);
	shTW.Init(shTWdata);


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

	Vector3 UniSca = Vector3::One;

	float throwPow = 0;
	Vector3 throwVec = { 0.0f,0.7f,1.0f };
	Vector3 twPos;
	throwVec.Normalize();
	bool throwing = false;
	bool flyGrenad = false;
	Quaternion twRot;
	Vector3 twScale = { 1.0f,1.0f,1.0f };
	twPos = m_player->GetPosition();
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

		DLig.SetEyePos();

		ALig.SetAmbientLight(DLig.GetColor().Length() / 2.0f);

		Lig.DLight = DLig;
		Lig.PLight = PLig;
		Lig.SLight = SLig;

		//if (g_pad[0]->IsTrigger(enButtonLB1)&&!m_player->IsSprint()) {
		//	throwPow = 75.0f;
		//	throwing = true;
		//	twPos = m_player->GetPosition();
		//	throwVec = { 0.0f, 0.7f, 1.0f };
		//	throwVec.Scale(throwPow);
		//	m_player->GetRotation().Apply(throwVec);
		//	m_player->GetRotation().CopyTo(twRot);
		//	flyGrenad = true;
		//	/*m_test->SetPos(m_test->GetPos() - Vector3{ 0.0f, 25.0f, 0.0f });
		//	m_test->SetRot(twRot);
		//	throwVec *= 0.9f;
		//	if (throwVec.Length() < 0.1f)
		//	{
		//		throwVec = Vector3::Zero;
		//	}*/
		//	
		//}
		//else if (g_pad[0]->IsTrigger(enButtonLB1) && flyGrenad == true && !m_player->IsSprint())
		//{
		//	twPos = Vector3::Zero;
		//	
		//	flyGrenad = false;
		//	throwing = false;
		//}

		Vector3 ComDistance = { 0.0f, 1000.0f, 400.0f };
		g_camera3D->SetTarget(m_player->GetPosition());
		g_camera3D->SetPosition(m_player->GetPosition() + ComDistance);

		shTW.UpdateWorldMatrix(twPos, twRot, twScale);

		DShadow.Update(Lig);
		

		renderContext.WaitUntilToPossibleSetRenderTarget(DShadow.GetShadowMap());
		renderContext.SetRenderTargetAndViewport(DShadow.GetShadowMap());
		renderContext.ClearRenderTargetView(DShadow.GetShadowMap());

		m_player->ShadowDrower(DShadow.GetCamera());
		//BackGroundSh.Draw(renderContext, DShadow.GetCamera());
		if (flyGrenad)shTW.Draw(renderContext, DShadow.GetCamera());

		renderContext.WaitUntilFinishDrawingToRenderTarget(DShadow.GetShadowMap());
		/*DShadow.DrawShadow(uniSha, renderContext);*/

		//�����_�����O�^�[�Q�b�g��mainRenderTarget�ɕύX����
		//�����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂�
		renderContext.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
		//�����_�����O�^�[�Q�b�g��ݒ�
		renderContext.SetRenderTargetAndViewport(mainRenderTarget);
		//�����_�����O�^�[�Q�b�g���N���A
		renderContext.ClearRenderTargetView(mainRenderTarget);
		
		m_player->ModelDrower();
		BackGround.Draw(renderContext);
		
		if (throwing)
		{
			
			throwing = false;
			
		}
		if (flyGrenad)
		{
			twPos += throwVec;
			twPos.y -= 25.0f;
			if (twPos.y < 0) { twPos.y = 0; }
			throwVec *= 0.9f;
			if (throwVec.Length() < 0.1)
			{
				throwVec = Vector3::Zero;
			}
			TW.UpdateWorldMatrix(twPos, twRot, twScale);
			TW.Draw(renderContext);
			
		}

		renderContext.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);

		m_player->Update(Lig);
		g_camera3D->Update();
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

