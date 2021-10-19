#pragma once
#include "GaussianBlur.h"
class KTypeBloom
{
private:
	/// @brief 輝度抽出用RenderTarget
	RenderTarget luminanceRenderTarget;
	/// @brief 加算合成対象 : isAObject
	RenderTarget bloomTarget;
	/// @brief 輝度抽出用のスプライト
	Sprite luminanceSprite;
	/// @brief 加算合成主体 : isASubject
	Sprite finalSprite;
	/// @brief ガウシアンブラー
	GaussianBlur toBloomGaussianBlur[4];		
public:
	/// <summary>
	/// 初期化関数
	/// </summary>
	/// <param name="renderTarget">加算合成したいレンダーターゲット</param>
	void Init(RenderTarget& RT);
	/// <summary>
	/// ループ内で行う処理
	/// </summary>
	/// <param name="RT">レンダーターゲット</param>
	/// <param name="RC">レンダーコンテキスト</param>
	void Updete(RenderTarget& RT, RenderContext& RC);
};

