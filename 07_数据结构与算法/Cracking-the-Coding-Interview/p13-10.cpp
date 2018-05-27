// 13.10 Write a function in C called my2DAlloc, which allocates space for 2d array. Try to minimize the number of mallocs and frees.
#include <cstdio>
#include <cstdlib>
using namespace std;

int **my2DAlloc(int row, int col)
{
	if (row < 1 || col < 1) {
		return nullptr;
	}

	int i;
	int **a;
	
	a = (int **)malloc(row *  sizeof(int *));
	a[0] = (int *)malloc(row * col * sizeof(int));
	for (i = 1; i < row; ++i) {
		a[i] = a[0] + i * col;
	}

	return a;
}

void my2DFree(int **ptr)
{
	if (ptr == nullptr) {
		return;
	}
	free(ptr[0]);
	free(ptr);
}

int main()
{
	int row, col;
	
	scanf("%d%d", &row, &col);
	int **a = my2DAlloc(row, col);
	
	int i, j;
	
	for (i = 0; i < row; ++i) {
		for (j = 0; j < col; ++j) {
			scanf("%d", &a[i][j]);
		}
	}
	
	for (i = 0; i < row; ++i) {
		for (j = 0; j < col; ++j) {
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}
	
	my2DFree(a);
	
	return 0;
}