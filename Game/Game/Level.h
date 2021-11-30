#pragma once

#include "Level3DRender/LevelRender.h"

class BlueButton;
class RedButton;
class GreenButton;
class Door;
class Stage;

class Level : public IGameObject
{
public:

	Level();

	~Level();

	//bool Start();

	void Update();

private:
	BlueButton*		blueButton;
	RedButton*		redButton;
	GreenButton*	greenButton;
	Door*			door;
	Stage*			stage;


	LevelRender m_levelRender;
};
