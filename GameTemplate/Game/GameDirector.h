#pragma once
#include"Lighting.h"
#include"SkinModelRender.h"
#include"KTypeBloom.h"


class GameDirector : public IGameObject
{
public:
	GameDirector();

	~GameDirector();

	bool Start();

	void Update();
private:
	enum GAME_STATE {enGame, };
};

