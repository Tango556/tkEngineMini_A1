#include "stdafx.h"
#include "GaussianBlur.h"
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


	//DirectionLight dirLig;
	//dirLig.SetDirection({ 1.0f, -1.0f, -1.0f });
	////正規化する
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

	DirectionLight DLig;
	
	Vector3 DLigDir = { 0.0f, -1.0f, -1.0f };

	DLig.SetColor({1.0f, 1.0f, 0.6f});
	DLig.SetDirection(DLigDir);
	
	PointLight PLig;
	/*
	PLig.SetColor({ 10.0f, 0.0f, 0.0f });
	PLig.SetPLigPos({ 50.0f, 100.0f, 50.0f });
	PLig.SetRange(150.0f);*/

	SpotLight SLig;
	/*SLig.SetSLigPos({ 0.0f, 0.0f, 300.0f });
	SLig.SetSLigColor({10.0f, 10.0f, 10.0f });
	SLig.SetSLigRan(1000.0f);
	SLig.SetSLigDir({ 0.0f, 0.0f, -1.0f });
	SLig.SetSLigAng(10.0f);*/

	AmbientLight ALig;
	ALig.Light = 0.5f;

	Light Lig;
	//Lig.DLight = DLig;
	//Lig.PLight = PLig;
	Lig.SLight = SLig;
	Lig.ALight = ALig;

	/*Lig.ptColor.x = 15.0f;
	Lig.ptColor.y = 15.0f;
	Lig.ptColor.z = 15.0f;
	Lig.ptPosition.x = 0.0f;
	Lig.ptPosition.y = 50.0f;
	Lig.ptPosition.z = 50.0f;

	Lig.ptRange = 100.0f;*/
	Model Uni;
	Model BackGround;

	ModelInitData uni;
	uni.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
	uni.m_fxFilePath = "Assets/shader/model.fx";

	uni.m_expandConstantBuffer = &Lig;
	uni.m_expandConstantBufferSize = sizeof(Lig);
	uni.m_collorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

	ModelInitData BG;
	BG.m_tkmFilePath = "Assets/modelData/bg/bg.tkm";
	BG.m_fxFilePath = "Assets/shader/model.fx";

	BG.m_expandConstantBuffer = &Lig;
	BG.m_expandConstantBufferSize = sizeof(Lig);
	BG.m_collorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

	Uni.Init(uni);
	BackGround.Init(BG);
	Quaternion DirRota;

	//輝度抽出用レンダリングターゲットを作成
	RenderTarget luminanceRenderTarget;

	//解像度、ミニマップレベル
	luminanceRenderTarget.Create(
		1280,
		720,
		1,
		1,
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		DXGI_FORMAT_D32_FLOAT
	);

	//輝度抽出用のスプライトを初期化
	//初期化情報を作成する
	SpriteInitData luminanceSpriteInitData;

	//輝度抽出用のシェーダーのファイルパスを指定する
	luminanceSpriteInitData.m_fxFilePath = "Assets/shader/posteffects.fx";

	//頂点シェーダーのエントリーポイントを指定
	luminanceSpriteInitData.m_vsEntryPointFunc = "VSMain";
	
	//ピクセルシェーダーのエントリーポイントを指定する
	luminanceSpriteInitData.m_psEntryPointFunc = "PSSamplingLuminance";

	//スプライトの幅と高さはluminannceRenderTargetと同じ
	luminanceSpriteInitData.m_width = 1280;
	luminanceSpriteInitData.m_height = 720;

	// テクスチャはメインレンダリングターゲットのカラーバッファー
	luminanceSpriteInitData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();

	//描き込むレンダリングターゲットのフォーマットを指定する
	luminanceSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

	//作成した初期化情報をもとにスプライトを初期化する
	Sprite luminanceSprite;
	luminanceSprite.Init(luminanceSpriteInitData);

	//ガウシアンブラーを初期化
	GaussianBlur toBloomGaussianBlur[4];
	//gaussianBlur[0]は輝度テクスチャにガウシアンブラーをかける。
	toBloomGaussianBlur[0].Init(&luminanceRenderTarget.GetRenderTargetTexture());
	//gaussianBlur[1]はgaussianBlur[1]にテクスチャにガウシアンブラーをかける
	toBloomGaussianBlur[1].Init(&toBloomGaussianBlur[0].GetBlurredTexture());
	toBloomGaussianBlur[2].Init(&toBloomGaussianBlur[1].GetBlurredTexture());
	toBloomGaussianBlur[3].Init(&toBloomGaussianBlur[2].GetBlurredTexture());

	//ボケ画像を合成して描き込むためのスプライトを初期化
	//初期化情報を設定す
	SpriteInitData finalSpriteInitData;
	finalSpriteInitData.m_textures[0] = &toBloomGaussianBlur[0].GetBlurredTexture();
	finalSpriteInitData.m_textures[1] = &toBloomGaussianBlur[1].GetBlurredTexture();
	finalSpriteInitData.m_textures[2] = &toBloomGaussianBlur[2].GetBlurredTexture();
	finalSpriteInitData.m_textures[3] = &toBloomGaussianBlur[3].GetBlurredTexture();

	//解像度はmainRenderTargetの幅と高さ
	finalSpriteInitData.m_width = 1280;
	finalSpriteInitData.m_height = 720;
	//ボケ画像を合成する必要があるので専用シェーダーを指定。
	finalSpriteInitData.m_fxFilePath = "Assets/shader/posteffects.fx";
	finalSpriteInitData.m_psEntryPointFunc = "PSBloomFinal";

	//ただし加算合成で描画するので、アルファブレンディングモードに加算にする
	finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;
	//カラーバッファのフォーマットは32bitFloatingPointバッファ
	finalSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

	//初期化情報を元に加算合成用のスプライトを初期化する。
	Sprite finalSprite;
	finalSprite.Init(finalSpriteInitData);

	//mainRenderTargetのテクスチャをフレームバッファーに貼り付けるためのスプライトを初期化する
	//スプライトの初期化オブジェクトを作成する。
	SpriteInitData spriteInitData;

	//テクスチャはmainRenderTargetのカラーバッファー
	spriteInitData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
	spriteInitData.m_width = 1280;
	spriteInitData.m_height = 720;

	//モノクロ用のシェーダーを指定する
	spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";

	Sprite copyToFrameBufferSprite;
	copyToFrameBufferSprite.Init(spriteInitData);

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
		
		SLig.SLigPosition.x -= g_pad[0]->GetLStickXF();
		if (g_pad[0]->IsPress(enButtonB)) {
			SLig.SLigPosition.y += g_pad[0]->GetLStickYF();
		}
		else {
			SLig.SLigPosition.z -= g_pad[0]->GetLStickYF();
		}

		float DirAng = 0.02f;

		//DirRota.SetRotation(Vector3::AxisX, DirAng);
		//DirRota.Apply(DLigDir);

		//DLig.SetDirection(DLigDir);
		Vector3 AdditionColor;


		Lig.DLight = DLig;
		//Lig.PLight = PLig;
		Lig.SLight = SLig;

		//レンダリングターゲットをmainRenderTargetに変更する
		//レンダリングターゲットとして利用できるまで待つ
		renderContext.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
		//レンダリングターゲットを設定
		renderContext.SetRenderTargetAndViewport(mainRenderTarget);
		//レンダリングターゲットをクリア
		renderContext.ClearRenderTargetView(mainRenderTarget);

		//モデル描画
		Uni.Draw(renderContext);
		BackGround.Draw(renderContext);

		renderContext.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);

		//輝度抽出
		//輝度抽出用のレンダリングターゲットに変更
		renderContext.WaitUntilToPossibleSetRenderTarget(luminanceRenderTarget);
		//レンダリングターゲットに設定
		renderContext.SetRenderTargetAndViewport(luminanceRenderTarget);
		//レンダリングターゲットをクリア
		renderContext.ClearRenderTargetView(luminanceRenderTarget);
		//輝度抽出を行う
		luminanceSprite.Draw(renderContext);
		//レンダリングターゲットへの書き込み終了待ち
		renderContext.WaitUntilFinishDrawingToRenderTarget(luminanceRenderTarget);
		//ガウシアンブラーを4回実行する
		toBloomGaussianBlur[0].ExevuteOnGPU(renderContext, 10);
		toBloomGaussianBlur[1].ExevuteOnGPU(renderContext, 10);
		toBloomGaussianBlur[2].ExevuteOnGPU(renderContext, 10);
		toBloomGaussianBlur[3].ExevuteOnGPU(renderContext, 10);

		//ボケ画像を合成してレンダリングターゲットに加算合成
		//レンダリングターゲットとして利用できるまで待つ
		renderContext.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
		//レンダリングターゲットを設定
		renderContext.SetRenderTargetAndViewport(mainRenderTarget);
		//最終合成
		finalSprite.Draw(renderContext);
		//レンダリングターゲットへの書き込み終了待ち
		renderContext.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);

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

