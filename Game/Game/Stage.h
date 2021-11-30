#pragma once

class Stage : public IGameObject
{
public:
	Stage();
	~Stage();
	bool Start();
	void Render(RenderContext& rc);

	Vector3				m_position;
	Vector3				m_scale;
	Quaternion			m_rotation;

private:
	ModelRender			m_modelRender;			//モデルレンダラー。
	PhysicsStaticObject m_phyStaticObject;		//静的物理オブジェクト。
};

