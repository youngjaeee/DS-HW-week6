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
	int key; // 노드가 가지는 value 값
	struct Node* link; // 다음 노드를 가리키는 노드 포인터
} listNode;

typedef struct Head {
	struct Node* first; // 첫 번째 노드를 가리키는 헤드 포인터
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h); // 노드를 초기화하는 함수
int freeList(headNode* h); // 노드의 값을 지우고 할당한 메모리를 회수하는 함수

int insertFirst(headNode* h, int key); // 리스트의 처음 부분에 노드를 추가하는 함수
int insertNode(headNode* h, int key); // 리스트 탐색하여, 입력받은 key보다 큰값 나오는 노드 앞에 삽입하는 함수
int insertLast(headNode* h, int key); // 리스트의 마지막 부분에 노드를 추가하는 함수

int deleteFirst(headNode* h); // 리스트의 첫 번째 노드를 삭제하는 함수
int deleteNode(headNode* h, int key); // 사용자가 입력한 값을 가지는 노드를 찾아 삭제하는 함수
int deleteLast(headNode* h); // 리스트의 마지막 노드를 삭제하는 함수
int invertList(headNode* h); // 리스트의 순서를 역방향으로 전환하는 함수

void printList(headNode* h); // 리스트를 출력하는 함수

int main()
{
	char command; // 사용자의 메뉴 선택값을 저장하는 변수 선언
	int key; // 특정 노드의 value 값을 임시로 저장할 변수 선언
	headNode* headnode = NULL; // 헤드 포인터 headnode 선언 및 초기화

	printf("\n\n ----- [손영재] [2018038080] -----\n\n");

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
		scanf(" %c", &command); // 사용자가 입력한 메뉴 선택값에 따라

		switch (command) {
		case 'z': case 'Z': // 사용자가 리스트 초기화를 선택했을 경우
			headnode = initialize(headnode); // headnode로 시작하는 리스트에 대한 초기화 함수 호출
			break;
		case 'p': case 'P': // 사용자가 리스트 출력을 선택했을 경우
			printList(headnode); // 리스트 출력 함수 호출, 인자로 headnode를 넘김
			break;
		case 'i': case 'I': // 입력받은 key보다 큰값 나오는 노드 앞에 삽입하고자 하는 경우
			printf("Your Key = ");
			scanf("%d", &key); // key 값을 입력받은 후
			insertNode(headnode, key); // 노드 삽입 함수 호출, 매개변수로 headnode와 탐색할 key값을 넘김
			break;
		case 'd': case 'D': // 입력받은 key값을 가지는 노드를 삭제하고자 하는 경우
			printf("Your Key = ");
			scanf("%d", &key); // key 값을 입력받은 후
			deleteNode(headnode, key); // 노드 삭제 함수 호출, 매개변수로 headnode와 탐색할 key값을 넘김
			break;
		case 'n': case 'N': // 리스트의 가장 마지막에 노드를 삽입하고자 하는 경우
			printf("Your Key = ");
			scanf("%d", &key); // key 값을 입력받은 후
			insertLast(headnode, key); // 리스트 마지막에 노드 삽입 함수 호출, 매개변수로 headnode와 key값
			break;
		case 'e': case 'E': // 리스트의 마지막 노드를 삭제하고자 하는 경우
			deleteLast(headnode);  // 리스트 마지막 노드 삭제 함수 호출, 매개변수로 headnode를 넘김
			break;
		case 'f': case 'F': // 리스트의 가장 처음 부분에 노드를 추가하고자 하는 경우
			printf("Your Key = ");
			scanf("%d", &key); // key 값을 입력받은 후
			insertFirst(headnode, key); // 리스트 처음 부분 삽입 함수 호출, 매개변수로 headnode와 key 값
			break;
		case 't': case 'T': // 리스트의 가장 처음 부분 node를 삭제하고자 하는 경우
			deleteFirst(headnode); // 리스트 처음 부분 삭제 함수 호출, 매개변수로 headnode 넘김
			break;
		case 'r': case 'R': // 리스트의 순서를 역으로 변환하고자 하는 경우
			invertList(headnode); // 리스트 순서 변환 함수 호출, 매개변수로 headnode 넘김
			break;
		case 'q': case 'Q': // 프로그램을 종료하고자 하는 경우
			freeList(headnode); // 리스트 값 제거 및 할당한 메모리 환수
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); // 메뉴를 잘못 선택했을 경우 메시지 출력
			break;
		}

	} while (command != 'q' && command != 'Q'); // 프로그램을 종료할 때까지 반복 실행

	return 1;
}

