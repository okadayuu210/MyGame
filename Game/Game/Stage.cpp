#include "stdafx.h"
#include "Stage.h"

Stage::Stage()
{
	
}

Stage::~Stage()
{

}

bool Stage::Start()
{

	//モデルを読み込む。
	m_modelRender.Init("Assets/modelData/stage/Stage.tkm");

	m_modelRender.SetPosition(m_position);

	m_modelRender.SetScale(m_scale);

	m_modelRender.SetRotation(m_rotation);

	m_modelRender.Update();
	//静的物理オブジェクトを作成。
	m_phyStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());


	return true;
}

void Stage::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}