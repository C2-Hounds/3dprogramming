#include "Sun.h"
void Sun::Init()
{
	m_model=std::make_shared<KdModelData>();
	m_model->Load("Asset/Data/LessonData/Planets/sun.gltf");
	rad = 0;
}

void Sun::Update()
{
	rad++;
	if (rad > 360)
	{
		rad -= 360;
	}
	Math::Matrix _rotateXMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(rad));
	Math::Matrix _transMat = Math::Matrix::CreateTranslation(0, 0, 0);
	m_mWorld = _rotateXMat * _transMat;
}

void Sun::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model,m_mWorld);
}
