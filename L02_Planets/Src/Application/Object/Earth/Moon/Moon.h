#pragma once

class Moon:public KdGameObject
{
public:
	Moon() {}
	~Moon() {}

	void Init();

	void Update(Math::Matrix _mat);

	void DrawLit();

	void SetEarthMat(Math::Matrix _mat) { m_earthMat = _mat; }

	


private:

	std::shared_ptr<KdModelData> m_model=nullptr;

	Math::Matrix m_earthMat;

	int rad;

	
	

};

