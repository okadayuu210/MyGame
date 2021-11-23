#pragma once

#include "Level3DRender/LevelRender.h"

//classの呼び出し。
class Player;
class Stage;
class GameCamera;
class Enemy;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Gameend();
	void Circle();
	void Render(RenderContext& rc);

private:
	//属性の表示。
	Player*			m_player;										//プレイヤー。
	Stage*			m_stage;										//背景。
	GameCamera*		m_gamecamera;									//ゲームカメラ。
	Enemy*			m_enemy;										//敵。

	Vector3			m_position;										//playerのy座標。
	Vector3			m_circlePos0 = { -825.0f, 480.0f, 0.0f };		//円の座標。
	Vector3			m_circlePos1 = { -745.0f, 355.0f, 0.0f };		//円の座標。
	Vector3			m_circlePos2 = { -905.0f, 355.0f, 0.0f };		//円の座標。

	int				m_killcount;									//敵を倒した数。
	int				m_elementState = 0;								//現在の属性をわかりやすくするためのステート。

	SpriteRender	el_render;										//左上の属性相性表示。
	SpriteRender	circle_render;									//今の属性を示す円表示。


	FontRender		m_fontRender;
};

