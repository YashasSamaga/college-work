import math

x = [1, 2, 3, 4, 5, 6, 7, 8]
N = len(x)

print("UP-SWEEP:")
for d in range(0, int(math.log2(N))):
    print("d:", d)
    for k in range(0, N, 2**(d+1)):
        print("\tk=%d, 2^d=%d, 2^(d+1)=%d" % (k, 2**d, 2**(d+1)))
        print("\tx[k + 2^(d+1) - 1] = x[k + 2^d - 1] + x[k + 2^d]")
        print("\tx[%d] = x[%d] + x[%d]" % (k + 2**(d+1) - 1, k + 2**d - 1, k + 2**(d+1) - 1))
        x[k + 2**(d+1) - 1] = x[k + 2**d - 1] + x[k + 2**(d+1) - 1]
        print()
    print("result:", x)
print()

print("DOWN-SWEEP:")
x[N - 1] = 0
d = int(math.log2(N)) - 1
while d >= 0:
    print("d:", d)
    for k in range(0, N - 1, 2**(d+1)):
        print("\tk=%d, 2^d=%d, 2^(d+1)=%d" % (k, 2**d, 2**(d+1)))
        temp = x[k + 2**d - 1]
        x[k + 2**d - 1] = x[k + 2**(d+1) - 1]
        x[k + 2**(d+1) - 1] += temp
    d -= 1
    print("result:", x)
