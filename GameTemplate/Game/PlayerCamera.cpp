#include "stdafx.h"
#include "PlayerCamera.h"

void PlayerCamera::SetPosition(Vector3 p)
{
	eyePosition = p;
}

void PlayerCamera::SetTarget(Vector3 t)
{
	targetPosition = t;
}

void PlayerCamera::SetDistance(Vector3 d)
{
	targetDistance = d;
}

void PlayerCamera::Update()
{
	g_camera3D->SetPosition(eyePosition);
	g_camera3D->SetTarget(targetPosition);
	g_camera3D->SetFar(maxFar);
	g_camera3D->SetNear(maxNear);
	g_camera3D->SetViewAngle(1.5f);
}

void PlayerCamera::SetFar(float f)
{
	maxFar = f;
	g_camera3D->SetFar(maxFar);
}

void PlayerCamera::SetNear(float n)
{
	maxNear = n;
	g_camera3D->SetNear(n);
}