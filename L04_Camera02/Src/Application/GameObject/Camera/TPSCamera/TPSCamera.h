﻿#pragma once
#include"../CameraBase.h"

class TPSCamera : public CameraBase
{
public:

	TPSCamera() {}
	~TPSCamera()		override {}

	void Init()			override;
	void Update()		override;
	void PostUpdate()	override;

private:

	Math::Vector3	nowPos = Math::Vector3::Zero;

	float MaxRange = 0;


};