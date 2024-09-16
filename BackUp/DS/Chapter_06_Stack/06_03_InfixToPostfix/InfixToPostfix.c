#include <string.h> //strlen, strcpy 등의 메서드를 사용하기 위함.
#include <stdlib.h> //malloc, free 등 동적할당에 필요한 라이브러리
#include <ctype.h> //isdigit같은 문자를 처리하는 함수를 위해 필요한 라이브러리
#include "ListBaseStack.h"

int GetOpPrec(char op) // Get Operator Precedence 연산자의 우선도를 반환하는 함수
{
	switch(op) //op를 받아서
	{
	case '*':
	case '/':
		return 5; //곱셈 나눗셈에는 우선도 5
	case '+':
	case '-':
		return 3; // 덧셈 뺄셈에는 우선도 3
	case '(':
		return 1; //괄호에는 우선도 1. 참고로 닫는 건 signal에 해당하니 굳이 정의할 필요도 없다.
	}

	return -1;   // 등록되지 않은 연산자
}

int WhoPrecOp(char op1, char op2) // 어떤 연산자가 더 우위인지를 비교하는 함수,
{
	int op1Prec = GetOpPrec(op1); //op1에 우선도를 계산하여 저장
	int op2Prec = GetOpPrec(op2); //op2에도 우선도를 계산하여 저장

	if(op1Prec > op2Prec) // 둘을 비교해서 op1의 우선도가 더 크다면
		return 1; //1을 반환하라
	else if(op1Prec < op2Prec)
		return -1; //아니면 -1 반환
	else
		return 0; //같으면 0인듯
}

void ConvToRPNExp(char exp[]) //실제로 중위연산을 후위연산식으로 바꿔주는 함수. 우선 연산식을 문자열로 받아준다.
{
	Stack stack; // 스택 필요하고(연산자만 따로 담을 곳)
	int expLen = strlen(exp); //최대길이는 문자열 길이만큼
	char * convExp = (char*)malloc(expLen+1); // 변환 완료된 연산식을 담을 공간을 동적할당해줍니다.
	//expLen + 1을 할당하는 이유는 문자열의 끝을 나타내는 널 종료 문자(\0)를 저장할 공간을 추가로 확보하기 위함

	int i, idx=0;
	char tok, popOp;
	//tok : 현재 처리 중인 문자를 담을 변수
	// popup : 스택에서 꺼낸 연산자를 담을 변수
	memset(convExp, 0, sizeof(char)*expLen+1); // convExp를 0으로 초기화해준다.
	StackInit(&stack); //스택 초기화해줍니다. &stack인 이유는 함수가 직접 변경할 권한이 있어야 하니까.

	for(i=0; i<expLen; i++)
	{
		tok = exp[i]; //처음부터 하나씩 연산자든 피연산자든 값을 tok에 넣어줍니다.
		if(isdigit(tok)) //만약에 tok이 숫자면, 피연산자니까
		{
			convExp[idx++] = tok; //변환된 연산식이 담길 convExp 0번째 인덱스에 tok을 넣고 idx를 1 증가시킴.
		}
		else //숫자가 아니면 연산자라는 소리니까 분류가 필요함
		{
			switch(tok)
			{
			case '(': //열린괄호면 닫힌괄호가 나올 때까지 Stack에 넣어야 함.
				SPush(&stack, tok); //스택에 열린괄호 넣어주고
				break; //넘어갈게요

			case ')': //닫힌괄호가 뜨면
				while(1)
				{
					popOp = SPop(&stack); //popOp 변수에 스택에 있던 맨 윗놈을 꺼내서 담는다.
					if(popOp == '(') //꺼낸게 열린괄호면 바닥까지 다 긁어서 꺼낸거니까
						break; //반복문 종료
					convExp[idx++] = popOp; // popOp에 담았으면 그대로 그걸 convExp에 담아주고 idx값 1 추가.
				}
				break;

			case '+': case '-': 
			case '*': case '/':// 나머지 일반연산자들은
				while(!SIsEmpty(&stack) && 
						WhoPrecOp(SPeek(&stack), tok) >= 0) //비어있지 않으면서 스택 맨 윗부분이 현 연산자보다 우선도가 높을 경우라면 반복
					convExp[idx++] = SPop(&stack); // convExp에 스택에 있던 녀석을 꺼내서 넣어줍니다.
					//이러면 현재 연산자보다 우선도가 높은 놈들은 싹 다 convExp에 들어갑니다.

				SPush(&stack, tok); //이제 현 연산자를 stack에 넣어줍니다.
				break; //처리 끝 !
			}
		}
	}

	while(!SIsEmpty(&stack))
		convExp[idx++] = SPop(&stack);
	// 연산식 변환이 끝났으면 Stack에 남은 녀석들까지 convExp에 넣고 마무리해야겠죠 ?
	// stack에 담긴 순서대로 stack이 빌 때까지 차곡차곡 convExp에 넣어줍니다.

	strcpy(exp, convExp); //convExp의 내용을 exp에 복사해주어 exp내용을 후위정렬연산식으로 갱신해줍니다.
	free(convExp); //동적할당했던 convExp는 해제해줍니다.
}




