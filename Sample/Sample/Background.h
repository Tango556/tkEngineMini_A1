#pragma once
/// <summary>
/// �w�i�N���X�B
/// </summary>
class Background : public IGameObject
{
public:
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc)override;
private:
	Model m_model;								//���f��
	PhysicsStaticObject m_physicsStaticObject;	//�ÓI�����I�u�W�F�N�g�E
};

