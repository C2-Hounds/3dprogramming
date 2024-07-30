#pragma once

class Moon;
class Earth:public KdGameObject
{
public:
	Earth() {}
	~Earth() {}

	void Init()override;

	void Update()override;

	void DrawLit()override;

	


private:

	std::shared_ptr<KdModelData> m_model=nullptr;

	std::shared_ptr<Moon> m_moon = nullptr;

	int rad;
	

};

