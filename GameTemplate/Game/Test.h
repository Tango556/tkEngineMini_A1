#pragma once
#include "Lighting.h"
class Test : public IGameObject
{
public:
	Test();
	~Test();
	void Update();
	bool Start();

	void Init(Light& Lig);
	void SetPos(Vector3 pos)
	{
		m_pos = pos;
	}
	void SetRot(Quaternion rot)
	{
		m_rot = rot;
	}
	void Draw()
	{
		auto renderContext = g_graphicsEngine->GetRenderContext();
		m_model.Draw(renderContext);
	}
	Vector3 GetPos()
	{
		return m_pos;
	}
private:
	Model m_model;
	Vector3 m_pos;
	Quaternion m_rot;
	Vector3 m_scale = { 1.0f,1.0f,1.0f };
};

