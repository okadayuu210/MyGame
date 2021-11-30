#pragma once

class Stage : public IGameObject
{
public:
	Stage();
	~Stage();
	bool Start();
	void Render(RenderContext& rc);

	Vector3				m_position;
	Vector3				m_scale;
	Quaternion			m_rotation;

private:
	ModelRender			m_modelRender;			//���f�������_���[�B
	PhysicsStaticObject m_phyStaticObject;		//�ÓI�����I�u�W�F�N�g�B
};

