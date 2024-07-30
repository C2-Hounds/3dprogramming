#include "CCTVCamera.h"

void CCTVCamera::Init()
{
	// 親クラスの初期化呼び出し
	CameraBase::Init();

	// 基準点(ターゲット)の目線
	m_mLocalPos = Math::Matrix::CreateTranslation(0, 6.0f, -10.0f);

	// 一旦行列を確定させる
	m_mWorld = m_mLocalPos;
}

void CCTVCamera::PostUpdate()
{
	// ターゲットの行列(有効な場合利用する)
	Math::Vector3								_targetPos = Math::Vector3::Zero;
	const std::shared_ptr<const KdGameObject>	_spTarget = m_wpTarget.lock();
	float yaw = 0;
	float pitch = 0;
	if (_spTarget)
	{
		_targetPos = _spTarget->GetPos();
		Math::Vector3 _targetVec = Math::Vector3::Zero;
		_targetVec = _targetPos - m_mLocalPos.Translation();

		//yaw角の計算
		yaw = DirectX::XMConvertToDegrees(atan2(_targetVec.x, _targetVec.z));
		//pitch角の計算
		pitch = DirectX::XMConvertToDegrees(atan2(_targetVec.y, sqrt(_targetVec.x * _targetVec.x + _targetVec.z * _targetVec.z)));
		

	}

	// カメラの回転
	UpdateLookAtRotate(_targetPos);

	Math::Matrix _rotateMat			= Math::Matrix::Identity;
	Math::Matrix _rotate_Yaw_Mat	= Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(yaw));
	Math::Matrix _rotate_Pitch_Mat	= Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(-pitch));

	_rotateMat =_rotate_Pitch_Mat* _rotate_Yaw_Mat;

	m_mWorld = _rotateMat * m_mLocalPos;

	
}

void CCTVCamera::UpdateLookAtRotate(const Math::Vector3& targetPos)
{
	// 方向ベクトルから角度を求める方法
	//_targetPos = _spTarget->GetPos();
	//Math::Vector3 _targetVec = Math::Vector3::Zero;
	//_targetVec = _targetPos - m_mLocalPos.Translation();

	////yaw角の計算
	//yaw = DirectX::XMConvertToDegrees(atan2(_targetVec.x, _targetVec.z));
	////pitch角の計算
	//pitch = DirectX::XMConvertToDegrees(atan2(_targetVec.y, sqrt(_targetVec.x * _targetVec.x + _targetVec.z * _targetVec.z)));


	// 
	//　XMMatrixLookAtLH:対象から見たときの行列を返す
	// LHおそらくLeftHand　左手座標系
	Math::Matrix _shaderVP= DirectX::XMMatrixLookAtLH(GetPos(), targetPos, Math::Vector3::Up);

	m_mWorld = _shaderVP.Invert();
}
