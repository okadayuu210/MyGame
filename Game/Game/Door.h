#pragma once

/// <summary>
/// ドア。
/// </summary>
class Door : public IGameObject
{
public:
	Door();
	~Door();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	
	void NotifyOpen();

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
	
	void SetDoorNumber(const int doorNumber)
	{
		m_doorNumber = doorNumber;
	}

	const int GetDoorNumber() const
	{
		return m_doorNumber;
	}


	void SetDoorState(const int doorState)
	{
		m_doorState = doorState;
	}

private:
	
	void PlayAnimation();
	
	void ReleasePhysicsObject();
	
	void CreatePhysicsObject();
	
	void ManageState();
	
	void ProcessOpenStateTransition();

public:

	Vector3						m_position;					//座標。
	Quaternion					m_rotation;					//回転。
	Vector3						m_scale;					//大きさ。

private:

	ModelRender					m_modelRender;				//モデルレンダ―。

	enum EnAnimationClip {					//アニメーション。
		enAnimationClip_Idle,				//待機。	
		enAnimationClip_Open,				//オープン。
		enAnimationClip_Num,				//アニメーションの数。
	};
	AnimationClip				m_animationClips[enAnimationClip_Num];	//アニメーションクリップ。
	PhysicsStaticObject			m_physicsStaticObject;					//フィジクススタティックオブジェクト。	
	int					m_doorState = 0;			//ドアステート。
	int							m_doorNumber = 0;						//ドアの番号。
};

