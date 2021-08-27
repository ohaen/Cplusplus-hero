#include <iostream>
#include <ctime>
#include <conio.h>
#include <fstream>
#include "FileM.h"

using namespace std;

struct PlayerStatus
{
	string name;
	int hp=5;
	int gold=0;
};

struct enemyLife
{
	bool life;
};

int RSPGame(int reward)
{
	int enemyRsp;
	int playerRsp;
	bool checkGame=1;
	srand(time(NULL));



	while (checkGame)
	{
		enemyRsp = (rand() % 3)+1;
		cout << "상대가 낸건? " << enemyRsp << endl;

		cout << "가위바위보 게임을 시작합니다" << endl;
		cout << "1.가위    2.바위    3.보" << endl;
		cout << "선택하세요:";

		cin >> playerRsp;

		if (playerRsp != enemyRsp)
		{
			if (playerRsp == 1 && enemyRsp == 2)
			{
				cout << "당신 > 가위! \t\t\t 바위 < 적" << endl;
				cout << "졌습니다"  << endl;
				return 0;
			}
			else if (playerRsp == 2 && enemyRsp == 3)
			{
				cout << "당신 > 바위! \t\t\t 보 < 적" << endl;
				cout << "졌습니다" << endl;
				return 0;
			}
			else if (playerRsp == 3 && enemyRsp == 1)
			{
				cout << "당신 > 보! \t\t\t 가위 < 적" << endl;
				cout << "졌습니다" << endl;
				return 0;
			}
			else if (playerRsp == 1 && enemyRsp == 3)
			{
				cout << "당신 > 가위! \t\t\t 보 < 적" << endl;
				cout << "이겼습니다" << endl;
				return 1;
			}
			else if (playerRsp == 2 && enemyRsp == 1)
			{
				cout << "당신 > 바위! \t\t\t 가위 < 적" << endl;
				cout << "이겼습니다" << endl;
				return 1;
			}
			else if (playerRsp == 3 && enemyRsp == 2)
			{
				cout << "당신 > 보! \t\t\t 바위 < 적" << endl;
				cout << "이겼습니다" << endl;
				return 1;
			}
		}
		else
		{
			cout << "무승부입니다" << endl;
		}
	}

}


