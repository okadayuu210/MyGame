#pragma once

class Player;

class Enemy :public IGameObject
{
public:
	Enemy();
	bool Start();
	~Enemy();
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
	//ダメージ処理
	void Damege();
	//hpにあわせて色が変わる処理
	void HPcolor();
	//気絶処理
	void Death();



	void attack();
	// アニメーションイベント用の関数。
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);


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

	const int GetKillCount() const
	{
		return m_killcount;
	}

	const bool GetBallDelete() const
	{
		return m_BallDelete;
	}

private:
	enum EnAnimationClip {		//アニメーション。
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Hit,
		enAnimationClip_Attack,
		enAnimationClip_Num,
	};

	AnimationClip animationClips[enAnimationClip_Num];  //アニメーションクリップ。

	ModelRender				m_modelRender;				//モデルレンダー。
	CharacterController		m_charaCon;					//キャラクターコントローラー。
	Vector3					m_moveSpeed;				//移動速度。
	Quaternion				m_rotation;					//回転。
	int						playerState = 0;			//State管理。
	Vector3					m_position;					//座標。
	Vector3					m_forward = Vector3::AxisZ;	//プレイヤーの正面ベクトル。
	Player*					m_player = nullptr;			//player呼び出し。
	int						m_elementState = 0;			//エレメントステート。
	int						m_killcount = 0;			//倒した数を数える。

	bool					m_BallDelete = false;		//

	int						m_hp = 0;					//敵のHP。
	const int				m_Maxhp = 4;				//敵の最大HP。
	SpriteRender			m_SpriteHPBar;				//HPバーの表示。
	Vector2					m_spritePosition = Vector2::Zero;
	float					m_latetimer = 0.0f;			//経過時間。


	int m_punchBoneId = -1;
	bool m_isUnderAttack = false;
};