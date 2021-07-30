#include "stdafx.h"
#include "HelloLevel2D.h"

bool HelloLevel2D::Start()
{
	//レベルを読み込む。
	m_level2D.Init("Assets/level2D/sample.casl", [&](Level2DObjectData& objdata) {
		//名前がtitleだったら。
		if (objdata.EqualObjectName("title")) {

			SpriteInitData data;
			//DDSファイル(画像データ)のファイルパスを指定する。
			data.m_ddsFilePath[0] = objdata.ddsFilePath;
			//Sprite表示用のシェーダーのファイルパスを指定する。
			data.m_fxFilePath = "Assets/shader/sprite.fx";
			//スプライトの幅と高さを取得する。
			data.m_width = objdata.width;
			data.m_height = objdata.height;
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite.Init(data);
			//座標を取得する。
			m_position = objdata.position;
			//大きさを設定する。
			m_scale = objdata.scale;
			return true;
		}
		//名前がlogoだったら。
		else if (objdata.EqualObjectName("logo")) {

			//return falseにすると、
			//Level2DクラスのSpriteで画像が読み込まれます。
			return false;
		}
		return false;
	});

	return true;
}

void HelloLevel2D::Update()
{
	//タイトルを上下に動かす。
	static float t = 0.0f;
	t += g_gameTime->GetFrameDeltaTime();
	m_position.y += sinf( t );
	m_sprite.Update(m_position, Quaternion::Identity, m_scale);
	//レベル2DクラスのSpriteの更新処理。
	m_level2D.Update();
}

void HelloLevel2D::Render(RenderContext& rc)
{
	m_sprite.Draw(rc);
	//レベル2DクラスのSpriteの描画処理。
	m_level2D.Draw(rc);
}
