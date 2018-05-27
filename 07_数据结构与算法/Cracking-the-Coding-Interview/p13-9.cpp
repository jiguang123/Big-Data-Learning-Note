// 13.9 Implement a memory-aligned malloc(), which returns a block of memory, and the address of the first byte is a multiple of a power of 2.
#include <cstdio>
#include <cstdlib>
using namespace std;

void *aligned_malloc(int nbytes, int align)
{
	// boundary check
	if (nbytes < 1 || align < 1) {
		return nullptr;
	}
	
	// make sure that align is a power of 2
	while ((align & align - 1) != 0) {
		align = (align & align - 1);
	}
	
	void *p1, *p2;
	
	p1 = (void *)malloc(nbytes + align - 1 + sizeof(void *));
	if (p1 == nullptr) {
		return nullptr;
	}
	p2 = (void *)(((size_t)p1 + align - 1 + sizeof(void *)) & (~(align - 1)));
	((void **)p2)[-1] = p1;
	
	return p2;
}

void aligned_free(void *ptr)
{
	if (ptr == nullptr) {
		return;
	}
	free(((void **)ptr)[-1]);
}

int main()
{
	void *p1 = aligned_malloc(100, 4096);
	void *p2 = malloc(100);
	
	printf("p1 = %p\n", p1);
	printf("p2 = %p\n", p2);
	aligned_free(p1);
	free(p2);
	
	return 0;
}