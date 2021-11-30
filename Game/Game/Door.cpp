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
	//�A�j���[�V������ǂݍ��ށB
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/door/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(false);
	m_animationClips[enAnimationClip_Open].Load("Assets/animData/door/open.tka");
	m_animationClips[enAnimationClip_Open].SetLoopFlag(false);
	
	//���f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/door/door.tkm", m_animationClips, enAnimationClip_Num);
	//���W��ݒ肷��B
	m_modelRender.SetPosition(m_position);
	//�傫����ݒ肷��B
	m_modelRender.SetScale(m_scale);
	//��]��ݒ肷��B
	m_modelRender.SetRotation(m_rotation);

	//���f���̍X�V�B
	m_modelRender.Update();
	//�����蔻����쐬����B
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	return true;
}

void Door::Update()
{
	//�A�j���[�V�������Đ�����B
	PlayAnimation();
	//�X�e�[�g�Ǘ��B
	ManageState();

	//���f���̍X�V�B
	m_modelRender.Update();
}

void Door::PlayAnimation()
{
	switch (m_doorState)
	{
	case 0:
		//�ҋ@�A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;

	case 1:
		//�I�[�v���A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimationClip_Open);
		m_modelRender.SetAnimationSpeed(0.6f);
		break;

	case 2:
		//�ҋ@�A�j���[�V�������Đ�����B
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
	//�I�[�v���X�e�[�g�ɑJ�ڂ���B
	m_doorState = 1;
}

void Door::ProcessOpenStateTransition()
{
	//�I�[�v���A�j���[�V�����̍Đ����I��������B
	if (m_modelRender.IsPlayingAnimation() == false)
	{
		//�����蔻����J������B
		ReleasePhysicsObject();
		//�I�[�v���I���X�e�[�g�ɑJ�ڂ���B
		m_doorState = 2;
	}
}

void Door::ReleasePhysicsObject()
{
	//�����蔻����J������B
	m_physicsStaticObject.Release();
	//CreatePhysicsObject();
}

void Door::CreatePhysicsObject()
{
	//�����蔻����쐬����B
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
}




void Door::Render(RenderContext& rc)
{
	//���f����`�悷��B
	m_modelRender.Draw(rc);
}
