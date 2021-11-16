#include "stdafx.h"
#include "SkinModelRender.h"

namespace {
	const char SM_FX_FILEPATH[] = "Assets/shader/SampleDepthShadow.fx";
	const char MO_FX_FILEPATH[] = "Assets/shader/model.fx";
}

SkinModelRender::SkinModelRender()
{
	m_Lighting = FindGO<Lighting>("");
	
}

SkinModelRender::~SkinModelRender()
{
	
}

bool SkinModelRender::Start()
{

	return true;
}

void SkinModelRender::Update()
{
	/*auto& renderContext = g_graphicsEngine->GetRenderContext();*/
	
}


void SkinModelRender::Init(const char tkmFilePath[], const bool SC, const bool SR)
{
	m_mInitData[enModel].m_tkmFilePath = tkmFilePath;
	m_mInitData[enModel].m_fxFilePath = MO_FX_FILEPATH;
	m_mInitData[enModel].m_expandConstantBuffer = &m_Lighting;
	m_mInitData[enModel].m_expandConstantBufferSize = sizeof(m_Lighting);
	if (SR == true)
	m_mInitData[enModel].m_expandShaderResoruceView = &m_Shadow.GetShadowMap().GetRenderTargetTexture();
	m_mInitData[enModel].m_collorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

	if (SC == true){
		m_mInitData[enShadow].m_tkmFilePath = tkmFilePath;
		m_mInitData[enShadow].m_fxFilePath = SM_FX_FILEPATH;
		m_mInitData[enShadow].m_expandConstantBuffer = m_Lighting;
		m_mInitData[enShadow].m_expandConstantBufferSize = sizeof(m_Lighting);
		m_mInitData[enShadow].m_collorBufferFormat[0] = DXGI_FORMAT_R32_FLOAT;
	}

	m_model[enModel].Init(m_mInitData[enModel]);
	m_model[enShadow].Init(m_mInitData[enShadow]);
}

void SkinModelRender::Render(RenderContext& renderContext)
{

		m_model[enShadow].UpdateWorldMatrix(m_position, m_rotation, m_scale);


		m_model[enModel].Draw(renderContext);

}