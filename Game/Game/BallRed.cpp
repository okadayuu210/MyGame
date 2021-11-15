#include "stdafx.h"
#include "BallRed.h"

#include "Player.h"

//CollisionObjectを使用したいので、ファイルをインクルードする。
#include "collision/CollisionObject.h"

bool BallRed::Start()
{
	//モデルを読み込む。
	m_modelRender0.Init("Assets/modelData/Ball/RedBall.tkm");
	m_modelRender1.Init("Assets/modelData/Ball/GreenBall.tkm");
	m_modelRender2.Init("Assets/modelData/Ball/BlueBall.tkm");


	//コリジョンオブジェクトを作成する。
	m_collisionObject = NewGO<CollisionObject>(0);
	//球状のコリジョンを作成する。
	m_collisionObject->CreateSphere(
		m_position,						//座標。
		Quaternion::Identity,           //回転。
		35.0f                           //半径。
	);

	//コリジョンオブジェクトが自動で削除されないようにする。
	m_collisionObject->SetIsEnableAutoDelete(false);

	//移動速度を計算。
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
	//コリジョンオブジェクトを削除する。
	DeleteGO(m_collisionObject);
	//エフェクトの再生を停止する。
	//m_effectEmitter->Stop();
	//エフェクトを削除する。
	//DeleteGO(m_effectEmitter);
}



void BallRed::Update()
{
	//座標を移動させる。
	m_position += m_moveSpeed * g_gameTime->GetFrameDeltaTime();
	//コリジョンオブジェクトに座標を設定する。
	m_collisionObject->SetPosition(m_position);

	//モデルを更新。
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

	//タイマーを加算する。
	m_timer += g_gameTime->GetFrameDeltaTime();
	
	//タイマーが0.7f以上だったら。
	if (m_timer >= 0.7f)
	{
		//自身を削除する。
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