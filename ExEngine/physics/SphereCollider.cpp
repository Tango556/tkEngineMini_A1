/*!
* @brief	���̃R���C�_�[�B
*/

#include "stdafx.h"
#include "ExEngine.h"
#include "Physics.h"
#include "SphereCollider.h"


void SphereCollider::Create( const float radius )
{
	m_shape = std::make_unique<btSphereShape>(radius);
}
