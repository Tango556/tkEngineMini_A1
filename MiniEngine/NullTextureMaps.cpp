#include "stdafx.h"
#include "NullTextureMaps.h"

void NullTextureMaps::Init()
{
	//�e��e�N�X�`�������[�h�B
	auto TexLoad = [&](
		const char* loadTexFilePath,
		std::unique_ptr<char[]>& outTexData,
		unsigned int& outTexSize
		) {
		FILE* fp = fopen(loadTexFilePath, "rb");
		if (fp == nullptr) {
			//null�e�N�X�`���̃��[�h�Ɏ��s�B
			MessageBoxA(nullptr, "null�e�N�X�`���̃��[�h�Ɏ��s���܂����B", "�G���[", MB_OK);
			std::abort();
		}
		//�e�N�X�`���T�C�Y���v�Z�B
		fseek(fp, 0L, SEEK_END);
		outTexSize = ftell(fp);
		fseek(fp, 0L, SEEK_SET);

		//���������m��
		outTexData = std::make_unique<char[]>(outTexSize);
		fread(outTexData.get(), outTexSize, 1, fp);
		fclose(fp);
	};

	//�A���x�h�}�b�v�����[�h�B
	TexLoad(
		"Assets/modelData/preset/NullAlbedoMap.DDS",
		m_albedoMap,
		m_albedoMapSize);

	//�@���}�b�v�����[�h�B
	TexLoad(
		"Assets/modelData/preset/NullNormalMap.DDS",
		m_normalMap,
		m_normalMapSize);

	//�O�̒l���i�[���Ă���}�b�v�����[�h�B
	TexLoad(
		"Assets/modelData/preset/ZeroValueMap.DDS",
		m_zeroValueMap,
		m_zeroValueMapSize);

}