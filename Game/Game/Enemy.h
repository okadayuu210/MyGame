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
	//�ړ�����
	void Move();
	//��]����
	void Rotation();
	//�X�e�[�g�Ǘ�
	void ManageState();
	//�A�j���[�V�����̍Đ�
	void PlayAnimation();
	//�_���[�W����
	void Damege();
	//hp�ɂ��킹�ĐF���ς�鏈��
	void HPcolor();
	//�C�⏈��
	void Death();



	void attack();
	// �A�j���[�V�����C�x���g�p�̊֐��B
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
	enum EnAnimationClip {		//�A�j���[�V�����B
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Hit,
		enAnimationClip_Attack,
		enAnimationClip_Num,
	};

	AnimationClip animationClips[enAnimationClip_Num];  //�A�j���[�V�����N���b�v�B

	ModelRender				m_modelRender;				//���f�������_�[�B
	CharacterController		m_charaCon;					//�L�����N�^�[�R���g���[���[�B
	Vector3					m_moveSpeed;				//�ړ����x�B
	Quaternion				m_rotation;					//��]�B
	int						playerState = 0;			//State�Ǘ��B
	Vector3					m_position;					//���W�B
	Vector3					m_forward = Vector3::AxisZ;	//�v���C���[�̐��ʃx�N�g���B
	Player*					m_player = nullptr;			//player�Ăяo���B
	int						m_elementState = 0;			//�G�������g�X�e�[�g�B
	int						m_killcount = 0;			//�|�������𐔂���B

	bool					m_BallDelete = false;		//

	int						m_hp = 0;					//�G��HP�B
	const int				m_Maxhp = 4;				//�G�̍ő�HP�B
	SpriteRender			m_SpriteHPBar;				//HP�o�[�̕\���B
	Vector2					m_spritePosition = Vector2::Zero;
	float					m_latetimer = 0.0f;			//�o�ߎ��ԁB


	int m_punchBoneId = -1;
	bool m_isUnderAttack = false;
};