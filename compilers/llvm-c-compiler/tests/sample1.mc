extern void writeInteger(int);
extern void writeString(char str[]);
extern int readInteger();

int power(int x, int exp)
{
    int result = 1;
    for (int i = 0; i < exp; i++)
    {
        result *= x;
    }
    return result;
}

int g(int N, int k)
{
    int accumulator = 0;
    for (int i = 1; i < N; i++)
    {
        accumulator += power(i, k);
    }
    return accumulator;
}

void main ()
{
    int N = readInteger();
    int k = readInteger();
    writeInteger(g(N, k));
}