headNode* initialize(headNode* h) {

	if (h != NULL) // headNode가 NULL이 아닌 경우 초기화를 먼저 진행해야 하므로
		freeList(h); // freeList 함수 호출, 인자로 헤드 포인터 h 넘겨 할당 메모리 해제

	headNode* temp = (headNode*)malloc(sizeof(headNode)); // 헤드 포인터 temp를 선언, 메모리 할당
	temp->first = NULL; // 초기화된 상태로 리스트에 노드가 없으므로 temp->first에 NULL을 대입
	return temp; // 헤드 포인터 temp 반환
}

int freeList(headNode* h) {
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; // 노드 포인터 p를 선언해 h->first 대입
	listNode* prev = NULL; // p=p->link 실행 이후 기존 p 노드를 가리키는 prev 노드 포인터 선언 및 NULL 초기화
	while (p != NULL) { // 모든 노드에 대한 공간 할당 해제를 완료할 때까지
		prev = p; // prev를 p로 설정
		p = p->link; // p를 p->link로 설정
		free(prev); // prev가 가리키는 노드 공간에 대한 할당 해제
	}
	free(h); // headNode 뒷부분의 노드 할당 해제 완료 후 headNode도 할당 해제
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 추가할 노드에 대한 공간을 할당에 node에 저장
	node->key = key; // node의 key를 사용자가 입력한 값으로 설정


	if (h->first == NULL) // 리스트에 노드가 존재하지 않을 경우
	{
		h->first = node; // h->first를 node로 설정하고
		node->link = NULL; // node가 리스트의 마지막 노드이므로 node->link를 NULL로 설정
		return 0;
	}
// 기존 리스트에 노드가 존재하는 경우
	node->link = h->first; // 새로 추가하는 node의 node->link가 헤드 포인터를 가리키게 하고
	h->first = node; // 헤드 포인터가 가리키는 위치를 추가한 node로 새로 지정

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 추가할 노드에 대한 공간을 할당에 node에 저장
	node->key = key; // node의 key를 사용자가 입력한 값으로 설정


	listNode* temp = h->first; // 값을 비교하기 위한 노드 포인터 temp, prevtemp 선언
	listNode* prevtemp = NULL; // 각각 h->first, NULL로 초기화

	if (temp == NULL) // temp가 NULL일때, 즉 리스트에 노드가 존재하지 않는 경우
	{
		printf("연결리스트 상 첫 번째로 입력하는 key로 비교대상 node가 없습니다.\n");
		node->link = NULL; // 첫 번째이자 유일한 노드로 추가하므로 node->link를 NULL로 설정
		h->first = node; // 헤드 포인터가 새로 추가한 node를 가리키게 함

		return 0;
	}
	else if (temp != NULL) // temp가 NULL이 아닐 때, 즉 노드가 1개 이상 존재하는 경우
	{
		for (temp = h->first; ; ) // temp가 리스트의 모든 노드를 한 번씩 가리킬 때까지 반복
		{
			if (key <(temp->key)) // 사용자가 추가하고자 하는 노드 key값 보다 큰 key를 가진 기존 노드를 발견한 경우
			{
				if (prevtemp == NULL) // prevtemp가 NULL, 즉 기존 노드가 1개 있는 경우
				{
					h->first = node; // 새로 추가하는 node를 기존 노드보다 앞선 위치에 추가해야 하므로
					node->link = temp; // 헤드 포인터가 node를 가리키게 하고 node->link가 기존 노드를 가리키게 함
					return 0;
				}
				else
				{ // 기존 노드가 2개 이상 있는 경우
					node->link = temp;  // 새로 추가하는 node->link를 값이 큰 뒤쪽 노드를 가리키게 하고
					prevtemp->link = node; // 기존 앞선 노드인 prevtemp->link를 새로 추가하는 node를 가리키게 함
					return 0;
				}
			}

			if ((temp->link) == NULL)
			{
				break; // temp->link가 NULL일 때, 즉 모든 노드에 대한 값 탐색을 완료한 경우 for문 탈출
			}

			prevtemp = temp; // 하나의 노드에 대한 탐색을 완료한 경우
			temp = temp->link; // prevtemp, temp가 가리키는 노드를 +1만큼 변경함

		
		}
		

		if ((temp->link) == NULL) // 모든 노드에 대한 탐색을 마쳤을 때 입력한 key보다 큰값 가지는 node 없는 경우
		{
//			printf("입력한 key보다 큰값을 가지는 노드가 없어 마지막 노드로 추가합니다.\n");
			temp->link = node; // temp가 가리키는 리스트의 마지막 노드의 link를 새로 추가하는 node로 설정
			node->link = NULL; // node가 리스트의 새로운 마지막 노드이므로 node->link를 NULL로 설정
		}
		return 0;
	}
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 추가할 노드의 정보를 저장할 node 선언 및 공간 할당
	node->key = key; // node의 key를 사용자가 입력한 key 값으로 설정

	if (h->first == NULL) // h->first == NULL, 즉 리스트에 노드가 없는 경우
	{
		h->first = node; // 헤드 포인터가 새로 추가하는 node를 가리키게 하고
		node->link = NULL; // node가 리스트의 마지막 노드이므로 node->link = NULL
		return 0;
	}
// 기존 리스트에 노드가 있는 경우
	listNode* listPoint; // 마지막 노드를 가리키는 포인터인 listPoint 선언
	for (listPoint = h->first; (listPoint->link) != NULL; )
		listPoint = listPoint->link; // for문을 통해 listPoint가 리스트의 마지막 노드를 가리킴

	listPoint->link = node; // listPoint->link를 node로 설정해 node를 리스트의 새로운 마지막 노드로 지정
	node->link = NULL; // node가 리스트의 마지막 노드이므로 node->link = NULL

	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL) // h->first = NULL인 경우, 즉 리스트에 노드가 존재하지 않을 경우
	{
		printf("입력된 node가 없습니다.\n"); // 메시지 출력 및 복귀
		return 0;
	}

	listNode* temp = h->first; // 노드 포인터 temp를 선언후 헤드 포인터가 가리키는 첫 번째 노드 주소 대입
	h->first = h->first->link; // 헤드 포인터가 두 번째 노드를 가리키게 하여 첫 번째 노드의 연결고리 끊음
	free(temp); // 기존 첫 번째 노드의 주소를 가지고 있는 temp에 대한 할당을 해제하여 첫 번째 노드를 삭제
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) // h->first = NULL인 경우, 즉 리스트에 노드가 존재하지 않을 경우
	{
		printf("입력된 노드가 없습니다.\n"); // 메시지 출력 및 복귀
		return 0;
	}

	listNode* temp = h->first; // 값을 비교하기 위한 노드 포인터 temp, prevtemp 선언
	listNode* prevtemp = NULL; // 각각 h->first, NULL로 초기화

	for (temp = h->first; ; temp = temp->link) // for문을 통해 리스트의 모든 노드를 탐색하여
	{
		if (h->first->link != NULL && temp->link == NULL) // 탐색 완료 후에도 값이 일치하는 노드가 없을 경우
		{
			printf("입력한 key와 같은 값을 가지는 노드가 없어 삭제하지 않습니다.\n"); // 메시지 출력 및 복귀
			break;
		}

		if (key == (temp->key)) // 입력한 key와 같은 값을 가지는 노드를 찾은 경우
		{
			if (h->first->link == NULL) // 리스트의 노드가 1개인 경우
			{
				h->first = NULL; // 리스트의 노드를 모두 없애므로 h->first = NULL
				free(temp); // 값이 같은 리스트의 노드에 대한 공간 할당 해제
				return 0;
			}
			// 리스트의 노드가 2개 이상일 경우
			prevtemp->link = temp->link; // 지울 노드의 left 노드가 right 노드를 가리키게 한 후
			free(temp); // 지울 노드(temp)에 대한 공간 할당 해제
			break; // for문 빠져나옴
		}
		prevtemp = temp; // prevtemp와 temp가 +1씩 다른 노드를 지정하게 하여 모든 노드 탐색

	}

	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL) // h->first = NULL, 즉 입력된 노드가 없는 경우
	{
		printf("입력된 노드가 없습니다.\n"); // 메시지 출력 및 복귀
		return 0;
	}
	else if (h->first != NULL && h->first->link == NULL) // 리스트에 노드가 1개 있는 경우
	{
		listNode* temp = h->first; // 노드 포인터 temp를 선언하여 헤드 포인터 값 대입
		h->first = h->first->link; // 헤드 포인터가 첫 번째 노드의 링크, 즉 NULL을 가리키게 함
		free(temp); // temp, 즉 첫 번째 노드에 대한 공간 할당을 해제하여 노드 삭제함
		return 0;
	}
