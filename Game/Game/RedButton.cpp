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

	//モデルを読み込む。
	m_modelRender.Init("Assets/modelData/Button/RedButton.tkm");

	m_modelRender.SetPosition(m_position);

	m_modelRender.SetScale(m_scale);

	m_modelRender.SetRotation(m_rotation);

	m_modelRender.Update();

	//コリジョンオブジェクトを作成する。
	CollisionObject* collisionObject = NewGO<CollisionObject>(0);
	//コリジョンを作成する。
	collisionObject->CreateBox(
		m_position,
		Quaternion::Identity,
		m_collisionScale
	);
	//名前を付ける。
	collisionObject->SetName("redButton");

	collisionObject->SetIsEnableAutoDelete(false);


	return true;
}

void RedButton::Update()
{
	//プレイヤーの攻撃用のコリジョンを取得する。
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player_ball");
	//コリジョンの配列をfor文で回す。
	for (auto collision : collisions)
	{
		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_collisionObject))
		{
			//ドアに開けることを通知する。
			FindGO<Door>("door")->SetDoorState(1);

		}
	}
}

void RedButton::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}