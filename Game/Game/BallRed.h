#pragma once
class BallRed :public IGameObject
{
public:
	BallRed();
	~BallRed();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	//void ColorState();

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

	int colorState = 0;

private:
	ModelRender				m_modelRender0;                   //モデルレンダー。
	ModelRender				m_modelRender1;                   //モデルレンダー。
	ModelRender				m_modelRender2;                   //モデルレンダー。
	Vector3					m_position;							//座標。
	Vector3                 emptyposition;                      //コリジョンの初期位置。
	Quaternion				m_rotation;							//回転。
	Vector3					m_scale = Vector3::One;				//大きさ。
	Vector3					m_moveSpeed;						//移動速度。
	float					m_timer = 0.0f;						//タイマー。
	CollisionObject* m_collisionObject = nullptr;			    //CollisionObject。



};

