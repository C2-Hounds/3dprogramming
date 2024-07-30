#pragma once

class Terrain:public KdGameObject
{
public:
	Terrain();
	~Terrain();

	void Init()override;
	void Update()override;
	void DrawLit()override;

private:


	std::shared_ptr<KdModelData>	m_spModel = nullptr;

	
};


