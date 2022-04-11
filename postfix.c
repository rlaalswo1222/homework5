 /*
    * postfix.c
 *
 *  Created on: Apr 2, 2019
 *      Author: rsyoung
 */

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack 내에서 우선순위는 내림차순, lparen = 0 가장 낮음 */

typedef enum{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];
char postfixExp[MAX_EXPRESSION_SIZE];
char postfixStack[MAX_STACK_SIZE];
int evalStack[MAX_STACK_SIZE];

int postfixStackTop = -1;
int evalStackTop = -1;

int evalResult = 0;
void postfixPush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
    printf("[----- [김민재] [2021041070] -----]\n");
	char command;

	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //문자 하나 입력받음

		switch(command) {
		case 'i': case 'I': // i일때 infix 입력받음
			getInfix();
			break;
		case 'p': case 'P': // p일때 postfix로 변환
			toPostfix();
			break;
		case 'e': case 'E': // e일때 연산결과를 출력
			evaluation();
			break;
		case 'd': case 'D': // d일때 현재 상태를 디버깅
			debug();
			break;
		case 'r': case 'R': // r일때 리셋
			reset();
			break;
		case 'q': case 'Q': //q일때 끝내기
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); // 그외의 입력은 오류 
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;


}

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x; //스택의 top을 한칸 증가시킨 후 그 자리에 추가
}

char postfixPop()
{
	char x;
    if(postfixStackTop == -1) //비어있다면
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--]; //스택에 있는 값을 가져온 후 top을 한칸 내림
    }
    return x;
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x; //스택의 top을 한칸 증가시킨 후 그 자리에 추가
}

int evalPop()
{
    if(evalStackTop == -1) //스택이 비어있다면
        return -1;
    else
        return evalStack[evalStackTop--]; //스택에 있는 값을 가져온 후 top을 한칸 내림
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */

void getInfix()
{
    printf("Type the expression >>> "); //infix를 입력받음
    scanf("%s",infixExp);
}

precedence getToken(char symbol)
{
	switch(symbol) { //문자를 입력받고 각각 대응되는 단어를 리턴
	case '(' : return lparen; 
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}
}

precedence getPriority(char x)
{
	return getToken(x); 
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0')  // 비어있다면
		strncpy(postfixExp, c, 1); //복사
	else
		strncat(postfixExp, c, 1); //비어있지 않다면 이어붙이기
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0') 
	{
		if(getPriority(*exp) == operand) // 피연산자면
		{
			x = *exp;
        	charCat(&x); //postfixexp에 넣기
		}
        else if(getPriority(*exp) == lparen) { // '(' 면  

        	postfixPush(*exp); // 스택에 넣기
        }
        else if(getPriority(*exp) == rparen) // ')' 면 
        {
        	while((x = postfixPop()) != '(') { //'('가 나올때까지 pop
        		charCat(&x); // postfixexp에 넣기
        	}
        }
        else //연산자라면 
        {
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp)) //만약 top에 있는 원소가 우선순위가 더 높거나 같다면
            {
            	x = postfixPop(); // 스택에서 가져온 뒤
            	charCat(&x); // postfixexp에 넣기
            }
            postfixPush(*exp); // 우선순위가 낮다면 스택에 계속 쌓아줌
        }
        exp++;
	}

    while(postfixStackTop != -1)
    {
    	x = postfixPop(); // 스택에서 가져온뒤
    	charCat(&x); //postfixexp에 넣기 
    }

}

void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult); // infix, postfix,evaluation 출력

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]); // 스택에 들어있는 연산자들 출력

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0'; //infix와 postfix의 첫원소를 끝('\0')으로 설정하여 리셋
	postfixExp[0] = '\0';

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0'; //스택을 초기화
         
	postfixStackTop = -1; //각 스택들의 top을 처음위치로 초기화
	evalStackTop = -1;
	evalResult = 0; // 연산 결과값 초기화
}
void evaluation()
{
	int opr1, opr2, i;

	int length = strlen(postfixExp); //postfix의 길이 가져옴
	char symbol;
	evalStackTop = -1;

	for(i = 0; i < length; i++)
	{
		symbol = postfixExp[i];
		if(getToken(symbol) == operand) { // 피연산자 라면
			evalPush(symbol - '0'); // 스택 삽입.  ASCII 문자값 48을 빼면, 숫자를 얻을 수 있음

		}
		else {
			opr2 = evalPop(); // 넣었던 피연산자를 가져옴
			opr1 = evalPop(); 
			switch(getToken(symbol)) { //연산자의 종류에 따라 피연산자의 연산을 진행 후 그 값을 스택에 저장
			case plus: evalPush(opr1 + opr2); break;
			case minus: evalPush(opr1 - opr2); break;
			case times: evalPush(opr1 * opr2); break;
			case divide: evalPush(opr1 / opr2); break;
			default: break;
			}
		}
	}
	evalResult = evalPop(); // 저장해놨던 결과값을 스택에서 가져옴
}
