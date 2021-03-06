/*!
 * @brief ポストエフェクト
 */

cbuffer cb : register(b0)
{
    float4x4 mvp;       //MVP配列
    float4 mulColor;    //乗算カラー
};

struct VSInput
{
    float4 pos  : POSITION;
    float2 uv   : TEXCOORD0;
};

struct PSInput
{
    float4 pos : SV_POSITION;
    float2 uv  : TEXCOORD0;
};

/*
 * @brief 頂点シェーダー
 */
PSInput VSMain(VSInput In)
{
    PSInput psIn;
    psIn.pos = mul(mvp, In.pos);
    psIn.uv = In.uv;
    return psIn;
}

Texture2D<float4> mainRenderTargetTexture : register(t0);//メインレンダリングターゲットのテクスチャ
sampler Sampler : register(s0);

////////////
//輝度抽出//
////////////
/*!
 * @brief 輝度抽出用のピクセルシェーダー
 */
float4 PSSamplingLuminance(PSInput In) : SV_Target0
{
    //メインレンダリングターゲットからカラーをサンプリング
    float4 color = mainRenderTargetTexture.Sample(Sampler, In.uv);

    //サンプリング下カラーの明るさを計算
    float t = dot(color.xyz, float3(0.2125f, 0.7154f, 0.0721f));
    
    //clip()関数は引数の値がマイナスになると、以降の処理をスキップする
    //なので、マイナスになるとピクセルカラーは出力されない
    //今回の実装はカラーの明るさが1以下ならピクセルキルする
    clip(t - 1.5f);
    
    return color;
}

//ボケ画像にアクセスするための変数を追加
Texture2D<float4> g_blurredTexture_0 : register(t0);
Texture2D<float4> g_blurredTexture_1 : register(t1);
Texture2D<float4> g_blurredTexture_2 : register(t2);
Texture2D<float4> g_blurredTexture_3 : register(t3);

float4 PSBloomFinal(PSInput In) : SV_Target0
{
    //ボケ画像をサンプリングして、平均を取って出力する
    float4 combineColor = g_blurredTexture_0.Sample(Sampler, In.uv);
    combineColor += g_blurredTexture_1.Sample(Sampler, In.uv);
    combineColor += g_blurredTexture_2.Sample(Sampler, In.uv);
    combineColor += g_blurredTexture_3.Sample(Sampler, In.uv);
    combineColor /= 4.0f;
    combineColor.a = 1.0f;
    return combineColor;
}