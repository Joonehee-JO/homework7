/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);			//링크드리스트를 메모리해제하는 함수

int insertNode(headNode* h, int key);	//입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입하는 함수
int insertLast(headNode* h, int key);	//리스트의 마지막에 입력한 키를 갖는 노드를 삽입하는 함수
int insertFirst(headNode* h, int key);	//리스트의 처음에 새 노드를 삽입하는 함수
int deleteNode(headNode* h, int key);	//입력한 key를 갖는 노드를 삭제하는 함수
int deleteLast(headNode* h);			//연결리스트의 마지막 노드를 삭제하는 함수
int deleteFirst(headNode* h);			//첫번째 노드를 삭제하는 함수
int invertList(headNode* h);			//연결리스트를 역순으로 배치하는 함수

void printList(headNode* h);			//연결리스트를 출력하는 함수


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	printf("[----- [Cho Joon Hee] [2017038076] -----]\n");	

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);		//연결리스트 초기화
			break;
		case 'p': case 'P':
			printList(headnode);		//연결리스트 출력
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);	//입력된 key값보다 큰 값을 갖는 노드 앞에 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);	//입력한 key와 같은 값을 갖는 노드를 삭제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);	//리스트의 마지막에 key값의 노드 삽입
			break;
		case 'e': case 'E':
			deleteLast(headnode);		//리스트의 마지막 노드 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);	//리스트의 처음에 key값을 갖는 노드 삽입
			break;
		case 't': case 'T':
			deleteFirst(headnode);		//첫번째 노드를 삭제
			break;
		case 'r': case 'R':
			invertList(headnode);		//리스트를 역순으로 배치
			break;
		case 'q': case 'Q':
			freeList(headnode);			//프로그램 종료 전 할당된 메모리 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {	//초기화하는 함수
	if(*h != NULL)				//할당된 공간이 존재한다면
		freeList(*h);			//해당 메모리 반납

	*h = (headNode *)malloc(sizeof(headNode));	//h에 headNode사이즈만큼 메모리 할당받음
	(*h)->first = NULL;							//리스트가 존재하지 않기에 NULL로 초기화

	return 1;
}

int freeList(headNode* h){	//링크드리스트 메모리해제하는 함수
	listNode* p = h->first;	//p가 첫번째 노들를 가리키도록 설정
	listNode* prev = NULL;	//삭제하고자 하는 노드

	while(p != NULL){		//리스트가 존재한다면 마지막까지 돌면서
		prev = p;			//prev가 삭제하고자하는 노드를 가리키도록하고
		p=p->rlink;			//p는 그다음 리스트를 가리키도록 설정
		free(prev);			//prev가 가리키는 노드 메모리 반납
	}
	free(h);				//마지막으로 헤드노드 메모리 반납

	return 0;
}


