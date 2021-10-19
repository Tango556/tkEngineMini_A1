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

	//輝度抽出用スプライトの初期化情報
	SpriteInitData luminanceSpriteInitData;
	//輝度抽出用シェーダーのファイルパスを指定
	luminanceSpriteInitData.m_fxFilePath = "Assets/shader/posteffects.fx";
	//頂点シェーダーのエントリーポイントを指定
	luminanceSpriteInitData.m_vsEntryPointFunc = "VSMain";

	//頂点シェーダーのエントリーポイントを指定
	luminanceSpriteInitData.m_psEntryPointFunc = "PSSamplingLuminance";

	//スプライトの幅と高さはluminanceRenderTargetと同じ
	luminanceSpriteInitData.m_width = 1280;
	luminanceSpriteInitData.m_height = 720;

	//テクスチャはBlurTargetのカラーバッファ
	luminanceSpriteInitData.m_textures[0] = &bloomTarget.GetRenderTargetTexture();

	//描き込むレンダリングターゲットのフォーマットを指定する
	luminanceSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

	//作成した初期化情報を元にスプライトを初期化する
	luminanceSprite.Init(luminanceSpriteInitData);
	
	//toBloomGaussianBlur[0]は輝度テクスチャにガウシアンブラーをかける
	toBloomGaussianBlur[0].Init(&luminanceRenderTarget.GetRenderTargetTexture());
	//toBloomGaussianBlur[1]はtoBloomGaussianBlur[0]のテクスチャにガウシアンブラーをかける
	toBloomGaussianBlur[1].Init(&toBloomGaussianBlur[0].GetBlurredTexture());
	toBloomGaussianBlur[2].Init(&toBloomGaussianBlur[1].GetBlurredTexture());
	toBloomGaussianBlur[3].Init(&toBloomGaussianBlur[2].GetBlurredTexture());

	//ブラード画像を合成して描き込むためのスプライトを初期化
	SpriteInitData finalSpriteInitData;
	finalSpriteInitData.m_textures[0] = &toBloomGaussianBlur[0].GetBlurredTexture();
	finalSpriteInitData.m_textures[1] = &toBloomGaussianBlur[1].GetBlurredTexture();
	finalSpriteInitData.m_textures[2] = &toBloomGaussianBlur[2].GetBlurredTexture();
	finalSpriteInitData.m_textures[3] = &toBloomGaussianBlur[3].GetBlurredTexture();

	//解像度はbloomTargetの幅と高さ
	finalSpriteInitData.m_width = 1280;
	finalSpriteInitData.m_height = 720;
	//ブラード画像を合成する必要があるので専用シェーダーを指定
	finalSpriteInitData.m_fxFilePath = "Assets/shader/posteffects.fx";
	finalSpriteInitData.m_psEntryPointFunc = "PSBloomFinal";
	
	//ただし加算合成で描画するので、アルファブレンディングモードに加算にする
	finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;
	//カラーバッファのフォーマットは32bitFloatingPointバッファ
	finalSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

	//加算合成主体のスプライトを初期化
	finalSprite.Init(finalSpriteInitData);
}

void KTypeBloom::Updete(RenderTarget& RT, RenderContext& RC)
{
	//輝度抽出
	//輝度抽出用のレンダリングターゲットに変更
	RC.WaitUntilToPossibleSetRenderTarget(luminanceRenderTarget);
	//レンダリングターゲットに設定
	RC.SetRenderTargetAndViewport(luminanceRenderTarget);
	//レンダリングターゲットをクリア
	RC.ClearRenderTargetView(luminanceRenderTarget);
	//輝度抽出を行う
	luminanceSprite.Draw(RC);
	//レンダリングターゲットへの書き込み終了待つ
	RC.WaitUntilFinishDrawingToRenderTarget(luminanceRenderTarget);
	//ガウシアンブラーを4回実行する
	toBloomGaussianBlur[0].ExecuteOnGPU(RC, 10);
	toBloomGaussianBlur[1].ExecuteOnGPU(RC, 10);
	toBloomGaussianBlur[2].ExecuteOnGPU(RC, 10);
	toBloomGaussianBlur[3].ExecuteOnGPU(RC, 10);

	//ブラード画像を合成しレンダリングターゲットに加算合成
	//レンダリングターゲットへの書き込み終了まち
	RC.WaitUntilToPossibleSetRenderTarget(RT);
	//レンダリングターゲットを設定
	RC.SetRenderTargetAndViewport(RT);
	//最終合成
	finalSprite.Draw(RC);
	//レンダリングターゲットへの書き込み終了待ち
	//RC.WaitUntilFinishDrawingToRenderTarget(RT);
}