int main()
{

	int sizeX;
	int sizeY;
	cout << "맵 가로 사이즈를 입력하세요 : ";
	cin >> sizeX;
	cout << "맵 세로 사이즈를 입력하세요 : ";
	cin >> sizeY;


	int enemy = 0;

	if (sizeX * sizeY <= 50)			//사이즈에 따른 적 생성
	{
		cout << "설정된 적의 수는 " << 1 << "입니다." << endl;
		enemy = 1;
	}
	else
	{
		cout << "설정된 적의 수는 " << ((sizeX * sizeY) / 50) * 2 << "입니다." << endl;
		enemy = ((sizeX * sizeY) / 50)*2;
	}

	cout << "설정된 적 수 : " << enemy << endl;
	string** mapTile = new string * [sizeY];
	for (int i = 0; i < sizeY; i++)
	{
		mapTile[i] = new string[sizeX];
	}

	enemyLife* enemyHeart = new enemyLife[enemy];


	PlayerStatus player;
	cout << "플레이어 이름을 적어주세요 :";
	cin >> player.name;



	//	mapTile[size][size] = {};
	//int escapeTileX = 0;
	//int escapeTileY = 0;

	int* escapeTileX = new int[enemy];
	int* escapeTileY = new int[enemy];

	int playerX = 0;
	int playerY = 0;

	bool reset = true;
	bool gameLive = true;
	bool retry = 1;
	char checkRetry;
	int reward = 0;
	int enemyCount = enemy;

	int motion = 0;

	char wasd;
	FileM saveFile;						//입출력문 시작

	saveFile.ReadFile("save1.txt");		//파일을 불러옴
	if (saveFile.saveGold > 0)			//파일이 없다면 음수로 표시되므로 해당 조건으로 파일 있는지 확인
	{
	player.gold += saveFile.saveGold;
	cout << "저장된 돈은 " << saveFile.saveGold << "입니다." << endl;
	}

	srand(time(NULL));

	while (reset)				//적 숫자만큼 적 생성
	{



		for (int i = 0; i < enemy; i++)
		{
			escapeTileX[i] = rand() % sizeX;
			escapeTileY[i] = rand() % sizeY;
			enemyHeart[i].life = 1;

			//cout << escapeTileX[i] << endl;
			//cout << escapeTileY[i] << endl;
			//cout << enemyHeart[i].life << endl;
			cout << endl;
		}
		for (int i = 0; i < enemy; i++)
		{
			if (escapeTileX[i] == playerX && escapeTileY[i] == playerY)
			{
				reset = true;
				escapeTileX[i] = rand() % sizeX;
				escapeTileY[i] = rand() % sizeY;
				cout << "출구를 재설정 합니다." << endl;
			}
			else
			{
				reset = false;
				cout << "게임을 시작하려면 wasd중 아무키나 누르세요" << endl;
				break;
			}

		}

	}


	while (gameLive)				// 게임 진행
	{

		wasd = _getch();
		system("cls");
		
		cout << "플레이어 이름 :" << player.name << endl;
		cout << "소지 골드 :" << player.gold << endl;		//초기골드
		cout << "현재 체력 :" << player.hp << endl;			//초기체력
		cout << "남은 적의 수 :" << enemyCount << endl;		//남은 적 수
		cout << endl;


		switch (wasd)
		{
		case 'w':
		{
			if (playerY <= 0)
			{
				cout << "그쪽으로는 갈 수 없습니다." << endl;
			}
			else
			{
				playerY--;
			}
		}
		break;
		case 'a':
		{
			if (playerX <= 0)
			{
				cout << "그쪽으로는 갈 수 없습니다." << endl;
			}
			else
			{
				playerX--;
			}
		}
		break;
		case 's':
		{
			if (playerY >= (sizeY - 1))
			{
				cout << "그쪽으로는 갈 수 없습니다." << endl;
			}
			else
			{
				playerY++;
			}
		}
		break;
		case 'd':
		{
			if (playerX >= (sizeX - 1))
			{
				cout << "그쪽으로는 갈 수 없습니다." << endl;
			}
			else
			{
				playerX++;
			}
		}

		break;
		default:cout << "잘못 입력하였습니다." << endl;
		}

		for (int i = 0; i < sizeY; i++)
		{
			for (int j = 0; j < sizeX; j++)
			{
				mapTile[i][j] = "□";
			}
		}
		for (int i = 0; i < enemy; i++)
		{
			if (enemyHeart[i].life == 1)
			{
				mapTile[escapeTileY[i]][escapeTileX[i]] = "ㅈ";
			}
		}
		mapTile[playerY][playerX] = "★";
		if (motion == 0)
		{
			mapTile[playerY][playerX] = "★";
			motion++;
		}
		else
		{
			mapTile[playerY][playerX] = "☆";
			motion--;
		}






		for (int i = 0; i < sizeY; i++)
		{
			for (int j = 0; j < sizeX; j++)
			{
				cout << mapTile[i][j];
			}
			cout << endl;
		}
		for (int i = 0; i < enemy; i++)
		{
			if (escapeTileY[i] == playerY && escapeTileX[i] == playerX && enemyHeart[i].life == 1)
			{
				cout << "적 출현!" << endl;
				retry = 1;
				while (retry)
				{
					reward = RSPGame(reward);
					cout << reward << endl;
					if (reward == 1)
					{
						cout << "이겼다" << endl;
						enemyHeart[i].life = 0;
						player.gold += (rand() % 5) + 5;
						enemyCount--;
						retry = 0;
					}
					else
					{
						cout << "졌다" << endl;
						player.hp--;
						cout << "다시 도전 하시겠습니까? y/n :";
						cin >> checkRetry;
						checkRetry == 'y' ? retry = 1 : retry = 0;
					}
				}
				cout << "이동하세요!" << endl;
			}
		}

		if (player.hp == 0)
		{
			cout << "체력이 소진되어 게임이 끝납니다.";
			gameLive = 0;
		}
		else if (enemyCount == 0)
		{
			cout << "적을 모두 섬멸하여 게임을 이깁니다." << endl;
			cout << "획득한 골드를 가지고 갑니다." << endl;
			saveFile.WriteFile("save1.txt", player.gold);
			gameLive = 0;
		}


	}
//cout << "승리하여씁니다.";
//delete[] escapeTileX;
//delete[] escapeTileY;
//for (int i = 0; i < sizeY; i++)
//{
//	delete[] mapTile[i];
//}
//delete[] mapTile;
//gameLive = 0;
}