#include "stdafx.h"
#include "Player.h"

#include "BallRed.h"

bool Player::Start()
{
	//アニメーションクリップをロードする。
	animationClips[enAnimationClip_Idle].Load("Assets/animData/player/idle.tka");
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	animationClips[enAnimationClip_Walk].Load("Assets/animData/player/walk.tka");
	animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	animationClips[enAnimationClip_Jump].Load("Assets/animData/player/fall.tka");
	animationClips[enAnimationClip_Jump].SetLoopFlag(false);

	//モデルを読み込む。
	m_modelRender.Init("Assets/modelData/character/man.tkm", animationClips, enAnimationClip_Num);
	
	m_modelRender.SetScale({Vector3::One*1.9f });

	//sampleStage用
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

	//モデルを更新。
	m_modelRender.Update();
}

//移動処理
void Player::Move()
{
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//このフレームの移動量を求める。
	//左スティックの入力量を受け取る。
	float lStick_x = g_pad[0]->GetLStickXF();
	float lStick_y = g_pad[0]->GetLStickYF();
	//カメラの前方方向と右方向を取得。
	Vector3 cameraForward = g_camera3D->GetForward();
	Vector3 cameraRight = g_camera3D->GetRight();
	//XZ平面での前方方向、右方向に変換する。
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	//XZ成分の移動速度をクリア。
	m_moveSpeed += cameraForward * lStick_y * 250.0f;	//奥方向への移動速度を加算。
	m_moveSpeed += cameraRight * lStick_x * 250.0f;		//右方向への移動速度を加算。

	//キャラクターコントローラーを使用して、座標を更新。
	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	if (m_charaCon.IsOnGround()) {
		//地面についた。
		m_moveSpeed.y = 0.0f;
	}
	
	else
	{
		//落下処理。
		//980.0fが最初。
		m_moveSpeed.y -= 580.0f * g_gameTime->GetFrameDeltaTime();
	}
	
	Vector3 modelPosition = m_position;
	//ちょっとだけモデルの座標を挙げる。
	//modelPosition.y += 2.5f;
	m_modelRender.SetPosition(modelPosition);
}

//回転処理
void Player::Rotation()
{
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		//m_moveSpeed.xとm_moveSpeed.zの絶対値がともに0.001以下ということは
		//このフレームではキャラは移動していないので旋回する必要はない。
		return;
	}
	//atan2はtanθの値を角度(ラジアン単位)に変換してくれる関数。
	//m_moveSpeed.x / m_moveSpeed.zの結果はtanθになる。
	//atan2を使用して、角度を求めている。
	//これが回転角度になる。
	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);
	//atanが返してくる角度はラジアン単位なので
	//SetRotationDegではなくSetRotationを使用する。
	m_rotation.SetRotationY(-angle);

	//回転を設定する。
	m_modelRender.SetRotation(m_rotation);

	//プレイヤーの正面ベクトルを計算する。
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);
}

//ステート管理
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
		//エレメントボールを作成する。
		m_redBall = NewGO<BallRed>(0);
		RedBallPosition = m_position;
		//座標を少し上にする。
		RedBallPosition.y += 70.0f;
		RedBallPosition.x += 10.0f;
		//座標を設定する。
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

//アニメーションの再生
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
	//座標表示。
	int x = m_position.x;
	wchar_t zx[256];
	swprintf_s(zx, 256, L"X:%d", x);

	//表示するテキストを設定。
	fontRenderX.SetText(zx);
	//フォントの位置を設定。
	fontRenderX.SetPosition(Vector3(200.0f, 300.0f, 0.0f));
	//フォントの大きさを設定。
	fontRenderX.SetScale(1.0f);



	int y = m_position.y;
	wchar_t zy[256];
	swprintf_s(zy, 256, L"Y:%d", y);

	//表示するテキストを設定。
	fontRenderY.SetText(zy);
	//フォントの位置を設定。
	fontRenderY.SetPosition(Vector3(200.0f, 250.0f, 0.0f));
	//フォントの大きさを設定。
	fontRenderY.SetScale(1.0f);


	int z = m_position.z;
	wchar_t zz[256];
	swprintf_s(zz, 256, L"Z:%d", z);

	//表示するテキストを設定。
	fontRenderZ.SetText(zz);
	//フォントの位置を設定。
	fontRenderZ.SetPosition(Vector3(200.0f, 200.0f, 0.0f));
	//フォントの大きさを設定。
	fontRenderZ.SetScale(1.0f);
}

void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
	
	fontRenderX.Draw(rc);
	fontRenderY.Draw(rc);
	fontRenderZ.Draw(rc);
}