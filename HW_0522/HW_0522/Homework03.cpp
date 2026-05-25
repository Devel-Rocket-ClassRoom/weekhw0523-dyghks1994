#include "Homework03.h"

#include <iostream>
#include <stdio.h>

// 3. 슬롯 머신 게임 만들기
// 시작 금액 10000
// 한판에 무조건  최소 100 배팅해야 함.만약 소지금액이 100 이하일 경우 게임 종료.
// 같은 숫자 3개가 나오면 50배로 돌려 받는다.
// 만약 777이면 10000배 받음

using namespace std;

void Homework03_Run()
{
	int Money = 10000;				// 시작 금액
	int Bet = 0;					// 배팅 금액

	const int MachineSize = 3;
	int SlotMachine[MachineSize] = { 0, };	// 슬롯머신 넘버

	printf("3. 슬롯머신 게임, 소지금액이 100 이하일 경우 종료됩니다.\n\n");

	do 
	{
		printf("소지 금액 = %d\n", Money);
		printf("베팅 금액을 입력하세요.(최소 100) = ");

		// 배팅액 임력
		cin >> Bet;
		if (Bet < 100)
		{
			// 100원 미만 입력한 경우 재 입력
			printf("최소 100원 이상 배팅 해 주세요.\n\n");
			continue;
		}

		// 슬롯머신 번호 생성
		for (int i = MachineSize - 1; i >= 0; i--)
		{
			SlotMachine[i] = rand() % 10;	// 0 ~ 9 중 랜덤 번호 생성
		}

		PrintMachine(SlotMachine);

		int Result = CalcResult(SlotMachine, Bet);	// 배팅결과 계산
		Money += Result;							// 머니 합산

	} while (Money >= 100);

	printf("소지금액 [%d] 로 게임 종료!\n\n", Money);

	printf("===================================================\n\n");
}

// 머신 출력
void PrintMachine(int* SlotMachine)
{
	printf("------ 슬롯 머신 ------ \n\n");
	printf("    [%d]  [%d]  [%d] \n\n", SlotMachine[0], SlotMachine[1], SlotMachine[2]);
	printf("----------------------- \n\n");
}

// 결과 계산
int CalcResult(int* SlotMachine, int Bet)
{
	int Return = Bet;

	// 숫자3개가 모두 같으면 당첨
	if (SlotMachine[0] == SlotMachine[1]
		&& SlotMachine[1] == SlotMachine[2])
	{
		// '777' 이면 10000배
		if (SlotMachine[0] == 7)
		{
			Return = Bet * 10000;
			printf("777 당첨으로 10000배(%d)를 획득합니다 !!!\n\n", Return);
		}

		// 그 외 면 50배
		else
		{
			Return = Bet * 50;
			printf("%d%d%d 당첨으로 50배(%d)를 획득합니다 !!!\n\n",SlotMachine[0], SlotMachine[1], SlotMachine[2], Return);
		}
	}

	// 꽝
	else
	{
		Return = -Bet;
		printf("아쉽게도 당첨되지 않았습니다...\n\n");
	}

	// 배팅결과 리턴
	return Return;
}
