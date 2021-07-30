#include "stdafx.h"
#include "DescriptorHeap.h"


DescriptorHeap::~DescriptorHeap()
{
	for (auto& ds : m_descriptorHeap) {
		if (ds) {
			ds->Release();
		}
	}
}
void DescriptorHeap::CommitSamperHeap()
{
	const auto& d3dDevice = g_graphicsEngine->GetD3DDevice();
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};

	srvHeapDesc.NumDescriptors = m_numSamplerDesc;
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

	for (auto& ds : m_descriptorHeap) {
		auto hr = d3dDevice->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&ds));
		if (FAILED(hr)) {
			MessageBox(nullptr, L"DescriptorHeap::Commit �f�B�X�N���v�^�q�[�v�̍쐬�Ɏ��s���܂����B", L"�G���[", MB_OK);
			std::abort();
		}
	}
	int bufferNo = 0;
	for (auto& descriptorHeap : m_descriptorHeap) {
		auto cpuHandle = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
		auto gpuHandle = descriptorHeap->GetGPUDescriptorHandleForHeapStart();
		for (int i = 0; i < m_numSamplerDesc; i++) {
			//�T���v���X�e�[�g���f�B�X�N���v�^�q�[�v�ɓo�^���Ă����B
			d3dDevice->CreateSampler(&m_samplerDescs[i], cpuHandle);
			cpuHandle.ptr += g_graphicsEngine->GetSapmerDescriptorSize();
		}
		m_samplerGpuDescriptorStart[bufferNo] = gpuHandle;
		bufferNo++;
	}

}
void DescriptorHeap::Commit()
{
	const auto& d3dDevice = g_graphicsEngine->GetD3DDevice();
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};

	srvHeapDesc.NumDescriptors = m_numShaderResource + m_numConstantBuffer + m_numUavResource;
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

	for (auto& ds : m_descriptorHeap) {
		auto hr = d3dDevice->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&ds));
		if (FAILED(hr)) {
			MessageBox(nullptr, L"DescriptorHeap::Commit �f�B�X�N���v�^�q�[�v�̍쐬�Ɏ��s���܂����B", L"�G���[", MB_OK);
			std::abort();
		}
	}
	//�萔�o�b�t�@��V�F�[�_�[���\�[�X�̃f�B�X�N���v�^���q�[�v�ɏ�������ł����B
	int bufferNo = 0;
	for (auto& descriptorHeap : m_descriptorHeap) {
		auto cpuHandle = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
		auto gpuHandle = descriptorHeap->GetGPUDescriptorHandleForHeapStart();

		//�萔�o�b�t�@��o�^���Ă����B
		for (int i = 0; i < m_numConstantBuffer; i++) {
			if (m_constantBuffers[i] != nullptr) {
				m_constantBuffers[i]->RegistConstantBufferView(cpuHandle, bufferNo);
			}
			//���ɐi�߂�B
			cpuHandle.ptr += g_graphicsEngine->GetCbrSrvDescriptorSize();
		}

		//�����ăV�F�[�_�[���\�[�X�B
		for (int i = 0; i < m_numShaderResource; i++) {
			if (m_shaderResources[i] != nullptr) {
				m_shaderResources[i]->RegistShaderResourceView(cpuHandle, bufferNo);
			}
			//���ɐi�߂�B
			cpuHandle.ptr += g_graphicsEngine->GetCbrSrvDescriptorSize();
		}

		//������UAV�B
		for (int i = 0; i < m_numUavResource; i++) {
			if (m_uavResoruces[i] != nullptr) {
				m_uavResoruces[i]->RegistUnorderAccessView(cpuHandle, bufferNo);
			}
			//���ɐi�߂�B
			cpuHandle.ptr += g_graphicsEngine->GetCbrSrvDescriptorSize();
		}

		//�萔�o�b�t�@�̃f�B�X�N���v�^�q�[�v�̊J�n�n���h�����v�Z�B
		m_cbGpuDescriptorStart[bufferNo] = gpuHandle;
		//�V�F�[�_�[���\�[�X�̃f�B�X�N���v�^�q�[�v�̊J�n�n���h�����v�Z�B
		m_srGpuDescriptorStart[bufferNo] = gpuHandle;
		m_srGpuDescriptorStart[bufferNo].ptr += (UINT64)g_graphicsEngine->GetCbrSrvDescriptorSize() * m_numConstantBuffer;
		//UAV���\�[�X�̃f�B�X�N���v�^�q�[�v�̊J�n�n���h�����v�Z�B
		m_uavGpuDescriptorStart[bufferNo] = gpuHandle;
		m_uavGpuDescriptorStart[bufferNo].ptr += (UINT64)g_graphicsEngine->GetCbrSrvDescriptorSize() * ( m_numShaderResource + m_numConstantBuffer );
		bufferNo++;
	}
}
