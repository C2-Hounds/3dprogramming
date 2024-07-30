﻿#include"CameraBase.h"

void CameraBase::Init()
{
	if (!m_spCamera)
	{
		m_spCamera = std::make_shared<KdCamera>();
	}
}

void CameraBase::Update()
{
	if (!m_spCamera) return;	//nullチェック
	//カメラ制御はm_mWorldをいじり倒すためこの行は大事

	m_spCamera->SetCameraMatrix(m_mWorld);
}

void CameraBase::PreDraw()
{
	if (!m_spCamera) return;

	//				↓シャーダープログラムに情報を渡す処理
	m_spCamera->SetToShader();
}

void CameraBase::UpdateRotateByMouse()
{
	POINT nowPos;
	GetCursorPos(&nowPos);

	//マウスカーソルの差分を求める
	POINT mouseMove{};
	mouseMove.x = nowPos.x - m_FixMousePos.x;
	mouseMove.y = nowPos.y - m_FixMousePos.y;

	//マウスカーソルを再度画面中央へ固定
	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	// 上の差分を基にカメラの回転角度を求める
	m_DegAng.x += mouseMove.y * 0.15f;
	m_DegAng.y += mouseMove.x * 0.15f;

	//※0.15f：差分値（マウス感度的な感じやで）

}