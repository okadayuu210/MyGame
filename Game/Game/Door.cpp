#include "stdafx.h"
#include "Door.h"

Door::Door()
{
	
}

Door::~Door()
{

}

bool Door::Start()
{
	//アニメーションを読み込む。
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/door/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(false);
	m_animationClips[enAnimationClip_Open].Load("Assets/animData/door/open.tka");
	m_animationClips[enAnimationClip_Open].SetLoopFlag(false);
	
	//モデルを読み込む。
	m_modelRender.Init("Assets/modelData/door/door.tkm", m_animationClips, enAnimationClip_Num);
	//座標を設定する。
	m_modelRender.SetPosition(m_position);
	//大きさを設定する。
	m_modelRender.SetScale(m_scale);
	//回転を設定する。
	m_modelRender.SetRotation(m_rotation);

	//モデルの更新。
	m_modelRender.Update();
	//当たり判定を作成する。
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	return true;
}

void Door::Update()
{
	//アニメーションを再生する。
	PlayAnimation();
	//ステート管理。
	ManageState();

	//モデルの更新。
	m_modelRender.Update();
}

void Door::PlayAnimation()
{
	switch (m_doorState)
	{
	case 0:
		//待機アニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;

	case 1:
		//オープンアニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimationClip_Open);
		m_modelRender.SetAnimationSpeed(0.6f);
		break;

	case 2:
		//待機アニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimationClip_Open);
		break;
	default:
		break;
	}
}

void Door::ManageState()
{
	switch (m_doorState)
	{
	case 0:
		break;

	case 1:
		ProcessOpenStateTransition();
		break;

	case 2:
		break;

	default:
		break;
	}
}

void Door::NotifyOpen()
{
	//オープンステートに遷移する。
	m_doorState = 1;
}

void Door::ProcessOpenStateTransition()
{
	//オープンアニメーションの再生が終了したら。
	if (m_modelRender.IsPlayingAnimation() == false)
	{
		//当たり判定を開放する。
		ReleasePhysicsObject();
		//オープン終わりステートに遷移する。
		m_doorState = 2;
	}
}

void Door::ReleasePhysicsObject()
{
	//当たり判定を開放する。
	m_physicsStaticObject.Release();
	//CreatePhysicsObject();
}

void Door::CreatePhysicsObject()
{
	//当たり判定を作成する。
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
}




void Door::Render(RenderContext& rc)
{
	//モデルを描画する。
	m_modelRender.Draw(rc);
}
