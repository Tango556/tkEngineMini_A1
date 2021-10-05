#pragma once

/// <summary>
/// ガウシアンブラークラス
/// </summary>
class GaussianBlur {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="originalTexture">ガウシアンブラーをかけるオリジナルテクスチャ</param>
	void Init(Texture* originalTexture);
	/// <summary>
	/// ガウシアンブラーをGPU上で実行
	/// </summary>
	/// <param name="renCon">レンダリングターゲット</param>
	/// <param name="blurPower">ブラー強度。値が大きいほど強くなる</param>
	void ExevuteOnGPU(RenderContext& renCon, float blurPower);
	/// <summary>
	/// ぼかしたテクスチャを取得
	/// </summary>
	/// <returns></returns>
	Texture& GetBlurredTexture()
	{
		return m_yBlurRenderTarget.GetRenderTargetTexture();
	}
private:
	/// <summary>
	/// レンダリングターゲットを初期化
	/// </summary>
	void InitRenderTargets();
	/// <summary>
	/// スプライトを初期化
	/// </summary>
	void InitSprites();
	/// <summary>
	/// 重みテーブルを更新する
	/// </summary>
	/// <param name="blurPower"></param>
	void UpdateWeightTable(float blurPower);
private:
	enum{NUM_WEIGHTS = 8};
	float m_weights[NUM_WEIGHTS];
	Texture* m_originalTexture = nullptr;
	RenderTarget m_xBlurRenderTarget;
	RenderTarget m_yBlurRenderTarget;
	Sprite m_xBlurSprite;
	Sprite m_yBlurSprite;
};

