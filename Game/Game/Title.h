#pragma once

class Title :public IGameObject
{
public:
	Title();
	~Title();
	void Update();
	void Render(RenderContext& rc);

private:
	SpriteRender	spriteRender;//title‚Ì•\¦B
};