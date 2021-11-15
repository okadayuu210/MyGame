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
	//�ړ�����
	void Move();
	//��]����
	void Rotation();
	//�X�e�[�g�Ǘ�
	void ManageState();
	//�A�j���[�V�����̍Đ�
	void PlayAnimation();
	//���W�\��
	void zahyou();
	//�U������
	void attack();
	//�U����State�Ǘ�
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

	enum EnAnimationClip {		//�A�j���[�V�����B
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Jump,
		enAnimationClip_Num,
	};

	AnimationClip animationClips[enAnimationClip_Num];//�A�j���[�V�����N���b�v�B

	ModelRender m_modelRender;              //���f�������_�[�B
	CharacterController m_charaCon;			//�L�����N�^�[�R���g���[���[�B
	Vector3 m_moveSpeed;					//�ړ����x�B
	Quaternion m_rotation;
	int playerState = 0;
	Vector3 m_position;						//���W�B
	Vector3	m_forward = Vector3::AxisZ;	    //�v���C���[�̐��ʃx�N�g���B

	Vector3 RedBallPosition;
	int elementState = 0;



	FontRender fontRenderX;
	FontRender fontRenderY;
	FontRender fontRenderZ;
};

