#pragma once

#pragma comment( lib, "xinput.lib")
#pragma comment(lib, "dxcompiler.lib")

#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <math.h>
#include <vector>
#include <list>
#include <D3Dcompiler.h>
#include <Windows.h>
#include <d3d12.h>
#include <map>
#include <functional>
#include <algorithm>
#include <DirectXMath.h>
#include <Xinput.h>
#include <array>
#include <dxcapi.h>
#include <atlbase.h>
#include <dxgi.h>
#include <dxgitype.h>
#include <dxgiformat.h>

#include "DirectXTK/Inc/CommonStates.h"
#include "DirectXTK/Inc/SpriteBatch.h"
#include "DirectXTK/Inc/SpriteFont.h"

#include "d3dx12.h"
#include "dbg/MyAssert.h"

#include "time/GameTime.h"
#include "math/Math.h"
#include "math/Vector.h"
#include "math/Matrix.h"

#include "TResourceBank.h"
#include "tkEngine.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "IShaderResource.h"
#include "IUnorderAccessResource.h"
#include "GPUBuffer.h"
#include "Texture.h"
#include "RWStructuredBuffer.h"
#include "StructuredBuffer.h"
#include "Shader.h"
#include "PipelineState.h"
#include "ConstantBuffer.h"
#include "RootSignature.h"
#include "raytracing/Raytracing.h"
#include "GraphicsEngine.h"
#include "DescriptorHeap.h"
#include "RenderTarget.h"
#include "Animation.h"
#include "font/Font.h"

#include "RenderContext_inline.h"
#include "DescriptorHeap_inline.h"

#include "Sprite.h"
#include "Model.h"
#include "HID/GamePad.h"

const UINT FRAME_BUFFER_W = 1280;				//�t���[���o�b�t�@�̕��B
const UINT FRAME_BUFFER_H = 720;				//�t���[���o�b�t�@�̍����B
static const int MAX_BONE = 512;	//!<�{�[���̍ő吔�B