#include "stdafx.h"
#include "Enemy.h"

#include "Player.h"

bool Enemy::Start()
{
	m_player = FindGO<Player>("player");
	return true;
}

Enemy::Enemy()
{
	//�A�j���[�V�����N���b�v�����[�h����B
	animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	animationClips[enAnimationClip_Jump].SetLoopFlag(false);

	//���f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/unityChan.tkm",
		animationClips, enAnimationClip_Num, enModelUpAxisY);
	//0,40,235
	m_position = Vector3(100.0f, -81.0f, 100.0f);
	m_rotation.SetRotationDegY(180.0f);
	m_modelRender.SetRotation(m_rotation);
	m_charaCon.Init(25.0f, 75.0f, m_position);

}

Enemy::~Enemy()
{

}


void Enemy::Update()
{
	Move();

	Rotation();

	ManageState();

	PlayAnimation();

	//���f�����X�V�B
	m_modelRender.Update();
}

//�ړ�����
void Enemy::Move()
{
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	Vector3 diff = m_player->GetPosition() - m_position;
	diff.Normalize();
	//�ړ����x��ݒ肷��B250
	m_moveSpeed = diff * 150.0f;

	//�L�����N�^�[�R���g���[���[���g�p���āA���W���X�V�B
	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	if (m_charaCon.IsOnGround()) {
		//�n�ʂɂ����B
		m_moveSpeed.y = 0.0f;
	}

	else
	{
		//���������B
		//980.0f���ŏ��B
		m_moveSpeed.y -= 580.0f * g_gameTime->GetFrameDeltaTime();
	}

	Vector3 modelPosition = m_position;
	//������Ƃ������f���̍��W��������B
	modelPosition.y += 2.5f;
	m_modelRender.SetPosition(modelPosition);
}

//��]����
void Enemy::Rotation()
{
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		//m_moveSpeed.x��m_moveSpeed.z�̐�Βl���Ƃ���0.001�ȉ��Ƃ������Ƃ�
		//���̃t���[���ł̓L�����͈ړ����Ă��Ȃ��̂Ő��񂷂�K�v�͂Ȃ��B
		return;
	}
	//atan2��tan�Ƃ̒l���p�x(���W�A���P��)�ɕϊ����Ă����֐��B
	//m_moveSpeed.x / m_moveSpeed.z�̌��ʂ�tan�ƂɂȂ�B
	//atan2���g�p���āA�p�x�����߂Ă���B
	//���ꂪ��]�p�x�ɂȂ�B
	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);
	//atan���Ԃ��Ă���p�x�̓��W�A���P�ʂȂ̂�
	//SetRotationDeg�ł͂Ȃ�SetRotation���g�p����B
	m_rotation.SetRotationY(-angle);

	//��]��ݒ肷��B
	m_modelRender.SetRotation(m_rotation);

	//�v���C���[�̐��ʃx�N�g�����v�Z����B
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);
}

//�X�e�[�g�Ǘ�
void Enemy::ManageState()
{
	if (m_charaCon.IsOnGround() == false)
	{
		playerState = 1;

		return;
	}

	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		playerState = 2;
	}
	else
	{
		playerState = 0;
	}
}

//�A�j���[�V�����̍Đ�
void Enemy::PlayAnimation()
{
	switch (playerState) {
	case 0:
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;

	case 1:
		m_modelRender.PlayAnimation(enAnimationClip_Jump);
		break;

	case 2:
		m_modelRender.PlayAnimation(enAnimationClip_Walk);
		break;

	}
}

void Enemy::Chase()
{

}

void Enemy::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}