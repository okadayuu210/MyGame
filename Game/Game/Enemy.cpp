#include "stdafx.h"
#include "Enemy.h"

#include "Player.h"

bool Enemy::Start()
{
	m_player = FindGO<Player>("player");

	//�A�j���[�V�����N���b�v�����[�h����B
	animationClips[enAnimationClip_Idle].Load("Assets/animData/blue/idle.tka");
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	animationClips[enAnimationClip_Walk].Load("Assets/animData/blue/run.tka");
	animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	animationClips[enAnimationClip_Hit].Load("Assets/animData/blue/hit.tka");
	animationClips[enAnimationClip_Hit].SetLoopFlag(false);

	return true;
}

Enemy::Enemy()
{
	m_SpriteHPBar.Init("Assets/sprite/HP.dds", 100.0f, 100.0f);
	m_SpriteHPBar.SetPivot(Vector2(0.0f, 0.5f));

	m_SpriteHPBar.Update();
	m_hp = m_Maxhp;

	//���f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/Enemy/BlueEnemy.tkm",
		animationClips, enAnimationClip_Num);
	m_modelRender.SetScale({ Vector3::One * 1.9f });

	m_position = Vector3(100.0f, 0.0f, 100.0f);
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

	Damege();

	PlayAnimation();

	HPcolor();

	Death();

	Vector3 position = m_position;
	position.x += 10.0f;
	position.y += 130.0f;

	g_camera3D->CalcScreenPositionFromWorldPosition
		(m_spritePosition, position);
	m_SpriteHPBar.SetPosition
		(Vector3(m_spritePosition.x, m_spritePosition.y, 0.0f));

	//���f�����X�V�B
	m_modelRender.Update();

	m_SpriteHPBar.Update();
}

//�ړ�����
void Enemy::Move()
{
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	if (playerState != 3) {
		Vector3 diff = m_player->GetPosition() - m_position;
		diff.Normalize();
		//�ړ����x��ݒ肷��B250
		m_moveSpeed = diff * 150.0f;
	}

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
	
	m_modelRender.SetPosition(m_position);
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
	if (playerState != 3) {

		if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
		{
			playerState = 2;
		}
		else
		{
			playerState = 0;
		}
	}
}

//�A�j���[�V�����̍Đ�
void Enemy::PlayAnimation()
{
	switch (playerState) {
	case 0:
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;
	case 2:
		m_modelRender.PlayAnimation(enAnimationClip_Walk);
		break;
	case 3:
		m_modelRender.PlayAnimation(enAnimationClip_Hit);
		//�A�j���[�V�����̍Đ����I�������B
		if (m_modelRender.IsPlayingAnimation() == false)
		{
			playerState = 0;
			m_BallDelete = false;
		}
		break;
	}
}

void Enemy::Damege()
{
	m_elementState = FindGO<Player>("player")->GetelementState();

	//�v���C���[�̍U���p�̃R���W�������擾����B
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player_ball");
	//�R���W�����̔z���for���ŉ񂷁B
	for (auto collision : collisions)
	{
		//�R���W�����ƃL�����R�����Փ˂�����B
		if (collision->IsHit(m_charaCon))
		{
			if (playerState != 3) {
				switch (m_elementState) {
				case 0:
					m_BallDelete = true;
					m_hp -= 1;
					playerState = 3;
					break;
				case 1:
					m_BallDelete = true;
					m_hp -= 4;
					playerState = 3;
					break;
				case 2:
					m_BallDelete = true;
					m_hp -= 2;
					playerState = 3;
					break;
				}
			}

		}

	}

	Vector3 scale = Vector3::One;
	scale.x = float(m_hp) / float(m_Maxhp);
	m_SpriteHPBar.SetScale(scale);
}

void Enemy::HPcolor()
{
	if (m_hp >= 3) {
		m_SpriteHPBar.SetMulColor(Vector4(0.0f, 1.0f, 0.0f, 1.0f));
	}
	else if (m_hp >= 2) {
		m_SpriteHPBar.SetMulColor(Vector4(1.0f, 1.0f, 0.0f, 1.0f));
	}
	else if (m_hp >= 1) {
		m_SpriteHPBar.SetMulColor(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	}
	else {
		m_SpriteHPBar.SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f));
	}
}

void Enemy::Death()
{
	if (m_hp <= 0)
	{
		m_killcount += 1;
		DeleteGO(this);
	}
}

void Enemy::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
	m_SpriteHPBar.Draw(rc);
}