#pragma once

class GreenButton : public IGameObject
{
public:
	GreenButton();
	~GreenButton();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void SetredButtonNum(const int number)
	{
		m_greenButtonNum = number;
	}

	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}

private:
	ModelRender			m_modelRender;			//モデルレンダラー。
	PhysicsStaticObject m_phyStaticObject;		//静的物理オブジェクト。


	Vector3				m_position;
	Vector3				m_scale;
	Quaternion			m_rotation;


	Vector3 m_collisionScale = { 20.0f,85.0f,95.0f };

	int m_greenButtonNum = 0;
	CollisionObject* m_collisionObject;

	int m_doorState;
};
