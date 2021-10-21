////////////////////////////////////////////////
// �萔�o�b�t�@�B
////////////////////////////////////////////////
//���f���p�̒萔�o�b�t�@

cbuffer ModelCb : register(b0)
{
    float4x4 mWorld;
    float4x4 mView;
    float4x4 mProj;
};

struct SVSIn
{
    float4 pos : POSITION; //���f���̒��_���W�B
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0; //UV���W�B
};
//�s�N�Z���V�F�[�_�[�ւ̓��́B
struct SPSIn
{
    float4 pos : SV_POSITION; //�X�N���[����Ԃł̃s�N�Z���̍��W�B
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0; //uv���W�B
};

//�O���[�o���ϐ�
Texture2D<float4> g_albedo : register(t0); //�A���x�h�}�b�v
Texture2D<float4> g_shadowMap : register(t10);
sampler g_sampler : register(s0); //�T���v���X�e�[�g�B

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