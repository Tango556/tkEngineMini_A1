/*!
 * @brief	�R���C�_�[�B
 */

#pragma once

class btCollisionShape;
/// <summary>
/// �R���C�_�[�̃C���^�[�t�F�[�X�N���X�B
/// </summary>
class ICollider {
public:
	virtual btCollisionShape* GetBody() const = 0;
};
