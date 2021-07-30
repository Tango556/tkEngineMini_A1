#pragma once
class PhysicsBall : public IGameObject
{
public:
	bool Start() override;
	void Render(RenderContext& rc)override;
	void Update() override;
private:
	Model m_model;
	SphereCollider m_sphereCollider;
	RigidBody m_rigidBody;
};

