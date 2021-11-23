#include "stdafx.h"
#include "GameOver.h"

#include "Title.h"

GameOver::GameOver()
{
	m_spriteRender.Init("Assets/sprite/over.dds", 1920.0f, 1080.0f);
}

GameOver::~GameOver()
{

}

void GameOver::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		DeleteGO(this);
		NewGO<Title>(0, "title");
	}
}

void GameOver::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}