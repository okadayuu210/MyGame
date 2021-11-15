#pragma once

//�΂˃J�������g�p�������ꍇ�́ASpringCamera���C���N���[�h����B
#include "camera/SpringCamera.h"

class Player;

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

	void UpdatePositionAndTarget();

	Player* m_player = nullptr;		//�v���C���[�B
	Vector3 m_toCameraPos = Vector3::One;
	SpringCamera		m_springCamera;	//�΂˃J�����B
};

