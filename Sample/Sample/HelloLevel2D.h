#pragma once
#include "level2D/Level2D.h"

/// <summary>
/// レベル2D処理のサンプルクラス。
/// </summary>
class HelloLevel2D : public IGameObject
{
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
private:
	Level2D m_level2D;		//レベル2D。
	Sprite m_sprite;			//スプライト。
	Vector3 m_position;		//座標。
	Vector3 m_scale;		//大きさ。
};

