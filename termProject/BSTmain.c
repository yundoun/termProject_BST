#include <stdio.h>
#include <stdlib.h>

/// <summary>
/// 자기 참조 구조체
/// </summary>
typedef int data; 
typedef struct _Node {
	int key; // 데이터부분
	struct _Node* right; //자기 자신에 대한 포인터
	struct _Node* left;
} Node;

 /// <summary>
 /// 노드 탐색 
 /// </summary>
 /// <param name="root"> 루트 노드에 접근해서 탐색 </param>
 /// <param name="x"> 노드의 데이터 값 </param>
 /// <returns></returns>
 Node* searchBST(Node* root, int x) {
	 Node* p = root;
	 while (p != NULL) {
		 if (p->key == x) {
			 printf("이진 트리 안의 %d 값을 탐색했습니다 \n\n",x);
			 return p;
		 }
		 else if (p->key < x)
			 p = p->right;
		 else
			 p = p->left;
	 }

	 printf("Error : 데이터 %d 값을 찾을 수 없습니다 !!\n\n", x);
	 return NULL;
}

 /// <summary>
 /// 노드 삽입
 /// </summary>
 /// <param name="root"> 루트 노드에 접근해서 탐색 </param>
 /// <param name="x"> 삽입할 노드의 데이터 값 </param>
 /// <returns></returns>
 Node* insertBST(Node* root, int x) {
	 Node* p = root;
	 Node* parent = NULL;
	 // NULL로 넣어주는 이유?
	 // while루프를 한바퀴도 못돌경우가 있음 => 루트가 없을 경우
	 while (p != NULL) {
		 parent = p;
		 if (p->key == x){
			 printf("Error : 같은 키가 존재합니다 !!\n\n");
			 return p;
		 }
		 else if (p->key < x)
			 p = p->right;
		 else
			 p = p->left;
	 }

	 // 새 노드 할당
	 Node* newNode = (Node*)malloc(sizeof(Node)); // malloc에서 나온 값은 명시적 형변환을 해주어야 함

	 newNode->key = x;
	 newNode->left = newNode->right = NULL;  // 단말노드가 될 것이기 때문에 NULL 할당


	 // parent의 자식으로 새 노드 붙이기
	 // parent의 자식이 항상 NULL이 아닐수도있음
	 // parent가 NULL일 수도 있음
	 // parent가 NULL이 아닐때만 진행시켜준다.

	 if (parent != NULL) {
		 if (parent->key < newNode->key)
			 parent->right = newNode;
		 else
			 parent->left = newNode;
	 }

	 return newNode;
 }


 /// <summary>
 /// 노드 삭제
 /// </summary>
 /// <param name="root"> 루트 노드에 접근해서 탐색 </param>
 /// <param name="x"> 삭제할 노드의 데이터 값 </param>
 /// <returns></returns>
 Node* deleteBST(Node* root, int x) {
	 // deleteBST의 반환타입을 Node*로 해야하는 이유
	 // => 찾으려는 노드(x)가 루트노드일때, 루트노드의 포인터로써 x의 주소를 가지고 있다
	 // 노드가 삭제가 되고 밑에 있는 노드가 올라올 때 바깥에서 기억하고 있는 루트노드의 포인터가 의미가 ㅇ벗게 된다
	 // 새로운 루트노드의 주소를 돌려줄 수 있어야 하기 때문에 Node* 형태로 반환해야한다.
	 Node* p = root;
	 Node* parent = NULL;
	
	 while ((p != NULL)&&(p->key != x)) { // 찾으려고 하는 노드가 없거나 루트의 키가 x 일때(루트노드를 찾을때?) 
		 parent = p;
		 if (p->key == x) {
			 printf("같은 키가 존재합니다\n\n");
			 return p;
		 }
		 else if (p->key < x)
			 p = p->right;
		 else
			 p = p->left;
	 }

	 // 찾는 노드가 없을 경우
	 if (p == NULL) {
		 printf("찾는 노드가 없습니다\n");
		 return root; // 내가 받은 루트를 그대로 돌려주어야 한다.
	 }

	 // 차수가 0인경우
	 if (p->left == NULL && p->right == NULL) {
		 if (parent == NULL) {
			 root = NULL;
			 // 루트하나가 지워지는데 루트차수가 0  => 트리전체 노드가 하나밖에 없는데 삭제되는 상황
		 }	 // 1. 현재 노드가 루트노드인데 차수가 0인 경우, 즉 현재 노드가 루트인데 while문을 한 번도 안 돌고 바로 찾은 경우
		 else {
			 if (parent->left == p)
				 parent->left = NULL;
			 else
				 parent->right = NULL; 
		 } // 2. 루트가 아닌데 차수가 0인 경우
	 }
		 
	// 차수가 1인 경우
	if (p->left == NULL || p->right == NULL) {
		Node* child = (p->left != NULL) ? p->left : p->right;
		if (parent == NULL)
			root = child;
		else {
			if (parent->left == p)
				parent->left = child;
			else
				parent->right = child;

		}
	}
	// 차수가 2인경우
	// 왼쪽 서브트리에서 후계자(가장 큰 노들)를 골랐을 때(왼쪽 서브트리에서 가장 큰 값)는 100% 오른쪽 자식이 없다. 오른쪽 자식이 있다는 것은 이보다 더 큰 노드가 있다는 것
	// 오른쪽 서브트리에서 후계자를 골랐을 때(오른쪽 서브 트리에서 가장 작은 값)는 100% 왼쪽 자식이 없다. 왼쪽 자식이 있다는 것은 이보다 더 작은 노드가 있다는 것
	// 제거해야할 노드는 제거 하지 않고, 후계자 노드를 삭제 시킨 후 후계자 노드의 값을 제거해야 하는 노드의 데이터값에 복사해준다. 
	else {
		// 오른쪽 왼쪽 어느쪽이든 상관없음
		// 오른쪽에서 찾는다 가정
		Node* succ_parent = p; // 후계자의 부모 
		Node* succ = p->right; // 후계자
		while (succ->left != NULL) {  // 더이상 왼쪽 자식이 없을때 까지 탐색
			succ_parent = succ;
			succ = succ->left;
		}
		p->key = succ->key;
			 
		if (succ_parent->left == succ) { // 현재 succ는 왼쪽 자식이 반드시 없다.
			succ_parent->left = succ->right;
		}
		else  // 이 경우는 succ가 parent의 오른쪽 자식인 경우, 즉 오른쪽 서브트리에서 가장 작은 노드가 아닐 경우
			succ_parent->right = succ->right;
		p = succ; // p 를 free 시킬 것이기 때문에 
	}

		 free(p);
		 return root;  // 바뀌었을지도 모를 루트 값 반환

}

 
 /// <summary>
 /// 중위 표현법으로 호출
 /// </summary>
 /// <param name="root"> 루트노드에 접근 </param>
 void Inorder(Node* root) { 
	 if (root == NULL) { // NULL일 경우 재귀호출 하지 않고 반환
		 return;
	 }
	 Inorder(root->left);   // 왼쪽 자식 처리
	 printf("%d  ", root->key);  // 자기 자신 처리
	 Inorder(root->right); // 오른쪽 자식 처리
 }


