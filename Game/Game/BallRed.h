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
	ModelRender				m_modelRender0;                   //���f�������_�[�B
	ModelRender				m_modelRender1;                   //���f�������_�[�B
	ModelRender				m_modelRender2;                   //���f�������_�[�B
	Vector3					m_position;							//���W�B
	Vector3                 emptyposition;                      //�R���W�����̏����ʒu�B
	Quaternion				m_rotation;							//��]�B
	Vector3					m_scale = Vector3::One;				//�傫���B
	Vector3					m_moveSpeed;						//�ړ����x�B
	float					m_timer = 0.0f;						//�^�C�}�[�B
	CollisionObject* m_collisionObject = nullptr;			    //CollisionObject�B



};

