#include "stdafx.h"
#include "DepthShadow.h"


void DepthShadow::Init(Light& lig)
{
	float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	ShadowMap.Create(
		4096,
		4096,
		1,
		1,
		DXGI_FORMAT_R32_FLOAT,
		DXGI_FORMAT_D32_FLOAT,
		clearColor
	);


	Vector3 SunPosition;
	SunPosition = lig.DLight.GetDirection();
	SunPosition.Scale(4000.0f);

	SunparspectiveCam.SetTarget({ 0.0f,0.0f,0.0f });
	SunparspectiveCam.SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
	SunparspectiveCam.SetPosition(SunPosition * -1.0f);
	SunparspectiveCam.SetFar(10000.0f);
	SunparspectiveCam.SetUp({ 0.0f,1.0f,0.0f });
	SunparspectiveCam.SetHeight(512);
	SunparspectiveCam.SetWidth(512);
	SunparspectiveCam.Update();

	
}

void DepthShadow::Update(Light& lig)
{
	auto renderContext = g_graphicsEngine->GetRenderContext();

	Vector3 SunPosition;
	SunPosition = lig.DLight.GetDirection();
	SunPosition.Scale(4000.0f);

	SunparspectiveCam.SetPosition(SunPosition * -1.0f);
	SunparspectiveCam.Update();
	lig.LV.SetPrjMatrix(SunparspectiveCam.GetViewProjectionMatrix());	
}

void DepthShadow::DrawShadow(ModelInitData& SHModelData, RenderContext& RC)
{
	//auto renderContext = g_graphicsEngine->GetRenderContext();
	Model ShaModel;
	ShaModel.Init(SHModelData);

	RC.WaitUntilToPossibleSetRenderTarget(ShadowMap);
	RC.SetRenderTargetAndViewport(ShadowMap);
	RC.ClearRenderTargetView(ShadowMap);
	ShaModel.Draw(RC, SunparspectiveCam);
	RC.WaitUntilFinishDrawingToRenderTarget(ShadowMap);
}