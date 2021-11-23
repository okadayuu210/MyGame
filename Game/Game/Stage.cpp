#include "stdafx.h"
#include "Stage.h"

Stage::Stage()
{

	//モデルを読み込む。
	m_modelRender.Init("Assets/modelData/stage1/Stage1.tkm");

	m_modelRender.SetScale(Vector3(10.0f, 10.0f, 10.0f));

	/*
	//Y軸に180°回転。
	Quaternion rot;
	rot.SetRotationDegY(180.0f);
	//回転を設定。
	m_modelRender.SetRotation(rot);
	//回転の変更を反映させるために、モデルを更新。
	m_modelRender.Update();
	*/
	m_modelRender.Update();
	//静的物理オブジェクトを作成。
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