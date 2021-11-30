#include "stdafx.h"
#include "Enemy.h"

#include "Player.h"
#include "collision/CollisionObject.h"

bool Enemy::Start()
{
	m_player = FindGO<Player>("player");

	//アニメーションクリップをロードする。
	animationClips[enAnimationClip_Idle].Load("Assets/animData/enemy/idle.tka");
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	animationClips[enAnimationClip_Walk].Load("Assets/animData/enemy/run.tka");
	animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	animationClips[enAnimationClip_Hit].Load("Assets/animData/enemy/hit.tka");
	animationClips[enAnimationClip_Hit].SetLoopFlag(false);
	animationClips[enAnimationClip_Attack].Load("Assets/animData/enemy/enemy_attack.tka");
	animationClips[enAnimationClip_Attack].SetLoopFlag(false);


	//アニメーションイベント用の関数を設定する。
	m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
		});


	m_punchBoneId = m_modelRender.FindBoneID(L"mixamorig:RightHandMiddle2");

	return true;
}

Enemy::Enemy()
{
	m_SpriteHPBar.Init("Assets/sprite/HP.dds", 100.0f, 100.0f);
	m_SpriteHPBar.SetPivot(Vector2(0.0f, 0.5f));

	m_SpriteHPBar.Update();
	m_hp = m_Maxhp;

	//モデルを読み込む。
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



	attack();


	Vector3 position = m_position;
	position.x += 10.0f;
	position.y += 130.0f;

	g_camera3D->CalcScreenPositionFromWorldPosition
		(m_spritePosition, position);
	m_SpriteHPBar.SetPosition
		(Vector3(m_spritePosition.x, m_spritePosition.y, 0.0f));

	//モデルを更新。
	m_modelRender.Update();

	m_SpriteHPBar.Update();
}

//移動処理
void Enemy::Move()
{
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	if (playerState != 3) {
		Vector3 diff = m_player->GetPosition() - m_position;
		diff.Normalize();
		//移動速度を設定する。250
		m_moveSpeed = diff * 150.0f;
	}

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
	
	m_modelRender.SetPosition(m_position);
}

//回転処理
void Enemy::Rotation()
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
void Enemy::ManageState()
{
	if (playerState != 3) {
		if (playerState != 4) {

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
}

//アニメーションの再生
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
		//アニメーションの再生が終わったら。
		if (m_modelRender.IsPlayingAnimation() == false)
		{
			playerState = 0;
			m_BallDelete = false;
		}
		break;
	case 4:
		m_modelRender.PlayAnimation(enAnimationClip_Attack);
		if(m_modelRender.IsPlayingAnimation() == false)
		{
			playerState = 0;
		}
	}
}

void Enemy::Damege()
{
	m_elementState = FindGO<Player>("player")->GetelementState();

	//プレイヤーの攻撃用のコリジョンを取得する。
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player_ball");
	//コリジョンの配列をfor文で回す。
	for (auto collision : collisions)
	{
		//コリジョンとキャラコンが衝突したら。
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


/// </summary>///

void Enemy::attack()
{
	Vector3 diff = m_player->GetPosition() - m_position;
	if (diff.Length() <= 65.0f)
	{
		playerState = 4;
	}


	//攻撃判定中であれば。
	if (m_isUnderAttack == true)
	{
		//攻撃用のコリジョンを作成する。
		//コリジョンオブジェクトを作成する。
		auto collisionObject = NewGO<CollisionObject>(0);

		Vector3 collisionPosition = m_position;
		//座標をプレイヤーの少し前に設定する。
		collisionPosition += m_forward * 50.0f;
		//球状のコリジョンを作成する。
		collisionObject->CreateSphere(collisionPosition,        //座標。
			Quaternion::Identity,                               //回転。
			10.0f                                               //半径。
		);
		collisionObject->SetName("enemy_attack");

		//「Sword」ボーンのワールド行列を取得する。
		Matrix matrix = m_modelRender.GetBone(m_punchBoneId)->GetWorldMatrix();
		//「Sword」ボーンのワールド行列をコリジョンに適用する。
		collisionObject->SetWorldMatrix(matrix);
	}
}



void Enemy::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	//キーの名前が「attack_start」の時。
	if (wcscmp(eventName, L"attack_start") == 0)
	{
		//攻撃中にする。
		m_isUnderAttack = true;
	}
	//キーの名前が「attack_end」の時。
	else if (wcscmp(eventName, L"attack_end") == 0)
	{
		//攻撃を終わる。
		m_isUnderAttack = false;
	}
}


///<summary>///


void Enemy::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
	m_SpriteHPBar.Draw(rc);
}