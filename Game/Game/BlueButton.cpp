#include "stdafx.h"
#include "BlueButton.h"
#include "BallRed.h"
#include "Door.h"

#include "collision/CollisionObject.h"

bool BlueButton::Start()
{

	//���f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/Button/BlueButton.tkm");

	m_modelRender.SetPosition(m_position);

	m_modelRender.SetScale(m_scale);

	m_modelRender.SetRotation(m_rotation);

	m_modelRender.Update();

	//�R���W�����I�u�W�F�N�g���쐬����B
	m_collisionObject = NewGO<CollisionObject>(0);
	//�R���W�������쐬����B
	m_collisionObject->CreateBox(
		m_position,
		Quaternion::Identity,
		m_collisionScale
	);
		//���O��t����B
	m_collisionObject->SetName("blueButton");

	m_collisionObject->SetIsEnableAutoDelete(false);

	return true;
}

BlueButton::BlueButton()
{

}

BlueButton::~BlueButton()
{

}

void BlueButton::Update()
{
	//�v���C���[�̍U���p�̃R���W�������擾����B
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player_ball");
	//�R���W�����̔z���for���ŉ񂷁B
	for (auto collision : collisions)
	{
		//�R���W�����ƃL�����R�����Փ˂�����B
		if (collision->IsHit(m_collisionObject))
		{
				//�h�A�ɊJ���邱�Ƃ�ʒm����B
			FindGO<Door>("door")->SetDoorState(1);
			
		}
	}
}


void BlueButton::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}