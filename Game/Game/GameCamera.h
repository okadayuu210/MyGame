#pragma once

//ばねカメラを使用したい場合は、SpringCameraをインクルードする。
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

	Player* m_player = nullptr;		//プレイヤー。
	Vector3 m_toCameraPos = Vector3::One;
	SpringCamera		m_springCamera;	//ばねカメラ。
};

