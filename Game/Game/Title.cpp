#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title::Title()
{
	spriteRender.Init("Assets/sprite/title.dds", 1920.0f, 1080.0f);
}

Title::~Title()
{

}

void Title::Update()
{
	//Abuttonを押したときの処理。Gameに移動する
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		DeleteGO(this);
		NewGO<Game>(0, "game");
	}
}

void Title::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
}