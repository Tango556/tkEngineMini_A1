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
	SunparspectiveCam.SetHeight(2248);
	SunparspectiveCam.SetWidth(2248);
	SunparspectiveCam.Update();
	GBlur.Init(&ShadowMap.GetRenderTargetTexture());
}

void DepthShadow::Update(Light& lig)
{
	auto renderContext = g_graphicsEngine->GetRenderContext();

	Vector3 SunPosition;
	SunPosition = lig.DLight.GetDirection();
	SunPosition.Scale(4000.0f);
	GBlur.ExecuteOnGPU(renderContext, 1.38f);

	SunparspectiveCam.SetPosition(g_camera3D->GetTarget() + (SunPosition * -1.0f));
	SunparspectiveCam.SetTarget(g_camera3D->GetTarget());
	SunparspectiveCam.Update();
	lig.LV.SetPrjMatrix(SunparspectiveCam.GetViewProjectionMatrix());
	
}
void DepthShadow::Update(Lighting& lig)
{
	
}

void DepthShadow::DrawShadow(ModelInitData& SHModelData, RenderContext& RC)
{
	auto renderContext = g_graphicsEngine->GetRenderContext();
	Model ShaModel;
	ShaModel.Init(SHModelData);

	renderContext.WaitUntilToPossibleSetRenderTarget(ShadowMap);
	renderContext.SetRenderTargetAndViewport(ShadowMap);
	renderContext.ClearRenderTargetView(ShadowMap);
	ShaModel.Draw(RC, SunparspectiveCam);
	renderContext.WaitUntilFinishDrawingToRenderTarget(ShadowMap);
}