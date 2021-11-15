#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class Stage;
class GameCamera;
class Enemy;

class Game : public IGameObject
{
public:
	Game();

private:
	~Game(){}
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	//UnityChanの表示。
	//ModelRender m_modelRender;

	//属性の表示。
	SpriteRender el_render;

	Player* m_player;				//プレイヤー。
	Stage* m_stage;	            	//背景。
	GameCamera* m_gamecamera;       //ゲームカメラ。
	Enemy* m_enemy;					//敵。
};

