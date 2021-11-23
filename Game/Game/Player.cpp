#include "stdafx.h"
#include "Player.h"

#include "BallRed.h"

bool Player::Start()
{
	//�A�j���[�V�����N���b�v�����[�h����B
	animationClips[enAnimationClip_Idle].Load("Assets/animData/player/idle.tka");
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	animationClips[enAnimationClip_Walk].Load("Assets/animData/player/walk.tka");
	animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	animationClips[enAnimationClip_Jump].Load("Assets/animData/player/fall.tka");
	animationClips[enAnimationClip_Jump].SetLoopFlag(false);

	//���f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/character/man.tkm", animationClips, enAnimationClip_Num);
	
	m_modelRender.SetScale({Vector3::One*1.9f });

	//sampleStage�p
	//m_position = Vector3(0.0f, -81.0f, 0.0f);

	m_position = Vector3(0.0f, 0.0f, 0.0f);
	m_rotation.SetRotationDegY(180.0f);
	m_modelRender.SetRotation(m_rotation);
	m_charaCon.Init(25.0f, 80.0f, m_position);

	m_modelRender.Update();
	
	return true;
}

Player::Player()
{
	
}

Player::~Player()
{
	DeleteGO(m_redBall);
}


void Player::Update()
{
	Move();

	Rotation();

	ManageState();

	PlayAnimation();

	zahyou();

	attack();

	attackState();

	//���f�����X�V�B
	m_modelRender.Update();
}

//�ړ�����
void Player::Move()
{
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//���̃t���[���̈ړ��ʂ����߂�B
	//���X�e�B�b�N�̓��͗ʂ��󂯎��B
	float lStick_x = g_pad[0]->GetLStickXF();
	float lStick_y = g_pad[0]->GetLStickYF();
	//�J�����̑O�������ƉE�������擾�B
	Vector3 cameraForward = g_camera3D->GetForward();
	Vector3 cameraRight = g_camera3D->GetRight();
	//XZ���ʂł̑O�������A�E�����ɕϊ�����B
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	//XZ�����̈ړ����x���N���A�B
	m_moveSpeed += cameraForward * lStick_y * 250.0f;	//�������ւ̈ړ����x�����Z�B
	m_moveSpeed += cameraRight * lStick_x * 250.0f;		//�E�����ւ̈ړ����x�����Z�B

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
	//modelPosition.y += 2.5f;
	m_modelRender.SetPosition(modelPosition);
}

//��]����
void Player::Rotation()
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
void Player::ManageState()
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

void Player::attack()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//�G�������g�{�[�����쐬����B
		m_redBall = NewGO<BallRed>(0);
		RedBallPosition = m_position;
		//���W��������ɂ���B
		RedBallPosition.y += 70.0f;
		RedBallPosition.x += 10.0f;
		//���W��ݒ肷��B
		m_redBall->SetPosition(RedBallPosition);
		m_redBall->SetRotation(m_rotation);
	}
	
}

void Player::attackState()
{
	if (g_pad[0]->IsTrigger(enButtonLB1))
	{
		switch (m_elementState)
		{
		case 0:
			m_elementState = 1;
			break;
		case 1:
			m_elementState = 2;
			break;
		case 2:
			m_elementState = 0;
			break;
		default:
			break;
		}
	}
}

//�A�j���[�V�����̍Đ�
void Player::PlayAnimation()
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

void Player::zahyou()
{
	//���W�\���B
	int x = m_position.x;
	wchar_t zx[256];
	swprintf_s(zx, 256, L"X:%d", x);

	//�\������e�L�X�g��ݒ�B
	fontRenderX.SetText(zx);
	//�t�H���g�̈ʒu��ݒ�B
	fontRenderX.SetPosition(Vector3(200.0f, 300.0f, 0.0f));
	//�t�H���g�̑傫����ݒ�B
	fontRenderX.SetScale(1.0f);



	int y = m_position.y;
	wchar_t zy[256];
	swprintf_s(zy, 256, L"Y:%d", y);

	//�\������e�L�X�g��ݒ�B
	fontRenderY.SetText(zy);
	//�t�H���g�̈ʒu��ݒ�B
	fontRenderY.SetPosition(Vector3(200.0f, 250.0f, 0.0f));
	//�t�H���g�̑傫����ݒ�B
	fontRenderY.SetScale(1.0f);


	int z = m_position.z;
	wchar_t zz[256];
	swprintf_s(zz, 256, L"Z:%d", z);

	//�\������e�L�X�g��ݒ�B
	fontRenderZ.SetText(zz);
	//�t�H���g�̈ʒu��ݒ�B
	fontRenderZ.SetPosition(Vector3(200.0f, 200.0f, 0.0f));
	//�t�H���g�̑傫����ݒ�B
	fontRenderZ.SetScale(1.0f);
}

void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
	
	fontRenderX.Draw(rc);
	fontRenderY.Draw(rc);
	fontRenderZ.Draw(rc);
}