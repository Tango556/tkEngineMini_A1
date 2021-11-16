#pragma once
#include "Lighting.h"
#include "GaussianBlur.h"
class DepthShadow
{
public:
	void Init(Light& lig);
	void Init(Lighting& lig);
	void Update(Light& lig);
	void Update(Lighting& lig);
	void DrawShadow(ModelInitData& SHModelData, RenderContext& RC);
	void SetLigCameraPos(Vector3 LigCamPos)
	{
		SunparspectiveCam.SetPosition(LigCamPos);
	}
	Camera GetCamera()
	{
		return SunparspectiveCam;
	}
	RenderTarget& GetShadowMap()
	{
		return ShadowMap;
	}
	Texture& GetBluredSHD()
	{
		return GBlur.GetBlurredTexture();
	}
	//void DrawShadow(Model SHModel[]);
private:
	/// @brief シャドウマップの宣言
	RenderTarget ShadowMap;
	/// @brief ライトカメラ
	Camera SunparspectiveCam;
	//ModelInitData ShadowModelData;
	GaussianBlur GBlur;
};

