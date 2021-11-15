#pragma once

class Title :public IGameObject
{
public:
	Title();
private:
	~Title();
	void Update();
	void Render(RenderContext& rc);

	SpriteRender spriteRender;
};