// 노드가 2개 이상 있는 경우
	listNode* temp;
	listNode* prevtemp; // 마지막 노드를 탐색하기 위해 노드 포인터 temp와 prevtemp 선언

	prevtemp = NULL;
	for (temp = h->first; ; temp = temp->link)
	{
		if (temp->link == NULL) // for문 반복을 통해 temp가 리스트의 마지막 노드를 가리킬 경우
		{
			prevtemp->link = NULL; // 마지막 노드의 이전 노드, 즉 prevtemp가 가리키는 노드의 link를 NULL로 하고
			free(temp); // 기존 마지막 노드를 가리키는 temp에 대한 공간 할당 해제로 마지막 노드 삭제
			break;
		}
		prevtemp = temp; // 마지막 노드 탐색 위해 for문 반복
	}

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	listNode* lead = h->first;
	listNode* middle, * trail; // 역순 재배치를 위한 노드 포인터 lead, middle, trail 선언.
	middle = NULL;
	trail = NULL; // lead는 헤드 포인터 값을 대입하고, middle과 trail에는 NULL을 대입
	while (lead) // lead가 가리키는 노드의 다음 노드가 있을 때까지 반복
	{
		trail = middle;
		middle = lead; // trail은 middle, middle은 lead를 가리키고
		lead = lead->link; // lead는 다음 노드를 가리키게 하는 방식으로 노드 탐색을 진행하면서
		middle->link = trail; // middle->link를 trail로 변환하여 리스트를 역순으로 재배치
	}
	h->first = middle; // while문이 끝난 후 middle이 기존 리스트의 마지막 노드를 가리키므로 h->first = middle
	return 0;
}


void printList(headNode* h) {
	int i = 0; // 리스트의 index 값을 나타내는 변수 선언
	listNode* p; // 리스트 탐색을 위한 노드 포인터 p 선언

	printf("\n---PRINT\n");

	if (h == NULL) { // 노드가 없는 빈 리스트일 경우
		printf("Nothing to print....\n"); // 메시지 출력 및 복귀
		return;
	}

	p = h->first; // 노드 포인터에 리스트의 헤드 포인터 값 대입

	while (p != NULL) { // 모든 노드에 대해 탐색할 때까지 반복
		printf("[ [%d]=%d ] ", i, p->key); // 각 노드의 index와 key 값을 출력
		p = p->link; // 노드 포인터가 다음 노드를 가리키게 함
		i++; // index 값 증가
	}

	printf("  items = %d\n", i); // 총 노드의 개수, 즉 index 값을 출력
}