void printList(headNode* h) {	//연결리스트를 출력하는 함수
	int i = 0;			//리스트의 인덱스
	listNode* p;		//헤더노드를 가리킬 변수

	printf("\n---PRINT\n");

	if(h == NULL) {		//만일 리스트가 존재하지 않는다면
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;		//p가 첫번째 노드를 가리키도록함

	while(p != NULL) {	//p가 마지막노드일때까지 출력
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {	//리스트의 마지막에 입력한 키를 갖는 노드를 삽입하는 함수
	listNode *temp = (listNode *)malloc(sizeof(listNode));	//삽입할 노드
	listNode *node;											//첫번째 노드를 가리킬 변수
	temp->key = key;										//사용자가 입력한 값 할당
	temp->llink = NULL, temp->rlink = NULL;					
	node = h->first;										//node가 첫번째 노드를 가리키도록 함

	if(h->first == NULL){									//리스트가 비어있다면
		printf("The linked list is empty\n");				//에러메세지 출력 후 함수종료
      	return 0;
	}

	for(; node->rlink != NULL; node=node->rlink);			//리스트의 마지막까지 돌음
	node->rlink = temp;										//리스트 마지막 노드뒤에 입력한 값을 받은 노드 삽입
	temp->llink = node;										//삽입한 노드의 왼쪽링크필드가 기존 마지막 노드를 가리키도록함

	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {		//마지막 노드를 삭제하는 함수
	listNode *node = h->first;	//node가 첫번째 노드를 가리키도록함
	listNode *previous = NULL;  //이전노드
	int count = 0;				//노드가 하나인지 확인하기 위한 변수

	if(h->first == NULL){									//리스트가 비어있다면
		printf("The linked list is empty\n");				//에러메세지 출력 후 함수종료
      	return 0;
	}

	for(; node->rlink!=NULL; previous = node, node=node->rlink)count++;	//리스트에 존재하는 노드만큼 반복

	if(count == 0){         //노드가 하나밖에 없다면
        h->first = NULL;    //헤더가 아무것도 가리키지 않도록하고
        free(node);         //해당 노드 메모리반납
        return 0;
    }
    else{                   //노드가 하나가 아니라면
        previous->rlink = NULL;  //이전노드가 아무것도 가리키지 않도록하고(마지막 노드로 만듦)
        free(node);         //마지막노드 삭제
        return 0;
    }

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {		//리스트의 처음에 새 노드를 삽입하는 함수
	listNode* temp = (listNode*)malloc(sizeof(listNode));		//삽입할 노드
	temp->key = key, temp->rlink = NULL, temp->llink = NULL;	//필드값 할당
	listNode* node = h->first;									//node가 첫번째 노드를 가리키도록함

	if(h->first == NULL){					//리스트가 비어있다면
		h->first = temp;					//입력노드가 첫번째 노드가 되도록함
      	return 0;					
	}
	else{									//리스트가 존재한다면
		temp->rlink = node;					//삽입노드의 오른쪽링크가 node를 가리키도록함 (첫번쨰 노드가 됨)
		node->llink = temp;					//그리고 기존노드의 왼쪽링크가 삽입노드를 가리키도록해서 이중리스트가 되도록함
		h->first = temp;					//먀지막으로 헤더노드 변경
	}	

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {		//첫번째 노드를 삭제하는 함수
	listNode *node = h->first;

	if(h->first == NULL){					//리스트가 존재하지 않는다면
		printf("The linked list is empty\n");				//에러메세지 출력 후 함수종료
      	return 0;
	}

	if(node->rlink == NULL){				//리스트의 노드가 하나밖에 없다면
		h->first = NULL;					//헤더노드가 아무것도 가리키지 않도록하고
		free(node);							//리스트의 노드삭제
		return 0;							//함수종료
	}
	else{									//리스트에 2개이상의 노드가 존재한다면
		h->first = node->rlink;				//헤더노드가 다음노드를 가리키도록하고
		free(node);							//첫번째 노드 삭제
		h->first->llink = NULL;				//이후 삭제한노드의 다음노드(첫 노드가 된)의 왼쪽링크를 Null로 할당
	}

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	listNode *node = h->first;			//node가 첫번째 노드를 가리키도록함
	listNode *trail = NULL;				//마지막 노드를 가리킬 포인터
	listNode *middle = NULL;			//중간 노드를 가리킬 포인터

	if(h->first == NULL){					//리스트가 존재하지 않는다면
		printf("The linked list is empty\n");				//에러메세지 출력 후 함수종료
      	return 0;
	}

	while(node){    //node가 마지막 노드일때까지 반복
        trail = middle;   //trail이 middle을 가리키도록하고
        middle = node;  //middle이 node를 가리키도록함
        node = node->rlink;  //노드는 다음 노드를 가리키도록함(trail->middle->node 순)
        middle -> rlink = trail; //middle이 가리키는 노드가 이전 노드를 가리키도록 함으로써 역순으로 배치
		middle -> llink = node;  //이중연결리스트기에 middle의 왼쪽링크는 node를 가리키도록함
    }

    h->first = middle;  //역순으로 배치가 끝났으니 헤더가 첫번째 노드(node는 null이고 middle이 마지막노드)를 가리키도록함

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {		
	listNode *node = h->first;		//node가 첫번째노드를 가리키도록함
	listNode *previous = NULL;		//이전 노드를 가리킬 포인터
	listNode *temp = (listNode*)malloc(sizeof(listNode));	//삽입할 노드
	temp->key = key, temp->llink = NULL, temp->rlink = NULL;	//필드값 할당
	int count = 0;		//노드가 첫번째 노드인지 판별하기 위한 변수

	for(; node != NULL; previous = node, node = node->rlink){	//연결리스트를 돌면서 key값 확인
		if(node->key >= key){					//입력받은 key보다 큰 값이 존재한다면
			if(count == 0){						//만일 그 노드가 첫번째 노드였을 시
				temp->rlink = node;				//temp의 오른쪽링크가 node를 가리키도록함(삽입노드가 첫번째 노드가 되도록함)
				node->llink = temp;				//node의 왼쪽링크가 temp를 가리키도록함(이중연결리스트로 만듦)
				h->first = temp;				//첫번째 노드로 삽입했으니 헤더노드 변경
				return 0;						//함수종료
			}
			else{								//찾은 노드가 첫번째 노드가 아니라면
				previous->rlink = temp;			//이전노드의 오른쪽링크가 삽입노드를 가리키도록함
				temp->rlink = node;				//삽입노드의 오른쪽링크가 node를 가리키도록함
				temp->llink = previous;			//이중연결리스트를 위해 삽입노드의 왼쪽링크가 이전노드를 가리키도록함
				node->llink = temp;				//node의 왼쪽링크가 삽입노드를 가리키도록함
				return 0;						//함수종료(최종적으로 previous<->temp<->node 형태)
			}
		}	
		count++;
	}

	//입력key 값이 제일 크다면
	if(count == 0){			//리스트가 비어있을 경우
		h->first = temp;	//헤더노드가 삽입노드를 가리키도록함
		return 0;			//함수종료
	}
	previous->rlink = temp;	//리스트의 노드가 여러개 존재할시
	temp -> llink = previous;	//삽입노드의 왼쪽링크가 previous(반복문을 다 돌아 마지막노드를 가리킴)를 가리키도록함
	return 0;				//함수종료
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {		//입력한 key를 갖는 노드를 삭제하는 함수
	listNode *node =  h->first;				//node가 첫번째 노드를 가리키도록함
	listNode *previous = NULL;				//이전노드를 가리킬 포인터
	int count = 0;							//첫번째 노드인지 확인하기 위한 변수

	if(h->first == NULL){					//리스트가 존재하지 않는다면
		printf("The linked list is empty\n");				//에러메세지 출력 후 함수종료
      	return 0;
	}

	for(; node != NULL; previous=node, node=node->rlink){	//노드의 마지막까지 반복
		if(node->key == key){					//입력 key값과 같은 값을 갖는 노드를 찾았다면
			if(count == 0){						//해당 노드가 첫번째 노드일시
				if(node->rlink == NULL){		//연결리스트의 노드가 한개라면
					h->first = NULL;			//헤더노드가 아무것도 가리키지 않도록 초기화
					free(node);					//존재하는 유일한 노드 삭제
					return 0;					//함수종료
				}
				h->first = node->rlink;			//노드가 한개가 아니라면 헤더노드가 노드의 다음노드를 가리키도록함
				h->first->llink = NULL;			//첫번째노드의 삭제하는 노드를 가리키던 왼쪽링크 NULL로 초기화
				free(node);						//해당 node삭제
				return 0;
			}
			else{								//해당 노드가 첫번째 노드가 아니라면
				if(node->rlink == NULL){		//node의 다음링크가 NULL이라면(마지막 노드라면)
					previous->rlink = NULL;		//이전노드의 오른쪽링크 NULL로 초기화(마지막 노드가됨)
					free(node);					//node 삭제
					return 0;					//함수종료
				}
				previous->rlink = node->rlink;	//해당 노드가 마지막 노드가 아닐시 이전노드의 오른쪽링크에 삭제할 node가 가리키는 노드를 가리키도록함
				node->rlink->llink = previous;	//삭제할노드 다음의 노드의 왼쪽링크는 이전노드를 가리키도록함
				free(node);						//해당노드 삭제(previous<->삭제노드의 다음노드)
				return 0;
			}
		}
		count++;
	}

	printf("Nothing to find\n");			//key값과 같은 값을 갖는 노드를 찾지못했을 경우

	return 1;
}


