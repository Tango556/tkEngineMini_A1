/*!
 * @brief	シンプルなモデルシェーダー。
 */


////////////////////////////////////////////////
// 定数バッファ。
////////////////////////////////////////////////
//モデル用の定数バッファ
cbuffer ModelCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
};

//ディレクションライト用定数バッファ
cbuffer DirectionLightCb : register(b1)
{
	float3 ligDirection;
	float3 ligColor;
    float3 eyePos;
};
////////////////////////////////////////////////
// 構造体
////////////////////////////////////////////////
//スキニング用の頂点データをひとまとめ。
struct SSkinVSIn{
	int4  Indices  	: BLENDINDICES0;
    float4 Weights  : BLENDWEIGHT0;
};
//頂点シェーダーへの入力。
struct SVSIn{
	float4 pos 		: POSITION;		//モデルの頂点座標。
	float3 normal	: NORMAL;
	float2 uv 		: TEXCOORD0;	//UV座標。
    //float3 worldPos : TEXCOORD1;
	SSkinVSIn skinVert;				//スキン用のデータ。
};
//ピクセルシェーダーへの入力。
struct SPSIn{
	float4 pos 			: SV_POSITION;	//スクリーン空間でのピクセルの座標。
	float3 normal		: NORMAL;
	float2 uv 			: TEXCOORD0;	//uv座標。
    float3 worldPos		: TEXCOORD1;
};

////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////
Texture2D<float4> g_albedo : register(t0);				//アルベドマップ
StructuredBuffer<float4x4> g_boneMatrix : register(t3);	//ボーン行列。
sampler g_sampler : register(s0);	//サンプラステート。

////////////////////////////////////////////////
// 関数定義。
////////////////////////////////////////////////

/// <summary>
//スキン行列を計算する。
/// </summary>
float4x4 CalcSkinMatrix(SSkinVSIn skinVert)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += g_boneMatrix[skinVert.Indices[i]] * skinVert.Weights[i];
        w += skinVert.Weights[i];
    }
    
    skinning += g_boneMatrix[skinVert.Indices[3]] * (1.0f - w);
	
    return skinning;
}

/// <summary>
/// 頂点シェーダーのコア関数。
/// </summary>
SPSIn VSMainCore(SVSIn vsIn, uniform bool hasSkin)
{
	SPSIn psIn;
	float4x4 m;
	if( hasSkin ){
		m = CalcSkinMatrix(vsIn.skinVert);
	}else{
		m = mWorld;
	}
	psIn.pos = mul(m, vsIn.pos);
	psIn.pos = mul(mView, psIn.pos);
	psIn.pos = mul(mProj, psIn.pos);

	psIn.normal = mul(mWorld, vsIn.normal);
	psIn.uv = vsIn.uv;
    psIn.worldPos = vsIn.pos;
	
	return psIn;
}

/// <summary>
/// スキンなしメッシュ用の頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
	return VSMainCore(vsIn, false);
}
/// <summary>
/// スキンありメッシュの頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSSkinMain( SVSIn vsIn ) 
{
	return VSMainCore(vsIn, true);
}
/// <summary>
/// ピクセルシェーダーのエントリー関数。
/// </summary>
float4 PSMain( SPSIn psIn ) : SV_Target0
{
	//float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv);
	//return albedoColor;
	float t = dot(psIn.normal, ligDirection);
	
	t *= -1.0f;
	
	if (t < 0.0f)
	{
		t = 0.0f;
	}
	float3 diffuseLig = ligColor * t;
	
    float3 refVec = reflect(ligDirection,psIn.normal);
	
    float3 toEye = eyePos - psIn.worldPos;
	//正規化する
    toEye = normalize(toEye);
	
	//dot関数を利用してrefVecとtoEyeの内積を求める。
    t = dot(refVec, toEye);
	//内積の結果はマイナスになるので、マイナスの場合は0にする
    if (t < 0.0f)
    {
        t = 0.0f;
    }
	
    t = pow(t, 5.0f);
	
    float3 specularLig = ligColor * t;
	
    float3 lig = diffuseLig + specularLig;
	
    float4 finalColor = g_albedo.Sample(g_sampler, psIn.uv);
	
    float3 ambientLig = { 0.3f, 0.3f, 0.3f };

	finalColor.xyz *= lig + ambientLig;
	
	
	return finalColor;
}
