#pragma once

/// <summary>
/// �h�A�B
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

	Vector3						m_position;					//���W�B
	Quaternion					m_rotation;					//��]�B
	Vector3						m_scale;					//�傫���B

private:

	ModelRender					m_modelRender;				//���f�������_�\�B

	enum EnAnimationClip {					//�A�j���[�V�����B
		enAnimationClip_Idle,				//�ҋ@�B	
		enAnimationClip_Open,				//�I�[�v���B
		enAnimationClip_Num,				//�A�j���[�V�����̐��B
	};
	AnimationClip				m_animationClips[enAnimationClip_Num];	//�A�j���[�V�����N���b�v�B
	PhysicsStaticObject			m_physicsStaticObject;					//�t�B�W�N�X�X�^�e�B�b�N�I�u�W�F�N�g�B	
	int					m_doorState = 0;			//�h�A�X�e�[�g�B
	int							m_doorNumber = 0;						//�h�A�̔ԍ��B
};

