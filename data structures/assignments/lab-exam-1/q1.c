#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int A;
	int C;
} Child;

int  compare(const void* a, const void* b) {
	Child *c1 = (Child*)a,
	      *c2 = (Child*)b;
		
	if(c1->A != c2->A)
		return c1->A - c2->A;
	return c2->C - c1->C;	
}

int main () {
	int n;
	scanf("%d", &n);

	int i;
	Child children[n];
	for(i = 0; i < n; i++)
		scanf("%d%d", &children[i].A, &children[i].C);

	qsort(children, n, sizeof(Child), compare);

	long long count = 0;
	int last = 0;
	for(i = 0; i < n; i++) {
		if(last <= children[i].C)
			last = children[i].C + 1;			
		count += last;
		//printf("Give %d chocolates to (%d, %d)\n", last, children[i].A, children[i].C);
	}
	//for(i = 0; i < n; i++)
		//printf("%d %d\n", children[i].A, children[i].C);

	printf("%lld", count);	
	return 0;
}
