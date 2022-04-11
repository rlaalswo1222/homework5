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
	printf("[----- [김민재] [2021041070] -----]\n");
	QueueType *cQ = createQueue(); //큐 생성
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
		case 'i': case 'I': // i일때 입력
			data = getElement(); 
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ,&data);// d일때 제거
			break;
		case 'p': case 'P': // p 일때 출력
			printQ(cQ);
			break;
		case 'b': case 'B': // b 일때 디버깅
			debugQ(cQ);
			break;
		case 'q': case 'Q': // q 일때 종료
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
	cQ = (QueueType *)malloc(sizeof(QueueType)); //큐 생성
	cQ->front = 0; // front와 rear는 0
	cQ->rear = 0;
	return cQ;
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;
    free(cQ); //큐에 할당된 메모리 해제
    return 1;
}

element getElement() // 큐에 들어갈 원소 받기
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


int isEmpty(QueueType *cQ) //큐가 비어있는지 확인하는 함수
{
	if (cQ->front == cQ->rear){ // 큐가 비어있을때 front와 rear은 동일하므로
		printf("Circular Queue is empty!");
		return 1;
	}
	else return 0;
}

int isFull(QueueType *cQ) //큐가 꽉찼는지 확인하는 함수
{
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) { //rear+1이 front에 있는지 확인
		printf(" Circular Queue is full!");
		return 1;
	}
	else return 0;
}

void enQueue(QueueType *cQ, element item) // 큐에 추가
{
	if(isFull(cQ)) return; //큐가 꽉찼는지부터 확인
	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; //현재 rear에서 한칸 증가
		// 원형큐이기 때문에 큐 사이즈보다 크면 다시 처음부터 원소가 삽입되어야함. 그러므로 큐 사이즈로 나머지 연산
		cQ->queue[cQ->rear] = item; // 값추가
	}
}

void deQueue(QueueType *cQ, element *item) // 큐에서 제거
{
	if(isEmpty(cQ)) return; //큐가 비어있는지부터 확인
	else {
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE; // front를 한칸 증가시켜 그 원소를 빼옴
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
		printf("%3c", cQ->queue[i]); //큐 원소 출력
		i = (i+1)%MAX_QUEUE_SIZE; // 다음 원소

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ) //현재 큐 상태를 디버깅
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i); //front의 위치를 출력 
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); // 원소의 위치를 출력

	}
	//printQ(cQ);
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); //rear, front의 위치출력
}