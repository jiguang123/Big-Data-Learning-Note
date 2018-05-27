// 4.7 Least Common Ancestor
// This solution is Naive Algorithm, may timeout on very large and skewed trees.
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 10005;
// tree[x][0]: parent of node x
// tree[x][1]: left child of node x
// tree[x][2]: right child of node x
// tree[x][3]: value of node x
int tree[MAXN][4];
// number of nodes
int e;

void build(int a)
{
    int tmp;

    scanf("%d", &tmp);
    if(tmp)
    {
        tree[a][1] = e;
        tree[e][3] = tmp;
        tree[e][0] = a;
        ++e;
		// build the left subtree
        build(e - 1);
    }

    scanf("%d", &tmp);
    if(tmp)
    {
        tree[a][2] = e;
        tree[e][3] = tmp;
        tree[e][0] = a;
        ++e;
		// build the right subtree
        build(e - 1);
    }
}

int main()
{
    int n, ni;
	int i;
	// the value to be queried
	int m1, m2;
	// the corresponding node indices of m1 and m2
	int s1, s2;
	int t1, t2;
	int c1, c2, c;

    while (scanf("%d", &n)  == 1) {
		for (ni = 0; ni < n; ++ni) {
			// get value for root node
			e = 1;
            scanf("%d", &tree[0][3]);

			// root has no parent node
            tree[0][0] = -1;
            build(0);

			while (scanf("%d%d", &m1, &m2) == 2 && (m1 && m2)) {
				s1 = s2 = -1;
				for (i = 0;i <= e; ++i) {
					if (tree[i][3] == m1) {
						s1 = i;
						// there're duplicate values
						break;
					}
				}
				for (i = 0;i <= e; ++i) {
					if (tree[i][3] == m2) {
						s2 = i;
						// there're duplicate values
						break;
					}
				}

				if (s1 != -1 && s2 != -1) {
					t1 = s1;
					t2 = s2;
					c1 = c2 = 0;

					// c1 is the depth of t1
					while (tree[t1][0] != -1) {
						++c1;
						t1 = tree[t1][0];
					}
					// c2 is the depth of t2
					while (tree[t2][0] != -1) {
						++c2;
						t2 = tree[t2][0];
					}
				
					// move'em to the same height level
					if (c1 > c2) {
						c = c1 - c2;
						while(c--) {
							s1 = tree[s1][0];
						}
					} else {
						c = c2 - c1;
						while(c--) {
							s2 = tree[s2][0];
						}
					}
				
					while(s1 != s2)
					{
						s1 = tree[s1][0];
						s2 = tree[s2][0];
					}
					printf("%d\n", tree[s1][3]);
				} else {
					// At least one value is not found in the tree.
					printf("Not found in the tree.\n");
				}
			}
        }
    }

    return 0;
}