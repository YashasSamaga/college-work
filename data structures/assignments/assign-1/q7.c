#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

#define MAX 200000
#define MOD (1000000000 + 7)


int64_t fast_exp2(int64_t base, int64_t exponent)
{
	base = base % MOD;
	exponent = exponent % MOD;	

	int64_t result = 1;
	while(exponent) {
		if(exponent%2)
			result = (result * base)%MOD;
		base = (base * base)%MOD;
		exponent /= 2;
		
	}
	return result;
}

int64_t eval(int operator, int64_t operand1, int64_t operand2) {
	switch(operator) {
		case '+': return (operand1 + operand2)%MOD;
		case '*': return (operand1 * operand2)%MOD;
		case '/': return ((operand1 % MOD) * fast_exp2(operand2, MOD - 2))%MOD;
		case '-': return (operand1 - operand2 + MOD) % MOD;
	}
}

int main () 
{
	int T;
	scanf("%d", &T);
	while(T--) {		
		char str[MAX + 1];
		scanf("%s", str);

		int len = strlen(str);
		int64_t stack[MAX];

		int64_t top = -1, i;
		for(i = 0; i < len; i++) {
			if(isdigit(str[i])) {
				stack[++top] = str[i] - '0';
			} else {
				int64_t oper2 = stack[top--],
				        oper1 = stack[top--];
				stack[++top] = eval(str[i], oper1, oper2);
			}
		}
		printf("%"PRId64"\n", stack[top]);	
	}
	return 0;
}
