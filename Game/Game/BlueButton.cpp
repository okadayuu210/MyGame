#include "stdafx.h"
#include "BlueButton.h"
#include "BallRed.h"
#include "Door.h"

#include "collision/CollisionObject.h"

bool BlueButton::Start()
{

	//モデルを読み込む。
	m_modelRender.Init("Assets/modelData/Button/BlueButton.tkm");

	m_modelRender.SetPosition(m_position);

	m_modelRender.SetScale(m_scale);

	m_modelRender.SetRotation(m_rotation);

	m_modelRender.Update();

	//コリジョンオブジェクトを作成する。
	m_collisionObject = NewGO<CollisionObject>(0);
	//コリジョンを作成する。
	m_collisionObject->CreateBox(
		m_position,
		Quaternion::Identity,
		m_collisionScale
	);
		//名前を付ける。
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


void BlueButton::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}