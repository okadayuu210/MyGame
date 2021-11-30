#include "stdafx.h"
#include "RedButton.h"
#include "BallRed.h"
#include "Door.h"

#include "collision/CollisionObject.h"

RedButton::RedButton()
{

}

RedButton::~RedButton()
{

}

bool RedButton::Start()
{

	//���f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/Button/RedButton.tkm");

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
	collisionObject->SetName("redButton");

	collisionObject->SetIsEnableAutoDelete(false);


	return true;
}

void RedButton::Update()
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

void RedButton::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}