#pragma once

#include "HID/GamePad.h"

class GraphicsEngine;

class TkEngine {
public:
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~TkEngine();
	/// <summary>
	/// �t���[���̊J�n���ɌĂ΂�鏈���B
	/// </summary>
	void BeginFrame();
	/// <summary>
	/// �t���[���̏I�����ɌĂ΂�鏈���B
	/// </summary>
	void EndFrame();
	/// <summary>
	/// �Q�[���G���W���̏������B
	/// </summary>
	void Init(HWND hwnd, UINT frameBufferWidth, UINT frameBufferHeight);
private:
	GraphicsEngine* m_graphicsEngine = nullptr;		//�O���t�B�b�N�G���W���B
	GamePad m_pad[GamePad::CONNECT_PAD_MAX];		//�Q�[���p�b�h�B
	GameTime m_gameTime;							//�Q�[���^�C���B
	
};

extern TkEngine* g_engine;	//TK�G���W���B
extern GameTime* g_gameTime;