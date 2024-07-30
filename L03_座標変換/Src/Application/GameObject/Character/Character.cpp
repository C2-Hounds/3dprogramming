#include "Character.h"
#include"../../main.h"

void Character::Init()
{
	if (!m_spPoly)
	{
		m_spPoly = std::make_shared<KdSquarePolygon>();
		m_spPoly->SetMaterial("Asset/Data/LessonData/Character/Hamu.png");
		m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	}
	m_tex = std::make_shared<KdTexture>();
	m_tex->Load("Asset/Textures/nameber.png");
	
}

void Character::Update()
{
	if (GetAsyncKeyState(VK_RBUTTON))
	{
		// ①マウスの位置を取得
		POINT _mousePos;
		GetCursorPos(&_mousePos);
		ScreenToClient(Application::Instance().GetWindowHandle(),&_mousePos);

		std::shared_ptr<KdCamera>_cam = m_wpCam.lock();
		if (_cam)
		{
			Math::Vector3	_camPos		= _cam->GetCameraMatrix().Translation();
			Math::Vector3	_rayDir		= Math::Vector3::Zero;
			float			_rayRange = 100.0f;

			// ②レイの発射方向を求める
			_cam->GenerateRayInfoFromClientPos(_mousePos, _camPos, _rayDir, _rayRange);

			// ③実際にレイを飛ばして衝突位置を求める

			const std::shared_ptr<KdGameObject> _terrain = m_wpTerrain.lock();
			if (_terrain)
			{
				//どの方向にどれぐらい伸ばすか
				Math::Vector3 _endRayPos = (_rayDir * _rayRange);
				KdCollider::RayInfo _rayInfo(KdCollider::TypeGround,_camPos, _endRayPos);
				
				// 実際の当たり判定の処理
				std::list<KdCollider::CollisionResult> _results;
				_terrain->Intersects(_rayInfo,&_results);

				// 結果が一つでも帰ってきていたら
				//if(_result.size())でも可
				if (_results.size() > 0)
				{
					for (KdCollider::CollisionResult result : _results)
					{
						m_TargetPos = result.m_hitPos;
					}
				}
			}
		}
		

		

	}

	// キャラクターの移動速度(真似しちゃダメですよ)
	float moveSpd = 0.05f;
	//nowPos = m_mWorld.Translation();
	Math::Vector3 nowPos	= GetPos();
	Math::Vector3 moveVec	= m_TargetPos - nowPos;
	//自分が修正する場合
	/*{
		if (abs(moveVec.x) < 0.1f)
		{
			moveVec.x = 0;
		}
		if (abs(moveVec.y) < 0.1f)
		{
			moveVec.y = 0;
		}
		if (abs(moveVec.z) < 0.1f)
		{
			moveVec.z = 0;
		}
	}*/
	//先生の場合
	if (moveVec.Length() < moveSpd)
	{
		moveSpd = moveVec.Length();
	}
	
	moveVec.Normalize();
	moveVec *= moveSpd;
	nowPos += moveVec;


	// キャラクターのワールド行列を創る処理
	m_mWorld = Math::Matrix::CreateTranslation(nowPos);

	

}

void Character::DrawLit()
{
	if (!m_spPoly) return;

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}

void Character::DrawSprite()
{
	std::shared_ptr<KdCamera>_cam = m_wpCam.lock();
	if (_cam)
	{
		_cam->ConvertWorldToScreenDetail(GetPos(), resultPos);
	}
	resultPos.y += 130;
	//↓　この赤い点が常にハムスターの原点（足元）に追従するように！
	// ①ハムスターの3ハムスターの3D座標を2D座標へ変換する！
	Math::Rectangle _rect = { 0,0,300,50 };
	Math::Color _col = { 1,1,1,1 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_tex, resultPos.x, resultPos.y,&_rect, &_col);

	float length = 0.001f;
	
	
}
