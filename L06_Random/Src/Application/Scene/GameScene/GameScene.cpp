﻿#include "GameScene.h"
#include"../SceneManager.h"

#include "../../GameObject/Terrain/Terrain.h"
#include "../../GameObject/Character/Character.h"

#include "../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include "../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include "../../GameObject/Camera/CCTVCamera/CCTVCamera.h"
#include "../../main.h"


// 少数第n位で四捨五入する
void round_n(float& number, int n)
{
	number = number * pow(10, n - 1);
	number = round(number);
	number /= pow(10, n - 1);
}



void GameScene::Init()
{
	//===================================================================
	// ステージ初期化
	//===================================================================
	std::shared_ptr<Terrain> _terrain = std::make_shared<Terrain>();
	_terrain->Init();
	AddObject(_terrain);

	//===================================================================
	// キャラクター初期化
	//===================================================================
	std::shared_ptr<Character> _character = std::make_shared<Character>();
	_character->Init();
	AddObject(_character);

	//===================================================================
	// カメラ初期化
	//===================================================================
//	std::shared_ptr<FPSCamera>		_camera = std::make_shared<FPSCamera>();
//	std::shared_ptr<TPSCamera>		_camera = std::make_shared<TPSCamera>();
	std::shared_ptr<CCTVCamera>		_camera = std::make_shared<CCTVCamera>();
	_camera->Init();
	_camera->SetTarget(_character);
	_camera->RegistHitObject(_terrain);
	_character->SetCamera(_camera);
	AddObject(_camera);

	//===================================================================
	// 乱数実験場
	//===================================================================

	int randRes[10] = {};

	//// 如何にrand()が偏るか
	//srand((unsigned)time(NULL));
	//for (int i = 0 ;i <100000000 ; ++i)
	//{
	//	// 0～32767 % 10000
	//	int tmp = rand() % 10000;
	//	int idx = tmp / 1000;

	//	randRes[idx]++;
	//}
	//// 結果を出力
	//OutputDebugStringA("--------------------------------------------\n");
	//for (int i = 0; i < 10; ++i)
	//{
	//	std::stringstream ss;
	//	ss << "取得した値が" << i * 1000 << "～" << (i + 1) * 1000 <<
	//		"の件数:\t" << randRes[i] << " \n";
	//	std::string str = ss.str();
	//	OutputDebugStringA(str.c_str());

	//}
	//OutputDebugStringA("--------------------------------------------\n");

	//// メルセンヌツイスタ
	//for (int i = 0 ;i <100000000 ; ++i)
	//{
	//	// 0～32767 % 10000
	//	int tmp = KdGetInt(0,9999);
	//	int idx = tmp / 1000;

	//	randRes[idx]++;
	//}
	//// 結果を出力
	//OutputDebugStringA("--------------------------------------------\n");
	//for (int i = 0; i < 10; ++i)
	//{
	//	std::stringstream ss;
	//	ss << "取得した値が" << i * 1000 << "～" << (i + 1) * 1000 <<
	//		"の件数:\t" << randRes[i] << " \n";
	//	std::string str = ss.str();
	//	OutputDebugStringA(str.c_str());

	//}
	//OutputDebugStringA("--------------------------------------------\n");


	// レッスン１　CカードとRカードを50%で
	//int tmp = 0;
	//for (int i = 0 ;i <100000000 ; ++i)
	//{
	//	// 0～32767 % 10000
	//	tmp = KdGetInt(0,1000);
	//	int idx = tmp / 1000;

	//	randRes[idx]++;
	//}
	//// 結果を出力
	//OutputDebugStringA("--------------------------------------------\n");
	//int _rnd = KdGetInt(0, 1);
	//std::stringstream ss;
	//if (_rnd == 0)
	//{
	//	
	//	ss << "Cカードゲット" << " \n";
	//	std::string str = ss.str();
	//	OutputDebugStringA(str.c_str());
	//}
	//else
	//{
	//	ss << "Rカードゲット" << " \n";
	//	std::string str = ss.str();
	//	OutputDebugStringA(str.c_str());
	//}
	//OutputDebugStringA("--------------------------------------------\n");

	// レッスン2　Cカード->99.5%とRカードを0.5%で

	// 結果を出力

	/*int _bunbo = 1000;
	int ThusenNum = 100000000;
	int TosenNum[2] = { 0,0 };
	std::stringstream ss;
	for (int i = 0; i < ThusenNum; i++)
	{
		int rand = KdGetInt(0, 99999);
		if(rand>4)
		{
			TosenNum[0]++;
		}
		else
		{
			TosenNum[1]++;
		}
	}
	OutputDebugStringA("--------------------------------------------\n");

	float prob = 0;
	for (int i = 0; i <2; i++)
	{
		prob = ((float)TosenNum[i] / (float)ThusenNum) * 100;
		round_n(prob, 5);

		switch (i)
		{
		case 0:
			ss << "それ以外" << "当選回数=" << TosenNum[i] << "当選確率=" << prob << "%" << "\n" ;

			break;
		case 1:
			ss << "ピックアップから恒常が出る悲しみを背負う" << "当選回数=" << TosenNum[i] << "当選確率=" << prob << "%" << "\n";
			break;
		default:
			break;
		}
		std::string str = ss.str();
		OutputDebugStringA(str.c_str());
	}

	OutputDebugStringA("--------------------------------------------\n");*/


	// レッスン３：CカードRカードSRカードそれぞれ34,33,33で
	/*int _bunbo = 100;
	int randNum[3] = { 34,33,33 };
	int ThusenNum = 100000000;
	int TosenNum[3] = { 0,0,0 };
	std::stringstream ss;
	for (int i = 0; i < ThusenNum; i++)
	{
		int rand = KdGetInt(0, _bunbo - 1);
		for (int j = 0; j < std::size(randNum); j++)
		{
			rand -= randNum[j];
			if (rand < 0)
			{
				TosenNum[j]++;
				break;
			}
		}
	}
	OutputDebugStringA("--------------------------------------------\n");

	float prob = 0;
	for (int i = 0; i < std::size(TosenNum); i++)
	{
		prob = ((float)TosenNum[i] / (float)ThusenNum) * 100;
		round_n(prob, 3);

		switch (i)
		{
		case 0:
			ss << "Cカード" << "当選回数=" << TosenNum[i] << "当選確率=" << prob << "%" << "\n";

			break;
		case 1:
			ss << "Rカード" << "当選回数=" << TosenNum[i] << "当選確率=" << prob << "%" << "\n";
			break;
		case 2:
			ss << "SRカード" << "当選回数=" << TosenNum[i] << "当選確率=" << prob << "%" << "\n";


		}
		std::string str = ss.str();
		OutputDebugStringA(str.c_str());
	}

	OutputDebugStringA("--------------------------------------------\n");*/


	// レッスン4：CカードRカードSRカードそれぞれ50,49.5,0.5で
	int _bunbo = 1000;
	int randNum[3] = { 500,495,5 };
	int ThusenNum = 100000000;
	int TosenNum[3] = { 0,0,0 };
	std::stringstream ss;
	for (int i = 0; i < ThusenNum; i++)
	{
		int rand = KdGetInt(0, _bunbo - 1);
		for (int j = 0; j < std::size(randNum); j++)
		{
			rand -= randNum[j];
			if (rand < 0)
			{
				TosenNum[j]++;
				break;
			}
		}
	}
	OutputDebugStringA("--------------------------------------------\n");

	float prob = 0;
	for (int i = 0; i < std::size(TosenNum); i++)
	{
		prob = ((float)TosenNum[i] / (float)ThusenNum) * 100;
		round_n(prob, 3);

		switch (i)
		{
		case 0:
			ss << "Cカード" << "当選回数=" << TosenNum[i] << "当選確率=" << prob << "%" << "\n";

			break;
		case 1:
			ss << "Rカード" << "当選回数=" << TosenNum[i] << "当選確率=" << prob << "%" << "\n";
			break;
		case 2:
			ss << "SRカード" << "当選回数=" << TosenNum[i] << "当選確率=" << prob << "%" << "\n";


		}
		std::string str = ss.str();
		OutputDebugStringA(str.c_str());
	}

	OutputDebugStringA("--------------------------------------------\n");

	/*Application::Instance().m_log.AddLog("C_card:%d", C_count);
	Application::Instance().m_log.AddLog("R_card:%d", R_count);*/

}

void GameScene::Event()
{
}