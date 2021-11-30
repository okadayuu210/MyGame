#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Level.h"
#include "GameCamera.h"
#include "Enemy.h"

#include "GameOver.h"
#include "GameClear.h"

#include "RedButton.h"
#include "GreenButton.h"
#include "BlueButton.h"
#include "Door.h"
#include "Stage.h"


bool Game::Start()
{
	//当たり判定を有効化する。
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	return true;
}

Game::Game()
{
	m_level=NewGO<Level>(0, "level");

	//////////////////////////////


	m_player=NewGO<Player>(0, "player");
	m_gamecamera=NewGO<GameCamera>(0, "GameCamera");
	m_enemy = NewGO<Enemy>(0, "enemy");

	circle_render.Init("Assets/sprite/circle.dds", 102.0f, 102.0f);
	circle_render.SetPosition(m_circlePos0);
	//circle_render.SetPosition(Vector3(-825.0f, 480.0f, 0.0f));

	el_render.Init("Assets/sprite/element3.dds", 267.0f, 267.0f);
	el_render.SetPosition(Vector3(-825.0f, 405.0f, 0.0f));
}

Game::~Game()
{
	DeleteGO(m_level);
	DeleteGO(m_player);
	DeleteGO(m_gamecamera);

	const auto& enemys = FindGOs<Enemy>("enemy");
	//配列の個数を取得する
	int number = enemys.size();
	for (int i = 0; i < number; i++)
	{
		DeleteGO(enemys[i]);
	}
}

void Game::Update()
{
	//敵を倒す処理を試すためのコード。
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		m_enemy = NewGO<Enemy>(0, "enemy");
	}
	//ここまで。

	m_position = FindGO<Player>("player")->GetPosition();

	if (m_position.y <= -1000.0f)
	{
		DeleteGO(this);
		NewGO<GameOver>(0, "gameover");
	}

	Gameend();

	Circle();

	wchar_t zz[256];
	swprintf_s(zz, 256, L"Kill:%d", m_killcount);

	//表示するテキストを設定。
	m_fontRender.SetText(zz);
	//フォントの位置を設定。
	m_fontRender.SetPosition(Vector3(100.0f, 100.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontRender.SetScale(1.0f);

	circle_render.Update();
	el_render.Update();
}


void Game::Gameend()
{
	m_killcount = FindGO<Enemy>("enemy")->GetKillCount();

	if (m_killcount >= 5)
	{
		NewGO<GameClear>(0, "gameclear");
		DeleteGO(this);
	}
}


void Game::Circle()
{
	m_elementState = FindGO<Player>("player")->GetelementState();

	switch (m_elementState)
	{
	case 0:
		circle_render.SetPosition(m_circlePos0);
		break;
	case 1:
		circle_render.SetPosition(m_circlePos1);
		break;
	case 2:
		circle_render.SetPosition(m_circlePos2);
		break;
	default:
		break;
	}
}

void Game::Render(RenderContext& rc)
{
	m_fontRender.Draw(rc);
	circle_render.Draw(rc);
	el_render.Draw(rc);
}