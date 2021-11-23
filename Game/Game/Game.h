#pragma once

#include "Level3DRender/LevelRender.h"

//class�̌Ăяo���B
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
	//�����̕\���B
	Player*			m_player;										//�v���C���[�B
	Stage*			m_stage;										//�w�i�B
	GameCamera*		m_gamecamera;									//�Q�[���J�����B
	Enemy*			m_enemy;										//�G�B

	Vector3			m_position;										//player��y���W�B
	Vector3			m_circlePos0 = { -825.0f, 480.0f, 0.0f };		//�~�̍��W�B
	Vector3			m_circlePos1 = { -745.0f, 355.0f, 0.0f };		//�~�̍��W�B
	Vector3			m_circlePos2 = { -905.0f, 355.0f, 0.0f };		//�~�̍��W�B

	int				m_killcount;									//�G��|�������B
	int				m_elementState = 0;								//���݂̑������킩��₷�����邽�߂̃X�e�[�g�B

	SpriteRender	el_render;										//����̑��������\���B
	SpriteRender	circle_render;									//���̑����������~�\���B


	FontRender		m_fontRender;
};

