#include "Homework04.h"

#include <iostream>
#include <stdio.h>

using namespace std;

// 4. 도둑 잡기 만들기
// 시작 금액 10000
// 한판에 무조건 최소 100 배팅해야 함.만약 소지금액이 100 이하일 경우 게임 종료.
// 딜러는 A~K까지의 트럼프 카드 중 2장을 중복없이 선택하고 조커 카드가 추가된다.
// 플레이어는 딜러의 카드 중 한장을 선택한다.
// 만약 플레이어가 조커를 뽑있다면 플레이어의 승리.배팅 금액의 2배를 받는다.
// 플레이어가 조커를 뽑지 못했다면 다음 게임을 시작하거나 배팅 금액의 2배를 추가로 지불하고 한번 더 선택할 수 있다.

void Homework04_Run()
{
	int Money = 10000;		// 소지금액
	int Bet = 0;			// 배팅금액
	int PlayerSelect = 0;	// 플레이어 선택

	const int DealerHandSize = 3;
	int DealerHand[DealerHandSize] = { 0, };	// 딜러 패

	printf("4. 도둑 잡기 게임\n\n");

	while (Money >= 100)	// 게임 종료 조건 : 플레이어가 소지금이 100원 미만일 경우 게임 종료.
	{
		// 배팅
		printf("현재 소지금 : [%d]원 배팅금액 입력 = ", Money);
		while ( (Bet = SelectNum()) < 100  || Bet > Money)
		{
			printf("현재 보유금액에서 100원 이상 배팅 하세요. \n");
		}
		Money -= Bet;			// 현재 보유금액에서 배팅금액 차감
		printf("남은 금액 : [%d]원   배팅 금액 : [%d]원\n\n", Money, Bet);
		

		// 딜러 카드 뽑기
		DealerDraw(DealerHand, DealerHandSize);

		// 플레이어의 선택
		PlayerSelect = SelectCard();
		
		// 선택한 카드가 조커(14)인지 체크
		if (DealerHand[PlayerSelect - 1] == 14)
		{
			printf("Joker를 찾았습니다!! 배팅금액의 2배(%d)를 획득합니다.\n\n", Bet * 2);
			Money += Bet * 2;
			Bet = 0;
		}

		// 재도전 or 새게임 시작
		else
		{
			printf("조커를 찾지 못했네요..\n");
			printf("(1)번 배팅액의 2배(%d)를 추가 배팅하고 재도전, (2)번 새게임 시작 = ", Bet * 2);

			do
			{
				PlayerSelect = SelectNum();

				if (PlayerSelect == 1
					|| PlayerSelect == 2)
				{
					break;
				}

				printf("1 or 2 를 입력 하세요. = ");

			} while (true);

			/// 2번째 시도
			if (PlayerSelect == 1 )	
			{
				if (Money >= Bet * 2) // 현재 베팅금댁의 2배가 있는지 확인
				{
					// 기존 베팅액에 2배 추가한 금액을 얹는다.
					Money -= Bet * 2;
					Bet = Bet + Bet * 2;

					// 플레이어의 선택
					PlayerSelect = SelectCard();
					printf("남은 금액 : [%d]원   배팅 금액 : [%d]원\n\n", Money, Bet);


					// 선택한 카드가 조커(14)인지 체크
					if (DealerHand[PlayerSelect - 1] == 14)
					{
						printf("Joker를 찾았습니다!! 배팅금액의 2배(%d)를 획득합니다.\n\n", Bet * 2);
						Money += Bet * 2;
						Bet = 0;
					}

					else
					{
						printf("두 번째 시도에도 조커를 찾지 못했네요.. 처음으로 돌아갑니다.\n\n");
					}
				}

				else
				{
					printf("배팅금액이 모자랍니다.. 처음으로 돌아갑니다.\n\n");
				}
				
			}

			else
			{
				printf("새 게임을 시작합니다.\n\n");
			}
		}
	}
	printf("소지금이 부족해서 더 이상 진행할 수 없습니다.\n\n");
}

int SelectNum()
{
	int Num = 0;

	cin >> Num;
	cin.clear();
	cin.ignore(10000, '\n');

	return Num;
}

// 딜러 카드 뽑기
void DealerDraw(int* DealerHand, int DealerHandSize)
{
	/// 2 ~ 10, A(1), J(11), Q(12), K(13), Joker(14)
	DealerHand[0] = rand() % 13 + 1;	// 첫 번째 카드 드로우(2 ~ K)

	do
	{
		DealerHand[1] = rand() % 13 + 1;	// 두 번째 카드 드로우(2 ~ K) 

	} while (DealerHand[0] == DealerHand[1]); // (첫 번째와 같으면 재드로우)

	DealerHand[2] = 14;		// JoKer 추가

	// 딜러 카드 셔플
	FisherYateShuffle(DealerHand, DealerHandSize);
}



void FisherYateShuffle(int* DealerHand, int Length)
{
	// 1. 인덱스는 배열의 마지막 요소에서 첫번째 요소로 진행
	// 2. 인덱스가 가리키는 요소와 0~인덱스까지의 요소 중 임의의 요소를 선택
	// 3. 인덱스가 가리키는 요소와 임의로 선택된 요소를 교환
	// 4. 인덱스는 1 감소

	for (int i = Length - 1; i > 0; i--)
	{
		int j = rand() % (i + 1);

		int Temp = DealerHand[i];
		DealerHand[i] = DealerHand[j];
		DealerHand[j] = Temp;
	}

}

int SelectCard()
{
	int PlayerSelect = 0;

	printf("1, 2, 3 중 원하는 카드를 선택 하세요 = ");

	do
	{
		PlayerSelect = SelectNum();
		if (PlayerSelect == 1		// 플레이어 입력이 정상(1~3)인지 체크
			|| PlayerSelect == 2
			|| PlayerSelect == 3)
		{
			break;
		}

		printf("잘못 입력했습니다. 다시 입력 하세요. \n");

	} while (true);

	return PlayerSelect;
}
