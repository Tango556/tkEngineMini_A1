#include "stdafx.h"
#include "system/system.h"


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

	/*struct DirectionLight
	{
		Vector3 ligDirection;
		float pad;
		Vector3 ligColor;
	};*/



	//DirectionLight dirLig;
	//dirLig.SetDirection({ 1.0f, -1.0f, -1.0f });
	////正規化する
	//dirLig.ligDirection.Normalize();

	//dirLig.SetColor({ 1.0f,1.0f,1.0f });

	//dirLig.eyePos = g_camera3D->GetPosition();

	DirectionLight DLig;

	DLig.SetColor({ 0.0f,0.0f,0.0f });
	DLig.SetDirection({ 0.0f,0.0f,0.0f });

	PointLight PLig;
	PLig.SetColor({ 0.0f, 0.0f, 0.0f });
	PLig.SetPLigPos({ 0.0f, 50.0f, 50.0f });
	PLig.SetRange(100.0f);

	SpotLight SLig;
	SLig.SetSLigPos({ 0.0f, 0.0f, 300.0f });
	SLig.SetSLigColor({ 10.0f, 10.0f, 10.0f });
	SLig.SetSLigRan(1000.0f);
	SLig.SetSLigDir({ 0.0f, 0.0f, -1.0f });
	SLig.SetSLigAng(25.0f);

	Light Lig;
	Lig.DLight = DLig;
	Lig.PLight = PLig;
	Lig.SLight = SLig;

	/*Lig.ptColor.x = 15.0f;
	Lig.ptColor.y = 15.0f;
	Lig.ptColor.z = 15.0f;

	Lig.ptPosition.x = 0.0f;
	Lig.ptPosition.y = 50.0f;
	Lig.ptPosition.z = 50.0f;

	Lig.ptRange = 100.0f;*/

	//////////////////////////////////////
	// 初期化を行うコードを書くのはここまで！！！
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	Model Uni;
	Model BackGround;

	ModelInitData uni;
	uni.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
	uni.m_fxFilePath = "Assets/shader/model.fx";

	uni.m_expandConstantBuffer = &Lig;
	uni.m_expandConstantBufferSize = sizeof(Lig);

	ModelInitData BG;
	BG.m_tkmFilePath = "Assets/modelData/bg/bg.tkm";
	BG.m_fxFilePath = "Assets/shader/model.fx";

	BG.m_expandConstantBuffer = &Lig;
	BG.m_expandConstantBufferSize = sizeof(Lig);

	Uni.Init(uni);
	BackGround.Init(BG);

	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		//レンダリング開始。
		g_engine->BeginFrame();
		
		SLig.SLigPosition.x -= g_pad[0]->GetLStickXF();
		if (g_pad[0]->IsPress(enButtonB)) {
			SLig.SLigPosition.y += g_pad[0]->GetLStickYF();
		}
		else {
			SLig.SLigPosition.z -= g_pad[0]->GetLStickYF();
		}

		Lig.DLight = DLig;
		Lig.PLight = PLig;
		Lig.SLight = SLig;
		//////////////////////////////////////
		//ここから絵を描くコードを記述する。
		//////////////////////////////////////
		
		GameObjectManager::GetInstance()->ExecuteUpdate();
		GameObjectManager::GetInstance()->ExecuteRender(renderContext);
		
		Uni.Draw(renderContext);
		BackGround.Draw(renderContext);
		//////////////////////////////////////
		//絵を描くコードを書くのはここまで！！！
		//////////////////////////////////////
		g_engine->EndFrame();
	}
	//ゲームオブジェクトマネージャーを削除。
	GameObjectManager::DeleteInstance();
	return 0;
}

