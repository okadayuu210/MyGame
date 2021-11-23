#pragma once
class Stage : public IGameObject
{
public:
	Stage();
	~Stage();
	bool Start();
	void Render(RenderContext& rc);

private:
	ModelRender			m_modelRender;			//モデルレンダラー。
	PhysicsStaticObject m_phyStaticObject;		//静的物理オブジェクト。
};

