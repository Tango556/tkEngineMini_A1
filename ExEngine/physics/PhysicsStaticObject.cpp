/*!
* @brief	�ÓI�I�u�W�F�N�g�B
*/


#include "stdafx.h"
#include "physics/PhysicsStaticObject.h"

PhysicsStaticObject::PhysicsStaticObject()
{
}
PhysicsStaticObject::~PhysicsStaticObject()
{
}
void PhysicsStaticObject::CreateFromModel(Model& model, const Matrix& worldMatrix)
{
	m_meshCollider.CreateFromModel(model, worldMatrix);
	RigidBodyInitData rbInfo;
	rbInfo.collider = &m_meshCollider;
	rbInfo.mass = 0.0f;
	m_rigidBody.Init(rbInfo);
}
