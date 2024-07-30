#pragma once

class CameraBase : public KdGameObject
{
public:
	CameraBase()				{}
	~CameraBase()	override	{}

	void Init()		override;
	void Update()	override;

	void PreDraw()	override;


	void SetTarget(std::shared_ptr<KdGameObject> target)
	{
		// カメラのターゲットとしたいオブジェクト情報の設定
		m_wpTarget = target;
	}

	const Math::Matrix GetRotationMatrix() const
	{
		return Math::Matrix::CreateFromYawPitchRoll
		(
			DirectX::XMConvertToRadians(m_DegAng.y),
			DirectX::XMConvertToRadians(m_DegAng.x),
			DirectX::XMConvertToRadians(m_DegAng.z)
		);
	}

	const Math::Matrix GetRotationYMatrix() const
	{
		return Math::Matrix::CreateRotationY
				(DirectX::XMConvertToRadians(m_DegAng.y));
	}

	void RegistHitObject(const std::shared_ptr<KdGameObject>& object)
	{
		m_wpHitObjectList.push_back(object);
	}

protected:

	void UpdateRotateByMouse();


	std::shared_ptr<KdCamera>	m_spCamera = nullptr;	//カメラのスマポを格納する変数

	std::weak_ptr<KdGameObject> m_wpTarget;
	std::vector<std::weak_ptr<KdGameObject>> m_wpHitObjectList{};

	Math::Matrix				m_mLocalPos;			//座標行列
	Math::Matrix				m_mRotation;			//回転行列

	POINT						m_FixMousePos = {};
	//カメラの回転用角度
	Math::Vector3				m_DegAng;


	///※m_mLocalPos
	///最初の[m]はメンバー変数の意
	///二つ目の[m]は"Matrix"の意

	





};

