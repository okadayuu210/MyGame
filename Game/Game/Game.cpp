#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Stage.h"
#include "GameCamera.h"
#include "Enemy.h"


bool Game::Start()
{
	//“–‚½‚è”»’è‚ð—LŒø‰»‚·‚éB
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	return true;
}

Game::Game()
{
	m_stage=NewGO<Stage>(0, "stage");
	m_player=NewGO<Player>(0, "player");
	m_gamecamera=NewGO<GameCamera>(0, "GameCamera");
	m_enemy = NewGO<Enemy>(0, "enemy");
	

	el_render.Init("Assets/sprite/element.dds", 160.0f, 160.0f);
	el_render.SetPosition(Vector3(-880.0f, 460.0f, 0.0f));
}

void Game::Update()
{
	el_render.Update();
}

void Game::Render(RenderContext& rc)
{
	el_render.Draw(rc);

}