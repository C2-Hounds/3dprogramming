#pragma once

class HamuHamu : public KdGameObject
{
public:
	HamuHamu();
	~HamuHamu()override;

	void Init()override;
	void Update()override;
	void DrawLit()override;

private:


	std::shared_ptr<KdSquarePolygon>	m_spPoly = nullptr;

	//コンストラクタの初期化をするとポインタの初期化
	//でうまく動作しない可能性がある


};

