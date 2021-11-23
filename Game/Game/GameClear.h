#pragma once

class GameClear :public IGameObject
{
public:
	GameClear();
	~GameClear();
	void Update();
	void Render(RenderContext& rc);

private:
	SpriteRender	m_spriteRender;		//title‚Ì•\¦B
};