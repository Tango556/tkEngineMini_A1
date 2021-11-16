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
	/// @brief �V���h�E�}�b�v�̐錾
	RenderTarget ShadowMap;
	/// @brief ���C�g�J����
	Camera SunparspectiveCam;
	//ModelInitData ShadowModelData;
	GaussianBlur GBlur;
};

