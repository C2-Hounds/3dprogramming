#pragma once

class Sun:public KdGameObject
{
public:
	Sun() {}
	~Sun() {}

	void Init()override;

	void Update()override;

	void DrawLit()override;


private:

	std::shared_ptr<KdModelData> m_model=nullptr;

	int rad;
	

};

