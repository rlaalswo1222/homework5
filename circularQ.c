#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();
int freeQueue(QueueType *cQ); 
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();


int main(void)
{
	printf("[----- [�����] [2021041070] -----]\n");
	QueueType *cQ = createQueue(); //ť ����
	element data;

	char command;

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I': // i�϶� �Է�
			data = getElement(); 
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ,&data);// d�϶� ����
			break;
		case 'p': case 'P': // p �϶� ���
			printQ(cQ);
			break;
		case 'b': case 'B': // b �϶� �����
			debugQ(cQ);
			break;
		case 'q': case 'Q': // q �϶� ����
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType)); //ť ����
	cQ->front = 0; // front�� rear�� 0
	cQ->rear = 0;
	return cQ;
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;
    free(cQ); //ť�� �Ҵ�� �޸� ����
    return 1;
}

element getElement() // ť�� �� ���� �ޱ�
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


int isEmpty(QueueType *cQ) //ť�� ����ִ��� Ȯ���ϴ� �Լ�
{
	if (cQ->front == cQ->rear){ // ť�� ��������� front�� rear�� �����ϹǷ�
		printf("Circular Queue is empty!");
		return 1;
	}
	else return 0;
}

int isFull(QueueType *cQ) //ť�� ��á���� Ȯ���ϴ� �Լ�
{
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) { //rear+1�� front�� �ִ��� Ȯ��
		printf(" Circular Queue is full!");
		return 1;
	}
	else return 0;
}

void enQueue(QueueType *cQ, element item) // ť�� �߰�
{
	if(isFull(cQ)) return; //ť�� ��á�������� Ȯ��
	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; //���� rear���� ��ĭ ����
		// ����ť�̱� ������ ť ������� ũ�� �ٽ� ó������ ���Ұ� ���ԵǾ����. �׷��Ƿ� ť ������� ������ ����
		cQ->queue[cQ->rear] = item; // ���߰�
	}
}

void deQueue(QueueType *cQ, element *item) // ť���� ����
{
	if(isEmpty(cQ)) return; //ť�� ����ִ������� Ȯ��
	else {
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE; // front�� ��ĭ �������� �� ���Ҹ� ����
		*item = cQ->queue[cQ->front];
		return;
	}
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]); //ť ���� ���
		i = (i+1)%MAX_QUEUE_SIZE; // ���� ����

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ) //���� ť ���¸� �����
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i); //front�� ��ġ�� ��� 
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); // ������ ��ġ�� ���

	}
	//printQ(cQ);
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); //rear, front�� ��ġ���
}