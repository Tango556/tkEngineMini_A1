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
	
    float3 PLigPosition;
    float3 PLigColor;
    float Range;
	
    float3 SLigPosition;
    float3 SligColor;
    float SLigRange;
    float3 SLigDirection;
    float SLigAngle;
    
    float AmbientLight;
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
	SSkinVSIn skinVert;				//スキン用のデータ。
};
//ピクセルシェーダーへの入力。
struct SPSIn{
	float4 pos 			: SV_POSITION;	//スクリーン空間でのピクセルの座標。
	float3 normal		: NORMAL;
	float2 uv 			: TEXCOORD0;	//uv座標。
    float3 worldPos		: TEXCOORD1;
};
///////////////////////////////////////////
// 関数宣言
///////////////////////////////////////////
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal);
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal);

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
    SPSIn psIn;
    
    psIn.pos = mul(mWorld, vsIn.pos);
    psIn.worldPos = psIn.pos;
    psIn.pos = mul(mView, psIn.pos);
    psIn.pos = mul(mProj, psIn.pos);
    
    //頂点法線をピクセルシェーダーに渡す
    psIn.normal = mul(mWorld, vsIn.normal);
    psIn.uv = vsIn.uv;
    
    return psIn;
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
	
    float3 PligDir = psIn.worldPos - PLigPosition;
    PligDir = normalize(PligDir);
	
    float3 diffPoint = CalcLambertDiffuse(PligDir, PLigColor, psIn.normal);
    float3 specPoint = CalcPhongSpecular(PligDir, PLigColor, psIn.worldPos, psIn.normal);
	
    float3 PLigDistance = length(psIn.worldPos - PLigPosition);
	
    float PligAffect = 1.0f - 1.0f / Range * PLigDistance;	
	//影響力がマイナスにならないように補正
    if (PligAffect < 0.0f)
    {
        PligAffect = 0.0f;
    }
    PligAffect = pow(PligAffect, 3.0f);
	
    diffPoint *= PligAffect;
    specPoint *= PligAffect;
    
    float3 SligDir = psIn.worldPos - SLigPosition;
    SligDir = normalize(SligDir);
    
    float3 diffSpotLight = CalcLambertDiffuse(
        SligDir,
        SligColor,
        psIn.normal
    );
    
    float3 specSpotLight = CalcPhongSpecular(
        SligDir,
        SligColor,
        psIn.worldPos,
        psIn.normal
    );
    
    //スポットライトとの距離を計算する
    float3 SLigDistance = length(psIn.worldPos - SLigPosition);
    
    //影響率は距離に比例して小さくなる
    float SLigAffect = 1.0f - 1.0f / SLigRange * SLigDistance;
    //影響値がマイナスにならないように補正する
    if (SLigAffect < 0.0f)
    {
        SLigAffect = 0.0f;
    }
    
    SLigAffect = pow(SLigAffect, 3.0f);
    
    diffSpotLight *= SLigAffect;
    specSpotLight *= SLigAffect;
    
    float angle = dot(SligDir, SLigDirection);
    
    angle = acos(angle);
    
    SLigAffect = 1.0f - (1.0f / SLigAngle * angle);
    //影響力がマイナスにならないように補正かける
    if (SLigAffect < 0.0f)
    {
        SLigAffect = 0.0f;
    }
    //影響の仕方を指数関数的にす
    SLigAffect = pow(SLigAffect, 0.5f);
    
    diffSpotLight *= SLigAffect;
    specSpotLight *= SLigAffect;
    
    float3 lig = (diffuseLig + diffPoint + diffSpotLight) + (specularLig + specPoint + specSpotLight);
	
    float4 finalColor = g_albedo.Sample(g_sampler, psIn.uv);
	
    float3 ambientLig = { AmbientLight, AmbientLight, AmbientLight };

	finalColor.xyz *= lig + ambientLig;
	
	
	return finalColor;
}

float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal)
{
    // ピクセルの法線とライトの方向の内積を計算する
    float t = dot(normal, lightDirection) * -1.0f;

    // 内積の値を0以上の値にする
    t = max(0.0f, t);

    // 拡散反射光を計算する
    return lightColor * t;
}

float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal)
{
    // 反射ベクトルを求める
    float3 refVec = reflect(lightDirection, normal);

    // 光が当たったサーフェイスから視点に伸びるベクトルを求める
    float3 toEye = eyePos - worldPos;
    toEye = normalize(toEye);

    // 鏡面反射の強さを求める
    float t = dot(refVec, toEye);

    // 鏡面反射の強さを0以上の数値にする
    t = max(0.0f, t);

    // 鏡面反射の強さを絞る
    t = pow(t, 5.0f);

    // 鏡面反射光を求める
    return lightColor * t;
}