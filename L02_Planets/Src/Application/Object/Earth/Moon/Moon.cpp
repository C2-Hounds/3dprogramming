#include "Moon.h"

void Moon::Init()
{
	m_model=std::make_shared<KdModelData>();
	m_model->Load("Asset/Data/LessonData/Planets/moon.gltf");
	rad = 0;
}

void Moon::Update(Math::Matrix _mat)
{
	rad+=3;
	if (rad > 360)
	{
		rad -= 360;
	}
	Math::Matrix _rotateXMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(rad));
	Math::Matrix _transMat;
	Math::Matrix _transMat2 = Math::Matrix::CreateTranslation(0, 0, 2);
	
	m_mWorld = _transMat2 * _rotateXMat* _mat;
	
}

void Moon::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model,m_mWorld);
}
