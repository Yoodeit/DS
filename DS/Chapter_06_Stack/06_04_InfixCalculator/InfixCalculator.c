#include <string.h>
#include <stdlib.h>
#include "InfixToPostfix.h" //입력받은 중위연산식을 후위연산식으로 바꿔줌
#include "PostCalculator.h" //후위연산 계산.

int EvalInfixExp(char exp[])
{
	int len = strlen(exp); // 입력받은 식의 길이 len
	int ret; //식의 결과를 담을 변수
	char * expcpy = (char*)malloc(len+1); // 식을 임시로 담을 공간 동적할당 NULL문자 담을 곳까지 하나 더 추가
	strcpy(expcpy, exp); // 식을 expcpy에 담음

	ConvToRPNExp(expcpy); //후위연산식으로 변환   
	ret = EvalRPNExp(expcpy); //그걸 계산해서 ret에 담는다.

	free(expcpy); //ret에 결과를 담았으니 expcpy는 메모리해제
	return ret; //결과값 반환.
}
