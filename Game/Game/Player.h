#pragma once
class Player:public IGameObject
{
public:
	Player();

	
//private:
	bool Start();
	~Player();
	void Update();
	void Render(RenderContext& rc);
	//移動処理
	void Move();
	//回転処理
	void Rotation();
	//ステート管理
	void ManageState();
	//アニメーションの再生
	void PlayAnimation();
	//座標表示
	void zahyou();
	//攻撃処理
	void attack();
	//攻撃のState管理
	void attackState();

	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	const Vector3& GetPosition() const
	{
		return m_position;
	}

	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

	enum EnAnimationClip {		//アニメーション。
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Jump,
		enAnimationClip_Num,
	};

	AnimationClip animationClips[enAnimationClip_Num];//アニメーションクリップ。

	ModelRender m_modelRender;              //モデルレンダー。
	CharacterController m_charaCon;			//キャラクターコントローラー。
	Vector3 m_moveSpeed;					//移動速度。
	Quaternion m_rotation;
	int playerState = 0;
	Vector3 m_position;						//座標。
	Vector3	m_forward = Vector3::AxisZ;	    //プレイヤーの正面ベクトル。

	Vector3 RedBallPosition;
	int elementState = 0;



	FontRender fontRenderX;
	FontRender fontRenderY;
	FontRender fontRenderZ;
};

