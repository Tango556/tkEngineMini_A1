#pragma once
class Seesaw : public IGameObject
{
public:
	bool Start() override;
	void Render(RenderContext& rc)override;
	void Update() override;
private:
	Model m_model;
	BoxCollider m_boxCollider;
	RigidBody m_rigidBody;
};


