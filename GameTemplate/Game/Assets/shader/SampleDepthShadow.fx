////////////////////////////////////////////////
// 定数バッファ。
////////////////////////////////////////////////
//モデル用の定数バッファ

cbuffer ModelCb : register(b0)
{
    float4x4 mWorld;
    float4x4 mView;
    float4x4 mProj;
};

struct SVSIn
{
    float4 pos : POSITION; //モデルの頂点座標。
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0; //UV座標。
};
//ピクセルシェーダーへの入力。
struct SPSIn
{
    float4 pos : SV_POSITION; //スクリーン空間でのピクセルの座標。
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0; //uv座標。
};

//グローバル変数
Texture2D<float4> g_albedo : register(t0); //アルベドマップ
Texture2D<float4> g_shadowMap : register(t10);
sampler g_sampler : register(s0); //サンプラステート。

SPSIn VSMain(SVSIn vsIn)
{
    SPSIn psIn;
    
    psIn.pos = mul(mWorld, vsIn.pos);
    psIn.pos = mul(mView, psIn.pos);
    psIn.pos = mul(mProj, psIn.pos);

    psIn.uv = vsIn.uv;
    psIn.normal = mul(mWorld, vsIn.normal);
    
    return psIn;
}

float4 PSMain(SPSIn psIn) : SV_Target0
{
    return float4(psIn.pos.z, psIn.pos.z, psIn.pos.z, 1.0f);
}