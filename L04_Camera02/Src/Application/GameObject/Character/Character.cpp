﻿#include "Character.h"
#include "../../main.h"
#include"../../GameObject/Camera/CameraBase.h"

void Character::Init()
{
	if (!m_spPoly)
	{
		m_spPoly = std::make_shared<KdSquarePolygon>();
		m_spPoly->SetMaterial("Asset/Data/LessonData/Character/Hamu.png");
		m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	}
}

void Character::Update()
{
	// キャラクターの移動速度(真似しちゃダメですよ)
	float moveSpd = 0.05f;
	Math::Vector3 nowPos = m_mWorld.Translation();

	Math::Vector3 moveVec = Math::Vector3::Zero;
	if (GetAsyncKeyState('D')) { moveVec.x = 1.0f; }
	if (GetAsyncKeyState('A')) { moveVec.x = -1.0f; }
	if (GetAsyncKeyState('W')) { moveVec.z = 1.0f; }
	if (GetAsyncKeyState('S')) { moveVec.z = -1.0f; }


	const std::shared_ptr<CameraBase> _spCamera = m_wpCamera.lock();
	if (_spCamera)
	{
		moveVec = moveVec.TransformNormal(moveVec, _spCamera->GetRotationYMatrix());
	}

	moveVec.Normalize();
	moveVec *= moveSpd;
	nowPos += moveVec;

	//キャラクターの回転角度を求める
	UpdateRotate(moveVec);

	// キャラクターのワールド行列を創る処理
	Math::Matrix _transMat = Math::Matrix::CreateTranslation(nowPos);
	Math::Matrix _rotateMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_WorldRot.y));
	//Math::Matrix _rotateMat = _spCamera->GetRotationYMatrix();
	m_mWorld = _rotateMat*_transMat;
}

void Character::DrawLit()
{
	if (!m_spPoly) return;

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}

void Character::UpdateRotate(Math::Vector3& _srcMoveVec)
{
	// 何も入力がない場合は処理しない
	//if (_srcMoveVec.Length() == 0.0f) return;
	//lengthは処理が重たいため純粋な長さを出すためには
	if (_srcMoveVec.LengthSquared() == 0.0f) return;
	
	//キャラの正面方向ベクトル
	Math::Vector3 _nowDir = GetMatrix().Backward();
	//※この環境では正面ベクトルはbackwardだが一般的にはforwardである
	_nowDir.Normalize();

	//移動方向のベクトル
	Math::Vector3 _targetDir = _srcMoveVec;
	_targetDir.Normalize();

	float _nowAng = atan2(_nowDir.x, _nowDir.z);
	_nowAng = DirectX::XMConvertToDegrees(_nowAng);

	float _TargetAng = atan2(_targetDir.x, _targetDir.z);
	_TargetAng = DirectX::XMConvertToDegrees(_TargetAng);

	//角度の差分を求める
	float _betweenAng = _TargetAng - _nowAng;
	if (_betweenAng > 180)
	{
		_betweenAng -= 360;
	}
	else if (_betweenAng < -180)
	{
		_betweenAng += 360;
	}

	float _rotateAng = std::clamp(_betweenAng, -8.0f, 8.0f);
	m_WorldRot.y += _rotateAng;
}

