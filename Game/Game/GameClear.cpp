#include "stdafx.h"
#include "GameClear.h"

#include "Title.h"

GameClear::GameClear()
{
	m_spriteRender.Init("Assets/sprite/clear.dds", 1920.0f, 1080.0f);
}

GameClear::~GameClear()
{

}

void GameClear::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		DeleteGO(this);
		NewGO<Title>(0, "title");
	}
}

void GameClear::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}