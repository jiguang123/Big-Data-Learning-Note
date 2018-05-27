// 4.4 Level order traversal
#include <cstdio>
#include <vector>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	
	TreeNode(int _val = 0): val(_val), left(nullptr), right(nullptr) {};
};

struct ListNode {
	int val;
	ListNode *next;
	
	ListNode(int _val = 0): val(_val), next(nullptr) {};
};

void consructBSTFromSortedArray(vector<int> &v, int left, int right, TreeNode *&root)
{
	if (left > right) {
		root = nullptr;
	} else {
		int mid = (left + right + 1) / 2;
		root = new TreeNode(v[mid]);
		consructBSTFromSortedArray(v, left, mid - 1, root->left);
		consructBSTFromSortedArray(v, mid + 1, right, root->right);
	}
}

void preorderTraversal(TreeNode *root, vector<ListNode *> &listHeads, vector<ListNode *> &listTails, int depth)
{
	if (root == nullptr) {
		printf("# ");
	} else {
		while ((int)listHeads.size() < depth) {
			listHeads.push_back(nullptr);
			listTails.push_back(nullptr);
		}
		
		if (listHeads[depth - 1] == nullptr) {
			listHeads[depth - 1] = listTails[depth - 1] = new ListNode(root->val);
		} else {
			listTails[depth - 1]->next = new ListNode(root->val);
			listTails[depth - 1] = listTails[depth - 1]->next;
		}
		
		printf("%d ", root->val);
		preorderTraversal(root->left, listHeads, listTails, depth + 1);
		preorderTraversal(root->right, listHeads, listTails, depth + 1);
	}
}

void clearBinaryTree(TreeNode *&root)
{
	if (root == nullptr) {
		return;
	} else {
		clearBinaryTree(root->left);
		clearBinaryTree(root->right);
		delete root;
		root = nullptr;
	}
}

void clearList(ListNode *&root)
{
	ListNode *ptr;
	
	ptr = root;
	while (ptr != nullptr) {
		root = root->next;
		delete ptr;
		ptr = root;
	}
	root = nullptr;
}

int main()
{
	TreeNode *root;
	int i, n;
	vector<int> v;
	vector<ListNode *> listHeads, listTails;
	ListNode *ptr;
	
	while (scanf("%d", &n) == 1 && n > 0) {
		for (i = 0; i < n; ++i) {
			v.push_back(i + 1);
		}
		
		consructBSTFromSortedArray(v, 0, n - 1, root);
		preorderTraversal(root, listHeads, listTails, 1);
		printf("\n");
		
		for (i = 0; i < (int)listHeads.size(); ++i) {
			printf("Level %d:", i + 1);
			ptr = listHeads[i];
			while (ptr != nullptr) {
				printf(" %d", ptr->val);
				ptr = ptr->next;
			}
			printf("\n");
			clearList(listHeads[i]);
		}
		
		v.clear();
		clearBinaryTree(root);
		listHeads.clear();
		listTails.clear();
	}
	
	return 0;
}