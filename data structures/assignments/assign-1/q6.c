#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define debug(...) //printf(__VA_ARGS__)

#define stack_max (1000 + 1)

typedef int stackitem_t;
typedef struct {
	stackitem_t stack[stack_max];
	unsigned int top;
} Stack;

void push(Stack *s, stackitem_t item) {
	debug("[DEBUG] pushed item %d to stack %p (top = %d)\n", item, s, s->top + 1);
	s->stack[++(s->top)] = item;
}
stackitem_t pop(Stack *s) {
	debug("[DEBUG] poped item %d from stack %p (top = %d)\n", s->stack[s->top], s, s->top - 1);
	return s->stack[(s->top)--];
}

/* helpers */
void copy(int32_t *first, int32_t *last, int32_t *dest) //[first, last)
{
	while(first != last)
		*dest++ = *first++;
}

/* sorting */
void msmerge(int32_t nums[], int32_t first, int32_t mid, int32_t last) //[first, mid), [mid, last)
{
	int32_t size_left = mid - first, left[size_left];
	copy(&nums[first], &nums[mid], left);

	int32_t left_itr = 0, right_itr = mid, dest_itr = first;
	while(left_itr < size_left && right_itr < last)
	{
		if(left[left_itr] < nums[right_itr])
			nums[dest_itr++] = left[left_itr++];
		else
			nums[dest_itr++] = nums[right_itr++];
	}
	copy(&left[left_itr], &left[size_left], &nums[dest_itr]);
	copy(&nums[right_itr], &nums[last], &nums[dest_itr]);
}

void mssplit(int32_t nums[], int32_t first, int32_t last) //[first, last)
{
	if(first >= (last - 1))
		return;

	int32_t mid = (first + last)/2;
	mssplit(nums, first, mid); //[first, mid)
	mssplit(nums, mid, last); //[mid, last)
	
	msmerge(nums, first, mid, last);
}

void mssort(int32_t nums[], int32_t size) 
{
	mssplit(nums, 0, size);
}

int main () {
	int n;
	scanf("%d", &n);

	int nums[n], i;
	for(i = 0; i < n; i++)
		scanf("%d", &nums[i]);
	
	/* create stacks */
	Stack s1, s2;
	s1.top = s2.top = -1;

	/* copy the values to the stack */
	copy(&nums[0], &nums[n], s1.stack);
	s1.top = n - 1;	

	/* sort nums */
	mssort(nums, n);

	/* hash the values to identify in which stack the number is in */
	enum {
	 	STACK1,
		STACK2
	};
	int which_stack[1001];
	memset(which_stack, STACK1, sizeof(which_stack));

	/**/
	int count = 0;
	for(i = 0; i < n; i++) {
		debug("[DEBUG] Iteration: value=%d, stack_pos=%d\n", nums[i], which_stack[nums[i]]);

		const int value = nums[i];
		switch(which_stack[value]) {
			case STACK1:
			{
				int top = pop(&s1);
				while(top != value) {
					push(&s2, top);
					which_stack[top] = STACK2;
					top = pop(&s1);
					count++;
				}
				break;
			}
			case STACK2:
			{
				int top = pop(&s2);
				while(top != value) {
					push(&s1, top);					
					which_stack[top] = STACK1;
					top = pop(&s2);
					count++;
				}
				break;
			}
		}
	}
	printf("%d", count);
	return 0;
}
