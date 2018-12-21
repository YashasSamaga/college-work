#include <stdio.h>
#include <math.h>

int main () {
	long long n;
	scanf("%lld", &n);

	long long powers[24];

	int i;
	for(i = 0; i < 24; i++) {
		powers[i] = (long long)pow(5, i);
		//printf("%d %lld \n",  i,powers[i]);
	}

	if(n == 1)
		return printf("0");
	//int k = 2;
	//while(k < 1000) {
		//n = k++;
		long long answer = 0;
		n--;
		while(n > 0) {
			for(i = 23; i >= 0; i--)
				if(n >= powers[i])
					break;

			//printf("%lld %lld %d\n", n, powers[i], i);

			long long q = n/powers[i],
				  r = n % powers[i];

			answer += q*pow(10, i);
			n = r;
		}
		printf("%lld\n", answer);		
	//}
	return 0;
}
