#include "stdafx.h"
#include "Stage.h"

Stage::Stage()
{

	//���f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/stage1/Stage1.tkm");

	m_modelRender.SetScale(Vector3(10.0f, 10.0f, 10.0f));

	/*
	//Y����180����]�B
	Quaternion rot;
	rot.SetRotationDegY(180.0f);
	//��]��ݒ�B
	m_modelRender.SetRotation(rot);
	//��]�̕ύX�𔽉f�����邽�߂ɁA���f�����X�V�B
	m_modelRender.Update();
	*/
	m_modelRender.Update();
	//�ÓI�����I�u�W�F�N�g���쐬�B
	m_phyStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

}

Stage::~Stage()
{

}

bool Stage::Start()
{
	return true;
}

void Stage::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}