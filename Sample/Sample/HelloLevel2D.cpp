#include "stdafx.h"
#include "HelloLevel2D.h"

bool HelloLevel2D::Start()
{
	//���x����ǂݍ��ށB
	m_level2D.Init("Assets/level2D/sample.casl", [&](Level2DObjectData& objdata) {
		//���O��title��������B
		if (objdata.EqualObjectName("title")) {

			SpriteInitData data;
			//DDS�t�@�C��(�摜�f�[�^)�̃t�@�C���p�X���w�肷��B
			data.m_ddsFilePath[0] = objdata.ddsFilePath;
			//Sprite�\���p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��B
			data.m_fxFilePath = "Assets/shader/sprite.fx";
			//�X�v���C�g�̕��ƍ������擾����B
			data.m_width = objdata.width;
			data.m_height = objdata.height;
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite.Init(data);
			//���W���擾����B
			m_position = objdata.position;
			//�傫����ݒ肷��B
			m_scale = objdata.scale;
			return true;
		}
		//���O��logo��������B
		else if (objdata.EqualObjectName("logo")) {

			//return false�ɂ���ƁA
			//Level2D�N���X��Sprite�ŉ摜���ǂݍ��܂�܂��B
			return false;
		}
		return false;
	});

	return true;
}

void HelloLevel2D::Update()
{
	//�^�C�g�����㉺�ɓ������B
	static float t = 0.0f;
	t += g_gameTime->GetFrameDeltaTime();
	m_position.y += sinf( t );
	m_sprite.Update(m_position, Quaternion::Identity, m_scale);
	//���x��2D�N���X��Sprite�̍X�V�����B
	m_level2D.Update();
}

void HelloLevel2D::Render(RenderContext& rc)
{
	m_sprite.Draw(rc);
	//���x��2D�N���X��Sprite�̕`�揈���B
	m_level2D.Draw(rc);
}
