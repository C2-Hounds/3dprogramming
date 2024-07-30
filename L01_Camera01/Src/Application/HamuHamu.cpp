#include "HamuHamu.h"

HamuHamu::HamuHamu()
{
}

HamuHamu::~HamuHamu()
{
}

void HamuHamu::Init()
{
	m_spPoly = std::make_shared<KdSquarePolygon>();
	
	m_spPoly->SetMaterial("Asset/Data/LessonData/Character/Hamu.png");
	
	m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
}

void HamuHamu::Update()
{
	//ベクトル
			//Characterの移動速度（マネしちゃだめですよ）
	float moveSpd = 0.05f;
	//HamuWorldの41,42,43をvectorで送る処理
	Math::Vector3 nowPos = m_mWorld.Translation();

	//移動したい「方向ベクトル」=絶対に長さが「１」でなければならない！！！

	Math::Vector3 moveVec = Math::Vector3::Zero;
	//矢印を生成してる
	if (GetAsyncKeyState('W')) { moveVec.z = 1.0f; }

	if (GetAsyncKeyState('A')) { moveVec.x = -1.0f; }

	if (GetAsyncKeyState('S')) { moveVec.z = -1.0f; }

	if (GetAsyncKeyState('D')) { moveVec.x = 1.0f; }

	if (GetAsyncKeyState('R')) { moveVec.y = 1.0f; }

	if (GetAsyncKeyState('F')) { moveVec.y = -1.0f; }

	//正規化（ノーマライズ）
	moveVec.Normalize();
	moveVec *= moveSpd;
	nowPos += moveVec;

	//Characterのワールド行列を作る
	m_mWorld = Math::Matrix::CreateTranslation(nowPos);
}

void HamuHamu::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}
