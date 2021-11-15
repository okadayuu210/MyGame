#pragma once
class Stage : public IGameObject
{
public:
	Stage();
private:
	~Stage();
	bool Start();
	void Render(RenderContext& rc);

	ModelRender m_modelRender;					//���f�������_���[�B
	PhysicsStaticObject m_phyStaticObject;		//�ÓI�����I�u�W�F�N�g�B
};

