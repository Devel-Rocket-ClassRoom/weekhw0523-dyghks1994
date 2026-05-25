#include "Homework04.h"

#include <iostream>
#include <stdio.h>
#include "Homework05.h"

using namespace std;

// 5. 미로 탈출 게임에 랜덤 인카운터를 추가하여 적과의 턴제 전투 만들기
// Homework05_Run(); 함수로 실행 가능해야 함.
// HP는 100으로 시작
// 공격을 할 때 상대방에게 5~15의 데미지를 준다.
// 10 % 의 확률로 크리티컬이 발생해 2배의 데미지를 준다.
// 상대방의 HP가 0 이하가 되면 승리한다.

void Homework05_Run()
{
	// 미로 크기
	const int MazeRows = 10;
	const int MazeCols = 20;

	// 미로 배열

	int Maze[MazeRows][MazeCols] =
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,2,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,1,0,1},
		{1,1,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,0,1},
		{1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1},
		{1,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
		{1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1},
		{1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1},
		{1,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,3,1},
		{1,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	//*/

	// 플레이어 위치 변수 시작위치로 초기화
	int PlayerPosY = 1;
	int PlayerPosX = 1;

	// 골인지점 위치 초기화
	int GoalPosY = 7;
	int GoalPosX = 18;

	//  골 도착 여부
	bool bGoal = false;

	char PlayerInput = 0;

	int PlayerHp = 100;		// 플레이어 Hp 초기화
	int EnemyHp = 50;		// 적 Hp 초기화

	printf("== = 미로 탈출 게임 Ver2 == =\n");
	//PrintMaze(&Maze[0][0], MazeRows, MazeCols);
	PrintMaze(*Maze, MazeRows, MazeCols, PlayerPosX, PlayerPosY);

	do
	{
		printf("이동할 수 있는 방향을 선택하세요(w: 위, s : 아래, a : 왼쪽, d : 오른쪽) :\n");
		printf("w(↑) s(↓) a(←) d(→)\n");

		cin >> PlayerInput;
		cin.clear();
		cin.ignore(10000, '\n');

		// 이동하려는 위치 변수 현재 위치로 초기화
		int CheckPosY = PlayerPosY;
		int CheckPosX = PlayerPosX;

		/// 위로 이동하려고 할 때
		if (PlayerInput == 'w' || PlayerInput == 'W')
		{
			CheckPosY -= 1;
		}

		/// 왼쪽으로 이동하려고 할 때
		else if (PlayerInput == 'a' || PlayerInput == 'A')
		{
			CheckPosX -= 1;
		}

		/// 아래쪽으로 이동하려고 할 때
		else if (PlayerInput == 's' || PlayerInput == 'S')
		{
			CheckPosY += 1;
		}

		/// 오른쪽으로 이동하려고 할 때
		else if (PlayerInput == 'd' || PlayerInput == 'D')
		{
			CheckPosX += 1;
		}

		// 이동하려는 위치가 벽이 아니라면
		if (Maze[CheckPosY][CheckPosX] != 1)
		{
			// 플레이어 위치 이동
			PlayerPosY = CheckPosY;
			PlayerPosX = CheckPosX;

			// 이동 후 미로 재출력
			PrintMaze(*Maze, MazeRows, MazeCols, PlayerPosX, PlayerPosY);

			// 골인 지점 도착시 종료 판별 변수 설정
			if (PlayerPosY == GoalPosY && PlayerPosX == GoalPosX)
			{
				printf("미로 탈출 성공!!\n");
				bGoal = true;
			}
			
			// 일정 확률로 적과의 전투
			else
			{
				/// 20% 확률로 전투 진입
				// 랜덤으로 0~9 숫자를 선택하고
				// 값이 0 or 1 인 경우
				if ((rand() % 10) < 2)
				{
					// 적 Hp 리셋
					EnemyHp = 50;

					// 전투 진행 후 결과 저장
					int Result = Encounter(&PlayerHp, &EnemyHp);

					// 플레이어 패배
					if (Result == -1)
					{
						printf("미로를 탈출하지 못했습니다..\n\n");
					}

				}
			}
		}

		else
		{
			printf("이동 불가!\n\n");
		}


	} while (bGoal == false && PlayerHp > 0);

	printf("===================================================\n\n");
}

void PrintMaze(int* Maze, int Rows, int Cols, int PlayerPosX, int PlayerPosY)
{
	printf("\n");

	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Cols; j++)
		{
			// 플레이어의 위치를 출력하려고 할 때
			if (i == PlayerPosY && j == PlayerPosX)
			{
				// P 출력 후 다음 위치로 넘김
				printf("P");
				continue;
			}

			// 현재 인덱스의 값 추출
			int Val = (Maze[i * Cols + j]);
			//printf("%d", Val);

			switch (Val)
			{
			case 0: { printf(".");	break; }	// 길
			case 1: { printf("#");	break; }	// 벽
			case 2: { printf("S");	break; }	// 시작점
			case 3: { printf("E");  break; }	// 출구
			}
		}
		printf("\n");
	}
	//*/
}

// 적과의 전투
// 플레이어와 적이 서로 번갈아가면서 공격한다.
// 
int Encounter(int* PlayerHp, int* EnemyHp)
{
	int Result = 0;			// 전투 상태 체크 1(플레이어 승리), 0(전투중), -1(적 승리)
	int TurnCount = 1;	// 턴 카운트

	printf("========= 전투 시작 =========\n");

	// 전투중 턴 진행
	while (Result == 0)
	{
		printf("-> 턴 (%d)\n", TurnCount);

		// 플레이어 데미지 계산
		int PlayerDamage = (rand() % 11) + 5;	// 5 ~ 15

		// 10% 확률로 크리티컬 적용
		int Temp = rand() % 10;
		if (Temp < 1)
		{
			PlayerDamage *= 2;	// 데미지 2배 적용
		}

		printf("플레이어의 공격~! 데미지 : %d\n", PlayerDamage);
		*EnemyHp -= PlayerDamage;
		if (*EnemyHp < 0)
		{
			*EnemyHp = 0;
		}
		printf("현재 적 체력 = [%d]\n", *EnemyHp);

		// 적이 죽으면
		if (*EnemyHp <= 0)
		{
			Result = 1;	// 플레이어 승리 처리
			printf("\n적을 쓰러뜨렸다!!!\n\n");
			printf("=============================\n");

			break;
		}

		// 적 데미지 계산
		int EnemyDamage = (rand() % 11) + 5;	// 5 ~ 15
		printf("적의 공격~! 데미지 : %d\n", EnemyDamage);
		*PlayerHp -= EnemyDamage;
		if (*PlayerHp < 0)
		{
			*PlayerHp = 0;
		}
		printf("현재 플레이어 체력 = [%d]\n", *PlayerHp);


		// 플레이어가 죽으면
		if (*PlayerHp <= 0)
		{
			Result = -1;	// 적 승리 처리
			printf("\n플레이어 Hp가 0이 되어 패배...\n\n");
			printf("=============================\n");

			break;
		}

		printf("\n");

		// 턴 증가
		TurnCount++;
	}

	return Result;
}
