#include "Earth.h"
#include"Moon/Moon.h"
void Earth::Init()
{
	m_model=std::make_shared<KdModelData>();
	m_model->Load("Asset/Data/LessonData/Planets/earth.gltf");
	rad = 0;
	m_moon = std::make_shared<Moon>();
	m_moon->Init();
	
}

void Earth::Update()
{
	rad++;
	if (rad > 360)
	{
		rad -= 360;
	}
	Math::Matrix _rotateXMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(rad));
	Math::Matrix _transMat = Math::Matrix::CreateTranslation(0, 0, 5);
	m_mWorld = _rotateXMat* _transMat* _rotateXMat;

	
	m_moon->Update(m_mWorld);
	
	
	
}

void Earth::DrawLit()
{

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model,m_mWorld);
	m_moon->DrawLit();
}
