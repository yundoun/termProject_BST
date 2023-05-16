#include <stdio.h>
#include <stdlib.h>

/// <summary>
/// �ڱ� ���� ����ü
/// </summary>
typedef int data; 
typedef struct _Node {
	int key; // �����ͺκ�
	struct _Node* right; //�ڱ� �ڽſ� ���� ������
	struct _Node* left;
} Node;

 /// <summary>
 /// ��� Ž�� 
 /// </summary>
 /// <param name="root"> ��Ʈ ��忡 �����ؼ� Ž�� </param>
 /// <param name="x"> ����� ������ �� </param>
 /// <returns></returns>
 Node* searchBST(Node* root, int x) {
	 Node* p = root;
	 while (p != NULL) {
		 if (p->key == x) {
			 printf("���� Ʈ�� ���� %d ���� Ž���߽��ϴ� \n\n",x);
			 return p;
		 }
		 else if (p->key < x)
			 p = p->right;
		 else
			 p = p->left;
	 }

	 printf("Error : ������ %d ���� ã�� �� �����ϴ� !!\n\n", x);
	 return NULL;
}

 /// <summary>
 /// ��� ����
 /// </summary>
 /// <param name="root"> ��Ʈ ��忡 �����ؼ� Ž�� </param>
 /// <param name="x"> ������ ����� ������ �� </param>
 /// <returns></returns>
 Node* insertBST(Node* root, int x) {
	 Node* p = root;
	 Node* parent = NULL;
	 // NULL�� �־��ִ� ����?
	 // while������ �ѹ����� ������찡 ���� => ��Ʈ�� ���� ���
	 while (p != NULL) {
		 parent = p;
		 if (p->key == x){
			 printf("Error : ���� Ű�� �����մϴ� !!\n\n");
			 return p;
		 }
		 else if (p->key < x)
			 p = p->right;
		 else
			 p = p->left;
	 }

	 // �� ��� �Ҵ�
	 Node* newNode = (Node*)malloc(sizeof(Node)); // malloc���� ���� ���� ����� ����ȯ�� ���־�� ��

	 newNode->key = x;
	 newNode->left = newNode->right = NULL;  // �ܸ���尡 �� ���̱� ������ NULL �Ҵ�


	 // parent�� �ڽ����� �� ��� ���̱�
	 // parent�� �ڽ��� �׻� NULL�� �ƴҼ�������
	 // parent�� NULL�� ���� ����
	 // parent�� NULL�� �ƴҶ��� ��������ش�.

	 if (parent != NULL) {
		 if (parent->key < newNode->key)
			 parent->right = newNode;
		 else
			 parent->left = newNode;
	 }

	 return newNode;
 }


 /// <summary>
 /// ��� ����
 /// </summary>
 /// <param name="root"> ��Ʈ ��忡 �����ؼ� Ž�� </param>
 /// <param name="x"> ������ ����� ������ �� </param>
 /// <returns></returns>
 Node* deleteBST(Node* root, int x) {
	 // deleteBST�� ��ȯŸ���� Node*�� �ؾ��ϴ� ����
	 // => ã������ ���(x)�� ��Ʈ����϶�, ��Ʈ����� �����ͷν� x�� �ּҸ� ������ �ִ�
	 // ��尡 ������ �ǰ� �ؿ� �ִ� ��尡 �ö�� �� �ٱ����� ����ϰ� �ִ� ��Ʈ����� �����Ͱ� �ǹ̰� ������ �ȴ�
	 // ���ο� ��Ʈ����� �ּҸ� ������ �� �־�� �ϱ� ������ Node* ���·� ��ȯ�ؾ��Ѵ�.
	 Node* p = root;
	 Node* parent = NULL;
	
	 while ((p != NULL)&&(p->key != x)) { // ã������ �ϴ� ��尡 ���ų� ��Ʈ�� Ű�� x �϶�(��Ʈ��带 ã����?) 
		 parent = p;
		 if (p->key == x) {
			 printf("���� Ű�� �����մϴ�\n\n");
			 return p;
		 }
		 else if (p->key < x)
			 p = p->right;
		 else
			 p = p->left;
	 }

	 // ã�� ��尡 ���� ���
	 if (p == NULL) {
		 printf("ã�� ��尡 �����ϴ�\n");
		 return root; // ���� ���� ��Ʈ�� �״�� �����־�� �Ѵ�.
	 }

	 // ������ 0�ΰ��
	 if (p->left == NULL && p->right == NULL) {
		 if (parent == NULL) {
			 root = NULL;
			 // ��Ʈ�ϳ��� �������µ� ��Ʈ������ 0  => Ʈ����ü ��尡 �ϳ��ۿ� ���µ� �����Ǵ� ��Ȳ
		 }	 // 1. ���� ��尡 ��Ʈ����ε� ������ 0�� ���, �� ���� ��尡 ��Ʈ�ε� while���� �� ���� �� ���� �ٷ� ã�� ���
		 else {
			 if (parent->left == p)
				 parent->left = NULL;
			 else
				 parent->right = NULL; 
		 } // 2. ��Ʈ�� �ƴѵ� ������ 0�� ���
	 }
		 
	// ������ 1�� ���
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
	// ������ 2�ΰ��
	// ���� ����Ʈ������ �İ���(���� ū ���)�� ����� ��(���� ����Ʈ������ ���� ū ��)�� 100% ������ �ڽ��� ����. ������ �ڽ��� �ִٴ� ���� �̺��� �� ū ��尡 �ִٴ� ��
	// ������ ����Ʈ������ �İ��ڸ� ����� ��(������ ���� Ʈ������ ���� ���� ��)�� 100% ���� �ڽ��� ����. ���� �ڽ��� �ִٴ� ���� �̺��� �� ���� ��尡 �ִٴ� ��
	// �����ؾ��� ���� ���� ���� �ʰ�, �İ��� ��带 ���� ��Ų �� �İ��� ����� ���� �����ؾ� �ϴ� ����� �����Ͱ��� �������ش�. 
	else {
		// ������ ���� ������̵� �������
		// �����ʿ��� ã�´� ����
		Node* succ_parent = p; // �İ����� �θ� 
		Node* succ = p->right; // �İ���
		while (succ->left != NULL) {  // ���̻� ���� �ڽ��� ������ ���� Ž��
			succ_parent = succ;
			succ = succ->left;
		}
		p->key = succ->key;
			 
		if (succ_parent->left == succ) { // ���� succ�� ���� �ڽ��� �ݵ�� ����.
			succ_parent->left = succ->right;
		}
		else  // �� ���� succ�� parent�� ������ �ڽ��� ���, �� ������ ����Ʈ������ ���� ���� ��尡 �ƴ� ���
			succ_parent->right = succ->right;
		p = succ; // p �� free ��ų ���̱� ������ 
	}

		 free(p);
		 return root;  // �ٲ�������� �� ��Ʈ �� ��ȯ

}

 
 /// <summary>
 /// ���� ǥ�������� ȣ��
 /// </summary>
 /// <param name="root"> ��Ʈ��忡 ���� </param>
 void Inorder(Node* root) { 
	 if (root == NULL) { // NULL�� ��� ���ȣ�� ���� �ʰ� ��ȯ
		 return;
	 }
	 Inorder(root->left);   // ���� �ڽ� ó��
	 printf("%d  ", root->key);  // �ڱ� �ڽ� ó��
	 Inorder(root->right); // ������ �ڽ� ó��
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

	// ���� Ž�� Ʈ�� ����
	printf("==========================================================================================================\n\n");
	printf("��� ������ 25���� ���� Ž�� Ʈ�� ���� \n\n");
	Inorder(root); printf("\n\n");
	printf("==========================================================================================================\n\n");

	// ��� Ž��
	printf("�����Ͱ� 56�� ��� Ž�� ��,,, \n\n");
	searchBST(root, 56);
	printf("==========================================================================================================\n\n");

	// ��� Ž�� / ���� ��Ȳ : ��尡 ���� ���� ���� ���
	printf("�����Ͱ� 79�� ��� Ž�� ��,,, \n\n");
	searchBST(root, 79);
	printf("==========================================================================================================\n\n");

	// ��� ����
	printf("�����Ͱ� 79�� ��� ���� ��,,,,\n\n");
	insertBST(root, 79);
	Inorder(root); printf("\n\n");
	printf("��尡 ����� ���ԵǾ����� Ȯ���մϴ�,,,,\n\n");
	searchBST(root, 79);
	printf("==========================================================================================================\n\n");

	// ��� ���� / ���� ��Ȳ : ��尡 �̹� ���� �ϴ� ���
	printf("�����Ͱ� 43�� ��� ���� ��,,,\n\n");
	insertBST(root, 43);
	printf("==========================================================================================================\n\n");

	// ��� ����
	printf("�����Ͱ� 22�� ��� ���� ��,,,\n\n");
	deleteBST(root, 22);
	Inorder(root); printf("\n\n");
	printf("��尡 ����� �����Ǿ����� Ȯ���մϴ�,,,,\n\n");
	searchBST(root, 22);
	printf("==========================================================================================================\n\n");


	printf("������ : 20193066 ������\n");




	//printf("74 ��带 ���� �ϰڽ��ϴ�\n");

	//root = deleteBST(root, 74);
	//Inorder(root); printf("\n");


	return 0;
}