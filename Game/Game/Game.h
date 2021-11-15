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

	//UnityChan�̕\���B
	//ModelRender m_modelRender;

	//�����̕\���B
	SpriteRender el_render;

	Player* m_player;				//�v���C���[�B
	Stage* m_stage;	            	//�w�i�B
	GameCamera* m_gamecamera;       //�Q�[���J�����B
	Enemy* m_enemy;					//�G�B
};