int main() {

	

	Node* root = insertBST(NULL, 34);
	insertBST(root, 54);
	insertBST(root, 1);
	insertBST(root, 4);
	insertBST(root, 17);
	insertBST(root, 74);
	insertBST(root, 22);
	insertBST(root, 55);
	insertBST(root, 100);
	insertBST(root, 41);
	insertBST(root, 91);
	insertBST(root, 431);
	insertBST(root, 88);
	insertBST(root, 43);
	insertBST(root, 59);
	insertBST(root, 21);
	insertBST(root, 67);
	insertBST(root, 11);
	insertBST(root, 544);
	insertBST(root, 144);
	insertBST(root, 80);
	insertBST(root, 37);
	insertBST(root, 48);
	insertBST(root, 56);
	insertBST(root, 134);

	// 이진 탐색 트리 생성
	printf("==========================================================================================================\n\n");
	printf("노드 개수가 25개인 이진 탐색 트리 생성 \n\n");
	Inorder(root); printf("\n\n");
	printf("==========================================================================================================\n\n");

	// 노드 탐색
	printf("데이터가 56인 노드 탐색 중,,, \n\n");
	searchBST(root, 56);
	printf("==========================================================================================================\n\n");

	// 노드 탐색 / 예외 상황 : 노드가 존재 하지 않을 경우
	printf("데이터가 79인 노드 탐색 중,,, \n\n");
	searchBST(root, 79);
	printf("==========================================================================================================\n\n");

	// 노드 삽입
	printf("데이터가 79인 노드 삽입 중,,,,\n\n");
	insertBST(root, 79);
	Inorder(root); printf("\n\n");
	printf("노드가 제대로 삽입되었는지 확인합니다,,,,\n\n");
	searchBST(root, 79);
	printf("==========================================================================================================\n\n");

	// 노드 삽입 / 예외 상황 : 노드가 이미 존재 하는 경우
	printf("데이터가 43인 노드 삽입 중,,,\n\n");
	insertBST(root, 43);
	printf("==========================================================================================================\n\n");

	// 노드 삭제
	printf("데이터가 22인 노드 삭제 중,,,\n\n");
	deleteBST(root, 22);
	Inorder(root); printf("\n\n");
	printf("노드가 제대로 삭제되었는지 확인합니다,,,,\n\n");
	searchBST(root, 22);
	printf("==========================================================================================================\n\n");


	printf("개발자 : 20193066 윤도운\n");




	//printf("74 노드를 삭제 하겠습니다\n");

	//root = deleteBST(root, 74);
	//Inorder(root); printf("\n");


	return 0;
}