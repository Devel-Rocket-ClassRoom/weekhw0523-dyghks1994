#include "Homework02.h"

#include <iostream>
#include <stdio.h>

using namespace std;

// 2. 자리수 분리해서 합치기(입력은 자리 수 제한 없음)

void Homework02_Run()
{
	
	int Number = 0;	// 입력할 변수
	int Sum = 0;	// 합계 저장용 변수

	printf("2. 자리수 분리해서 합치기(입력은 자리 수 제한 없음) \n");

	do
	{
		printf("분리해서 더할 수 입력(종료는 0) = ");

		cin >> Number;

		// 중간 단계 갱신할 변수
		int Temp = Number;
		while (Temp != 0)
		{
			Sum += Temp % 10;		// 현재 1의자리의 값을 누적
			Temp /= 10;				// Temp 값을 10으로 나눔(10진수 기준 오른쪽으로 옮긴 것 같게)
		}

		printf("Sum = %d\n\n", Sum);
		Sum = 0;	//  Sum 초기화

	} while (Number != 0);
}
