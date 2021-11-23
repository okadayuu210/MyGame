#pragma once

class BallRed;

class Player:public IGameObject
{
public:
	Player();
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

	const int GetelementState() const
	{
		return m_elementState;
	}

private:
	enum EnAnimationClip {		//アニメーション。
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Jump,
		enAnimationClip_Num,
	};

	AnimationClip animationClips[enAnimationClip_Num];		//アニメーションクリップ。

	ModelRender				m_modelRender;					//モデルレンダー。
	CharacterController		m_charaCon;						//キャラクターコントローラー。
	Vector3					m_moveSpeed;					//移動速度。
	Quaternion				m_rotation;						//回転。
	int						playerState = 0;				//アニメーションのステート。
	Vector3					m_position;						//座標。
	Vector3					m_forward = Vector3::AxisZ;		//プレイヤーの正面ベクトル。

	BallRed*				m_redBall;						//弾。
	Vector3					RedBallPosition;				//ボールの座標。
	int						m_elementState = 0;				//属性の変更のステート。

	FontRender				fontRenderX;					//プレイヤーのX座標表示。
	FontRender				fontRenderY;					//プレイヤーのY座標表示。
	FontRender				fontRenderZ;					//プレイヤーのZ座標表示。
};

