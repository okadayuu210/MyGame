#include "stdafx.h"
#include "GreenButton.h"
#include "BallRed.h"
#include "Door.h"

#include "collision/CollisionObject.h"

GreenButton::GreenButton()
{

}

GreenButton::~GreenButton()
{

}

bool GreenButton::Start()
{

	//���f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/Button/GreenButton.tkm");

	m_modelRender.SetPosition(m_position);

	m_modelRender.SetScale(m_scale);

	m_modelRender.SetRotation(m_rotation);

	m_modelRender.Update();

	//�R���W�����I�u�W�F�N�g���쐬����B
	CollisionObject* collisionObject = NewGO<CollisionObject>(0);
	//�R���W�������쐬����B
	collisionObject->CreateBox(
		m_position,
		Quaternion::Identity,
		m_collisionScale
	);
	//���O��t����B
	collisionObject->SetName("greenButton");

	collisionObject->SetIsEnableAutoDelete(false);

	return true;
}

void GreenButton::Update()
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

void GreenButton::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}