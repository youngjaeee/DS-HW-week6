/*
 * singly linked list
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

 /* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode = NULL;

	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h) {
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL; // p=p->link 실행 이후 기존 p 노드를 가리키는 prev 노드 포인터 선언 및 NULL 초기화
	while (p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;


	if (h->first == NULL)
	{
		h->first = node;
		node->link = NULL;
		return 0;
	}

	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;


	listNode* temp = h->first;
	listNode* prevtemp = NULL;

	if (temp == NULL)
	{
		printf("연결리스트 상 첫 번째로 입력하는 key로 비교대상 node가 없습니다.\n");
		node->link = NULL;
		h->first = node;

		return 0;
	}
	else if (temp != NULL)
	{
		for (temp = h->first; ; )
		{
			if (key <(temp->key))
			{
				if (prevtemp == NULL)
				{
					h->first = node;
					node->link = temp;
					return 0;
				}
				else
				{
					node->link = temp;
					prevtemp->link = node;
					return 0;
				}
			}

			if ((temp->link) == NULL)
			{
				break;
			}

			prevtemp = temp;
			temp = temp->link;

		
		}
		

		if ((temp->link) == NULL)
		{
			printf("입력한 key보다 큰값을 가지는 노드가 없어 마지막 노드로 추가합니다.\n");
			temp->link = node;
			node->link = NULL;
		}
		return 0;
	}
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	if (h->first == NULL)
	{
		h->first = node;
		node->link = NULL;
		return 0;
	}

	listNode* listPoint;
	for (listPoint = h->first; (listPoint->link) != NULL; )
		listPoint = listPoint->link;

	listPoint->link = node;
	node->link = NULL;

	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL)
	{
		printf("입력된 node가 없습니다.\n");
		return 0;
	}

	listNode* temp = h->first;
	h->first = h->first->link;
	free(temp);
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL)
	{
		printf("입력된 노드가 없습니다.\n");
		return 0;
	}

	listNode* temp;
	listNode* prevtemp;
	prevtemp = NULL;
	for (temp = h->first; ; temp = temp->link)
	{
		if (h->first->link != NULL && temp->link == NULL)
		{
			printf("입력한 key와 같은 값을 가지는 노드가 없어 삭제하지 않습니다.\n");
			break;
		}

		if (key == (temp->key))
		{
			if (h->first->link == NULL)
			{
				h->first = NULL;
				free(temp);
				return 0;
			}
			prevtemp->link = temp->link;
			free(temp);
			break;
		}
		prevtemp = temp;

	}

	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL)
	{
		printf("입력된 노드가 없습니다.\n");
		return 0;
	}
	else if (h->first != NULL && h->first->link == NULL)
	{
		listNode* temp = h->first;
		h->first = h->first->link;
		free(temp);
		return 0;
	}

	listNode* temp;
	listNode* prevtemp;

	prevtemp = NULL;
	for (temp = h->first; ; temp = temp->link)
	{
		if (temp->link == NULL)
		{
			prevtemp->link = NULL;
			free(temp);
			break;
		}
		prevtemp = temp;
	}

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	listNode* lead = h->first;
	listNode* middle, * trail;
	middle = NULL;
	trail = NULL;
	while (lead)
	{
		trail = middle;
		middle = lead;
		lead = lead->link;
		middle->link = trail;
	}
	h->first = middle;
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

