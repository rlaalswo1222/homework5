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

/* stack ������ �켱������ ��������, lparen = 0 ���� ���� */

typedef enum{
	lparen = 0,  /* ( ���� ��ȣ */
	rparen = 9,  /* ) ������ ��ȣ*/
	times = 7,   /* * ���� */
	divide = 6,  /* / ������ */
	plus = 5,    /* + ���� */
	minus = 4,   /* - ���� */
	operand = 1 /* �ǿ����� */
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
    printf("[----- [�����] [2021041070] -----]\n");
	char command;

	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //���� �ϳ� �Է¹���

		switch(command) {
		case 'i': case 'I': // i�϶� infix �Է¹���
			getInfix();
			break;
		case 'p': case 'P': // p�϶� postfix�� ��ȯ
			toPostfix();
			break;
		case 'e': case 'E': // e�϶� �������� ���
			evaluation();
			break;
		case 'd': case 'D': // d�϶� ���� ���¸� �����
			debug();
			break;
		case 'r': case 'R': // r�϶� ����
			reset();
			break;
		case 'q': case 'Q': //q�϶� ������
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); // �׿��� �Է��� ���� 
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;


}

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x; //������ top�� ��ĭ ������Ų �� �� �ڸ��� �߰�
}

char postfixPop()
{
	char x;
    if(postfixStackTop == -1) //����ִٸ�
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--]; //���ÿ� �ִ� ���� ������ �� top�� ��ĭ ����
    }
    return x;
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x; //������ top�� ��ĭ ������Ų �� �� �ڸ��� �߰�
}

int evalPop()
{
    if(evalStackTop == -1) //������ ����ִٸ�
        return -1;
    else
        return evalStack[evalStackTop--]; //���ÿ� �ִ� ���� ������ �� top�� ��ĭ ����
}

/**
 * infix expression�� �Է¹޴´�.
 * infixExp���� �Էµ� ���� �����Ѵ�.
 */

void getInfix()
{
    printf("Type the expression >>> "); //infix�� �Է¹���
    scanf("%s",infixExp);
}

precedence getToken(char symbol)
{
	switch(symbol) { //���ڸ� �Է¹ް� ���� �����Ǵ� �ܾ ����
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
 * �����ϳ��� ���޹޾�, postfixExp�� �߰�
 */
void charCat(char* c)
{
	if (postfixExp == '\0')  // ����ִٸ�
		strncpy(postfixExp, c, 1); //����
	else
		strncat(postfixExp, c, 1); //������� �ʴٸ� �̾���̱�
}

/**
 * infixExp�� ���ڸ� �ϳ��� �о�鼭 stack�� �̿��Ͽ� postfix�� �����Ѵ�.
 * ����� postfix�� postFixExp�� ����ȴ�.
 */
void toPostfix()
{
	/* infixExp�� ���� �ϳ����� �б����� ������ */
	char *exp = infixExp;
	char x; /* �����ϳ��� �ӽ÷� �����ϱ� ���� ���� */

	/* exp�� �������Ѱ��鼭, ���ڸ� �а� postfix�� ���� */
	while(*exp != '\0') 
	{
		if(getPriority(*exp) == operand) // �ǿ����ڸ�
		{
			x = *exp;
        	charCat(&x); //postfixexp�� �ֱ�
		}
        else if(getPriority(*exp) == lparen) { // '(' ��  

        	postfixPush(*exp); // ���ÿ� �ֱ�
        }
        else if(getPriority(*exp) == rparen) // ')' �� 
        {
        	while((x = postfixPop()) != '(') { //'('�� ���ö����� pop
        		charCat(&x); // postfixexp�� �ֱ�
        	}
        }
        else //�����ڶ�� 
        {
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp)) //���� top�� �ִ� ���Ұ� �켱������ �� ���ų� ���ٸ�
            {
            	x = postfixPop(); // ���ÿ��� ������ ��
            	charCat(&x); // postfixexp�� �ֱ�
            }
            postfixPush(*exp); // �켱������ ���ٸ� ���ÿ� ��� �׾���
        }
        exp++;
	}

    while(postfixStackTop != -1)
    {
    	x = postfixPop(); // ���ÿ��� �����µ�
    	charCat(&x); //postfixexp�� �ֱ� 
    }

}

void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult); // infix, postfix,evaluation ���

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]); // ���ÿ� ����ִ� �����ڵ� ���

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0'; //infix�� postfix�� ù���Ҹ� ��('\0')���� �����Ͽ� ����
	postfixExp[0] = '\0';

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0'; //������ �ʱ�ȭ
         
	postfixStackTop = -1; //�� ���õ��� top�� ó����ġ�� �ʱ�ȭ
	evalStackTop = -1;
	evalResult = 0; // ���� ����� �ʱ�ȭ
}
void evaluation()
{
	int opr1, opr2, i;

	int length = strlen(postfixExp); //postfix�� ���� ������
	char symbol;
	evalStackTop = -1;

	for(i = 0; i < length; i++)
	{
		symbol = postfixExp[i];
		if(getToken(symbol) == operand) { // �ǿ����� ���
			evalPush(symbol - '0'); // ���� ����.  ASCII ���ڰ� 48�� ����, ���ڸ� ���� �� ����

		}
		else {
			opr2 = evalPop(); // �־��� �ǿ����ڸ� ������
			opr1 = evalPop(); 
			switch(getToken(symbol)) { //�������� ������ ���� �ǿ������� ������ ���� �� �� ���� ���ÿ� ����
			case plus: evalPush(opr1 + opr2); break;
			case minus: evalPush(opr1 - opr2); break;
			case times: evalPush(opr1 * opr2); break;
			case divide: evalPush(opr1 / opr2); break;
			default: break;
			}
		}
	}
	evalResult = evalPop(); // �����س��� ������� ���ÿ��� ������
}
