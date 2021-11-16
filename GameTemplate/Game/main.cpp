#include "stdafx.h"
#include "system/system.h"
#include "KTypeBloom.h"
#include "DepthShadow.h"
#include "Player.h"


///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	//////////////////////////////////////
	// ここから初期化を行うコードを記述する。
	//////////////////////////////////////

	//ゲームオブジェクトマネージャーのインスタンスを作成する。
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

	DLig.SetColor({1.2f, 1.2f, 1.2f });
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

	Player * m_player = new Player;
	m_player->Init(Lig);

	//RenderTarget shadowMapRT; //シャドウマップレンダーターゲット
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

	/*Model Uni;
	Model UniSha;*/
	Model BackGround;
	Model TW;
	Model shTW;

	ModelInitData uni;
	uni.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
	uni.m_fxFilePath = "Assets/shader/model.fx";
	uni.m_expandShaderResoruceView = &DShadow.GetBluredSHD();
	//uni.m_expandShaderResoruceView = &DShadow.GetShadowMap().GetRenderTargetTexture();
	uni.m_expandConstantBuffer = &Lig;
	uni.m_expandConstantBufferSize = sizeof(Lig);
	uni.m_collorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

	ModelInitData uniSha;
	uniSha.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
	uniSha.m_fxFilePath = "Assets/shader/SampleDepthShadow.fx";
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

	//Uni.Init(uni);
	BackGround.Init(BG);
	//UniSha.Init(uniSha);
	TW.Init(TWData);
	shTW.Init(shTWdata);


	SpriteInitData spriteInitData;

	//テクスチャはmainRenderTargetのカラーバッファー
	spriteInitData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
	spriteInitData.m_width = 1280;
	spriteInitData.m_height = 720;

	//モノクロ用のシェーダーを指定する
	spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";

	Sprite copyToFrameBufferSprite;
	copyToFrameBufferSprite.Init(spriteInitData);	

	KTypeBloom kBloom;
	kBloom.Init(mainRenderTarget);

	int DLigStrLevel = 0;

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
	twPos = m_player->GetPositon();
	//////////////////////////////////////
	// 初期化を行うコードを書くのはここまで！！！
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	


	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		//レンダリング開始。
		g_engine->BeginFrame();
		
		//////////////////////////////////////
		//ここから絵を描くコードを記述する。
		//////////////////////////////////////
		
		SLig.SetSLigPos({ SLig.GetSLigPos().x - g_pad[0]->GetLStickXF(),SLig.GetSLigPos().y, SLig.GetSLigPos().z });
		if (g_pad[0]->IsPress(enButtonB)) {
			SLig.SetSLigPos({ SLig.GetSLigPos().x, SLig.GetSLigPos().y, SLig.GetSLigPos().z + g_pad[0]->GetLStickYF() });
		}
		else {			
			SLig.SetSLigPos({ SLig.GetSLigPos().x, SLig.GetSLigPos().y + g_pad[0]->GetLStickYF(),SLig.GetSLigPos().z });
		}
		
		DireLigRollerX.SetRotationDeg(Vector3::AxisX, -0.01f * (g_pad[0]->GetRStickYF() * 100.0f + 1.0f));
		DireLigRollerY.SetRotationDeg(Vector3::AxisY, g_pad[0]->GetRStickXF());
		DireLigRollerX.Multiply(DireLigRollerY, DireLigRollerX);

		DireLigRollerX.Apply(DLigDir);
		DLig.SetDirection(DLigDir);

		if (g_pad[0]->IsTrigger(enButtonA))
		{
			DLigStrLevel++;
			if (DLigStrLevel > 2)
			{
				DLigStrLevel = 0;
			}
		}
		switch (DLigStrLevel)
		{
		case 0:
			DLig.SetColor({ 0.8f, 0.8f, 0.9f });
			break;
		case 1:
			DLig.SetColor({ 1.2f,1.2f,1.3f });
			break;
		case 2:
			DLig.SetColor({ 2.0f,2.0f,2.1f });
			break;
		};

		DLig.SetEyePos();

		ALig.SetAmbientLight(DLig.GetColor().Length() / 2.0f);

		Lig.DLight = DLig;
		Lig.PLight = PLig;
		Lig.SLight = SLig;
		
		//RotAng += (float)g_pad[0]->GetRStickXF() * 2.0f;
		//RotAng -= (float)g_pad[0]->GetRStickXF() * 2.0f;
		//UniQua.SetRotationDeg(Vector3::AxisY, RotAng);

		Vector3 UniControll = { g_pad[0]->GetLStickXF(), 0.0f, g_pad[0]->GetLStickYF() };
		UniControll.Normalize();
		//UniQua.Apply(UniControll);
		UniControll.Scale(10.0f);
		//UniPos.Add(UniControll);

		//Uni.UpdateWorldMatrix(UniPos, UniQua, UniSca);
		//UniSha.UpdateWorldMatrix(UniPos, UniQua, UniSca);

		if (g_pad[0]->IsTrigger(enButtonLB1)) {
			throwPow = 75.0f;
			throwing = true;
			twPos = m_player->GetPositon();
			throwVec = { 0.0f, 0.7f, 1.0f };
			throwVec.Scale(throwPow);
			m_player->GetRotation().Apply(throwVec);
			m_player->GetRotation().CopyTo(twRot);
			flyGrenad = true;
		}
		else if (g_pad[0]->IsTrigger(enButtonLB1) && flyGrenad == true)
		{
			twPos = Vector3::Zero;
			
			flyGrenad = false;
			throwing = false;
		}

		Vector3 ComDistance = { 0.0f, 1000.0f, 400.0f };
		g_camera3D->SetTarget(m_player->GetPositon());
		g_camera3D->SetPosition(m_player->GetPositon() + ComDistance);

		shTW.UpdateWorldMatrix(twPos, twRot, twScale);

		DShadow.Update(Lig);
		m_player->Update(Lig);

		renderContext.WaitUntilToPossibleSetRenderTarget(DShadow.GetShadowMap());
		renderContext.SetRenderTargetAndViewport(DShadow.GetShadowMap());
		renderContext.ClearRenderTargetView(DShadow.GetShadowMap());

		m_player->ShadowDrower(DShadow.GetCamera());
		//UniSha.Draw(renderContext,DShadow.GetCamera());
		if (flyGrenad)shTW.Draw(renderContext, DShadow.GetCamera());

		renderContext.WaitUntilFinishDrawingToRenderTarget(DShadow.GetShadowMap());
		/*DShadow.DrawShadow(uniSha, renderContext);*/

		//レンダリングターゲットをmainRenderTargetに変更する
		//レンダリングターゲットとして利用できるまで待つ
		renderContext.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
		//レンダリングターゲットを設定
		renderContext.SetRenderTargetAndViewport(mainRenderTarget);
		//レンダリングターゲットをクリア
		renderContext.ClearRenderTargetView(mainRenderTarget);
		
		m_player->ModelDrower();
		//Uni.Draw(renderContext);
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

		//モデル描画

		kBloom.Updete(mainRenderTarget);


		renderContext.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);
		
		copyToFrameBufferSprite.Draw(renderContext);
		

		GameObjectManager::GetInstance()->ExecuteUpdate();
		GameObjectManager::GetInstance()->ExecuteRender(renderContext);
		
		
		//////////////////////////////////////
		//絵を描くコードを書くのはここまで！！！
		//////////////////////////////////////
		g_engine->EndFrame();
	}
	//ゲームオブジェクトマネージャーを削除。
	GameObjectManager::DeleteInstance();
	return 0;
}

