/////
//�萔�o�b�t�@
/////

cbuffer ModelCb : register(b0)
{
    float4x4 mWorld;
    float4x4 mView;
    float4x4 mProj;
};

cbuffer mLVP : register(b1)
{
    float4x4 mLVP;
};

struct SVSIn{
    float4 pos : POSITION; //���f���̒��_���W�B
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0; //UV���W�B
};

struct SPSIn{
    float4 pos : SV_POSITION; //�X�N���[����Ԃł̃s�N�Z���̍��W�B
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0; //uv���W�B
    float4 posInLVP : TEXCOORD3; //���C�g�r���[�X�N���[����Ԃł̃s�N�Z�����W
};

////////
//�O���[�o���ϐ�
////////
Texture2D<float4> g_albedo : register(t0); //�A���x�h�}�b�v
Texture2D<float4> g_shadowMap : register(t10);
sampler g_sampler : register(s0); //�T���v���X�e�[�g�B


SPSIn VSMain(SVSIn vsIn)
{
    SPSIn psIn;
    psIn.pos = mul(mWorld, vsIn.pos);
    psIn.pos = mul(mView, psIn.pos);
    psIn.pos = mul(mProj, psIn.pos);
    
    //���_�@�����s�N�Z���V�F�[�_�[�ɓn��
    psIn.normal = mul(mWorld, vsIn.normal);
    psIn.uv = vsIn.uv;
    
    psIn.posInLVP = mul(mLVP, mul(mWorld, vsIn.pos));
    
    return psIn;
};

float4 PSMain(SPSIn psIn) : SV_Target0
{
    float4 finalColor = g_albedo.Sample(g_sampler, psIn.uv);

    
    float2 shadowMapUV = psIn.posInLVP.xy / psIn.posInLVP.w;
    shadowMapUV *= float2(0.5f, -0.5f);
    shadowMapUV += 0.5f;
    
    
    float zInLVP = psIn.posInLVP.z / psIn.posInLVP.w;
    
    //g_shadowMap = float4(psIn.pos.z, psIn.pos.z, psIn.pos.z, 1.0f);
    
    if (shadowMapUV.x > 0.0f && shadowMapUV.x < 1.0f
        && shadowMapUV.y > 0.0f && shadowMapUV.y < 1.0f)
    {        
        
        
        float zInShadowMap = g_shadowMap.Sample(g_sampler, shadowMapUV).r;
        if (zInLVP > zInShadowMap)
        {
            
            finalColor.xyz *= 0.5f;
        }
    }	
    return finalColor;
}