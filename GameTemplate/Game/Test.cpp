#include "stdafx.h"
#include "Test.h"

Test::Test()
{

}

Test::~Test()
{

}

void Test::Init(Light& Lig)
{
	ModelInitData TWData;
	TWData.m_tkmFilePath = "Assets/modelData/teapot.tkm";
	TWData.m_fxFilePath = "Assets/shader/model.fx";
	TWData.m_expandConstantBuffer = &Lig;
	TWData.m_expandConstantBufferSize = sizeof(Lig);
	TWData.m_collorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

	m_model.Init(TWData);
}

void Test::Update()
{
	m_model.UpdateWorldMatrix(m_pos, m_rot, m_scale);
}

bool Test::Start()
{
	return true;
}