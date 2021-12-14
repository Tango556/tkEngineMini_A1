#include "stdafx.h"
#include "ModelLib.h"

ModelLib::ModelLib()
{

}

ModelLib::~ModelLib()
{

}

void ModelLib::Inits()
{
	for (int alpha = 0; alpha < enVal; alpha++)
	{
		switch (alpha)
		{
		case enTeapot:
			Datas[enTeapot].m_tkmFilePath = "Assets/modelData/teapot.tkm";
			Datas[enTeapot].m_fxFilePath = "Assets/shader/model.fx";
			Datas[enTeapot].m_collorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;
			Models[enTeapot].Init(Datas[enTeapot]);
			break;
		default:
			break;
		}
	}
}

Model* ModelLib::GetModel(enModel enAny)
{
	return &Models[enAny];
}