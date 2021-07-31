#include "stdafx.h"
#include "system/system.h"


///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	//////////////////////////////////////
	// �������珉�������s���R�[�h���L�q����B
	//////////////////////////////////////

	//�Q�[���I�u�W�F�N�g�}�l�[�W���[�̃C���X�^���X���쐬����B
	GameObjectManager::CreateInstance();
	PhysicsWorld::CreateInstance();

	/*struct DirectionLight
	{
		Vector3 ligDirection;
		float pad;
		Vector3 ligColor;
	};*/



	//DirectionLight dirLig;
	//dirLig.SetDirection({ 1.0f, -1.0f, -1.0f });
	////���K������
	//dirLig.ligDirection.Normalize();

	//dirLig.SetColor({ 1.0f,1.0f,1.0f });

	//dirLig.eyePos = g_camera3D->GetPosition();

	DirectionLight DLig;

	DLig.ligDirection.x = 0.0f;
	DLig.ligDirection.y = 1.0f;
	DLig.ligDirection.z = -0.5f;
	DLig.ligDirection.Normalize();

	DLig.DirColor.x = 0.0f;
	DLig.DirColor.y = 0.0f;
	DLig.DirColor.z = 0.0f;

	PointLight PLig;
	PLig.SetColor({ 1.0f, 0.0f, 0.0f });
	PLig.SetPLigPos({ 0.0f, 50.0f, 50.0f });
	PLig.SetRange(100.0f);

	Light Lig;
	Lig.DLight = DLig;
	Lig.PLight = PLig;

	/*Lig.ptColor.x = 15.0f;
	Lig.ptColor.y = 15.0f;
	Lig.ptColor.z = 15.0f;

	Lig.ptPosition.x = 0.0f;
	Lig.ptPosition.y = 50.0f;
	Lig.ptPosition.z = 50.0f;

	Lig.ptRange = 100.0f;*/

	//////////////////////////////////////
	// ���������s���R�[�h�������̂͂����܂ŁI�I�I
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	Model Uni;
	Model BackGround;

	ModelInitData uni;
	uni.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
	uni.m_fxFilePath = "Assets/shader/model.fx";

	uni.m_expandConstantBuffer = &Lig;
	uni.m_expandConstantBufferSize = sizeof(Lig);

	ModelInitData BG;
	BG.m_tkmFilePath = "Assets/modelData/bg/bg.tkm";
	BG.m_fxFilePath = "Assets/shader/model.fx";

	BG.m_expandConstantBuffer = &Lig;
	BG.m_expandConstantBufferSize = sizeof(Lig);

	Uni.Init(uni);
	BackGround.Init(BG);

	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		//�����_�����O�J�n�B
		g_engine->BeginFrame();
		
		PLig.PLigPosition.x -= g_pad[0]->GetLStickXF();
		if (g_pad[0]->IsPress(enButtonB)) {
			PLig.PLigPosition.y += g_pad[0]->GetLStickYF();
		}
		else {
			PLig.PLigPosition.z -= g_pad[0]->GetLStickYF();
		}

		Lig.DLight = DLig;
		Lig.PLight = PLig;
		//////////////////////////////////////
		//��������G��`���R�[�h���L�q����B
		//////////////////////////////////////
		
		GameObjectManager::GetInstance()->ExecuteUpdate();
		GameObjectManager::GetInstance()->ExecuteRender(renderContext);
		
		Uni.Draw(renderContext);
		BackGround.Draw(renderContext);
		//////////////////////////////////////
		//�G��`���R�[�h�������̂͂����܂ŁI�I�I
		//////////////////////////////////////
		g_engine->EndFrame();
	}
	//�Q�[���I�u�W�F�N�g�}�l�[�W���[���폜�B
	GameObjectManager::DeleteInstance();
	return 0;
}

