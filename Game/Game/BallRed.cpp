#include "stdafx.h"
#include "BallRed.h"

#include "Player.h"

//CollisionObject���g�p�������̂ŁA�t�@�C�����C���N���[�h����B
#include "collision/CollisionObject.h"

bool BallRed::Start()
{
	//���f����ǂݍ��ށB
	m_modelRender0.Init("Assets/modelData/Ball/RedBall.tkm");
	m_modelRender1.Init("Assets/modelData/Ball/GreenBall.tkm");
	m_modelRender2.Init("Assets/modelData/Ball/BlueBall.tkm");


	//�R���W�����I�u�W�F�N�g���쐬����B
	m_collisionObject = NewGO<CollisionObject>(0);
	//����̃R���W�������쐬����B
	m_collisionObject->CreateSphere(
		m_position,						//���W�B
		Quaternion::Identity,           //��]�B
		35.0f                           //���a�B
	);

	//�R���W�����I�u�W�F�N�g�������ō폜����Ȃ��悤�ɂ���B
	m_collisionObject->SetIsEnableAutoDelete(false);

	//�ړ����x���v�Z�B
	m_moveSpeed = Vector3::AxisZ;
	m_rotation.Apply(m_moveSpeed);
	m_position += m_moveSpeed * 50.0f;
	m_moveSpeed *= 1200.0f;
	m_rotation.AddRotationDegY(360.0f);

	colorState = FindGO<Player>("player")->elementState;

	return true;
}

BallRed::BallRed()
{

}

BallRed::~BallRed()
{
	//�R���W�����I�u�W�F�N�g���폜����B
	DeleteGO(m_collisionObject);
	//�G�t�F�N�g�̍Đ����~����B
	//m_effectEmitter->Stop();
	//�G�t�F�N�g���폜����B
	//DeleteGO(m_effectEmitter);
}



void BallRed::Update()
{
	//���W���ړ�������B
	m_position += m_moveSpeed * g_gameTime->GetFrameDeltaTime();
	//�R���W�����I�u�W�F�N�g�ɍ��W��ݒ肷��B
	m_collisionObject->SetPosition(m_position);

	//���f�����X�V�B
	if (colorState == 0) {
		m_modelRender0.SetPosition(m_position);
		m_modelRender0.Update();
	}
	else if (colorState == 1) {
		m_modelRender1.SetPosition(m_position);
		m_modelRender1.Update();
	}
	else if (colorState == 2) {
		m_modelRender2.SetPosition(m_position);
		m_modelRender2.Update();
	}

	//�^�C�}�[�����Z����B
	m_timer += g_gameTime->GetFrameDeltaTime();
	
	//�^�C�}�[��0.7f�ȏゾ������B
	if (m_timer >= 0.7f)
	{
		//���g���폜����B
		DeleteGO(this);
	}
}

void BallRed::Render(RenderContext& rc)
{
	if (colorState == 0) {
		m_modelRender0.Draw(rc);
	}
	else if (colorState == 1) {
		m_modelRender1.Draw(rc);
	}
	else if(colorState==2){
		m_modelRender2.Draw(rc);
	}
}