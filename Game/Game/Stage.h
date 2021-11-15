#pragma once
class Stage : public IGameObject
{
public:
	Stage();
private:
	~Stage();
	bool Start();
	void Render(RenderContext& rc);

	ModelRender m_modelRender;					//モデルレンダラー。
	PhysicsStaticObject m_phyStaticObject;		//静的物理オブジェクト。
};

